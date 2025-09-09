{
  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }: let
    supportedSystems = [
      "x86_64-linux"
      "aarch64-linux"
      "x86_64-darwin"
      "aarch64-darwin"
    ];
  in
    flake-utils.lib.eachSystem supportedSystems (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};

        # Final derivation including any overrides made to output package
        inherit (self.packages.${system}) prexy;

        devPkgs = with pkgs; [
          shfmt
          alejandra
          clang-tools # NOTE: clang-tools must come before clang
          clang
        ];

        mkApp = text: {
          type = "app";
          program = pkgs.lib.getExe (pkgs.writeShellApplication {
            name = "app";
            runtimeInputs = devPkgs;
            inherit text;
          });
        };
      in {
        packages = {
          prexy-stage1 = pkgs.callPackage ./stage1 {};

          prexy = pkgs.callPackage ./. {
            stdenv = pkgs.clangStdenv;
          };

          prexy-gcc = prexy.override {
            inherit (pkgs) stdenv;
          };

          prexy-win = prexy.override {
            inherit (pkgs.pkgsCross.mingwW64) stdenv;
          };

          default = prexy;
        };

        devShells = {
          default = pkgs.mkShell {
            inputsFrom = [prexy];
            nativeBuildInputs = devPkgs;
            shellHook = ''
              source dev_shell.sh
            '';
          };
        };

        apps = {
          format = mkApp ''
            ./format.sh
            alejandra ./*.nix
          '';
          test = mkApp ''
            PREXY=stage1/prexy.awk ./test/test.sh
          '';
        };

        formatter = pkgs.alejandra;
      }
    );
}
