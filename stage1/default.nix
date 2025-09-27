{
  lib,
  stdenvNoCC,
}:
stdenvNoCC.mkDerivation {
  pname = "prexy";
  version = builtins.readFile ../version.txt;
  src = lib.cleanSource ./..;

  installPhase = ''
    mkdir -p $out/share

    mv stage1 $out/bin
    mv include $out
    mv docs $out/share/prexy-docs
  '';

  meta = {
    license = lib.licenses.gpl3Plus;
    mainProgram = "prexy";
  };
}
