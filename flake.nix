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
        inherit (self.packages.${system}) c-start;

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
          c-start = pkgs.callPackage ./. {
            stdenv = pkgs.clangStdenv;
          };

          c-start-gcc = c-start.override {
            inherit (pkgs) stdenv;
          };

          c-start-win = c-start.override {
            inherit (pkgs.pkgsCross.mingwW64) stdenv;
          };

          default = c-start;
        };

        devShells = {
          default = pkgs.mkShell {
            inputsFrom = [c-start];
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
        };

        formatter = pkgs.alejandra;
      }
    );
}
