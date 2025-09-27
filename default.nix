{
  cmake,
  lib,
  stdenv,
}:
stdenv.mkDerivation {
  pname = "prexy";
  version = lib.trim (builtins.readFile ./version.txt);
  src = lib.cleanSource ./.;

  nativeBuildInputs = [cmake];

  configurePhase = ''
    cmake -B build
  '';

  buildPhase = ''
    cmake --build build
  '';

  installPhase = ''
    if [[ "$CC" == *"mingw32"* ]]; then
      # Workaround broken pkgCross cmake install
      mkdir -p "$out/bin"
      cp build/src/*.exe "$out/bin"
    else
      cmake --install build --prefix $out
    fi
  '';
}
