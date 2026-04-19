{
  description = "QMK firmware build environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-24.11";
  };

  outputs = { self, nixpkgs }: 
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        gcc-arm-embedded
        gnumake
        git
        dfu-util
        hidapi
        libusb1

        (python3.withPackages (ps: with ps; [
          argcomplete
          colorama
          dotty-dict
          hid
          hjson
          jsonschema
          milc
          pygments
          pyserial
          pyusb
          pillow
        ]))
      ];

      shellHook = ''
        export ORIG_CWD=$PWD
        export PYTHONPATH=$PWD/lib/python:$PYTHONPATH
        export LD_LIBRARY_PATH=${pkgs.hidapi}/lib:${pkgs.libusb1}/lib:$LD_LIBRARY_PATH

        [ -f env/bin/activate ] && source env/bin/activate
      '';
    };
  };
}
