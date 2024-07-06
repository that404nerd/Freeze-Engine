{
  description = "Build Engine";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            # builder
            gnumake
            cmake
            mesa

            # fix headers not found
            clang-tools
            xorg.libX11
            xorg.libX11.dev
            xorg.libXft
            xorg.libXrandr
            xorg.libXinerama
            xorg.libXcursor
            xorg.libXi

            valgrind

            # libs
            glew
            glfw
            SDL2
          ];
        };
      };
    };
}
