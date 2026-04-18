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
      '';
    };
  };
}
