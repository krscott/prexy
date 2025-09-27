{
  lib,
  stdenvNoCC,
}: let
  includeSrc = lib.cleanSource ../include;
in
  stdenvNoCC.mkDerivation {
    pname = "prexy";
    version = builtins.readFile ../version.txt;
    src = lib.cleanSource ./.;

    installPhase = ''
      mkdir -p $out/bin
      chmod +x prexy.awk
      mv prexy.awk $out/bin/prexy
      cp -r ${includeSrc} $out/include
    '';

    meta = {
      license = lib.licenses.gpl3Plus;
      mainProgram = "prexy";
    };
  }
