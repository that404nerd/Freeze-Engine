# Freeze Engine
Freeze Engine - A Small Game Engine Made Using C++ and OpenGL

## UPDATE: I DIDN'T ABANDON THIS PROJECT. I WILL RESUME IT IN PROBABLY 10 DAYS. 

## How To Run?
This engine only supports linux for now (I will extend this to windows and etc...). If you are running Linux make sure you have:
- glew
- glfw
- opengl
- cmake
Other dependencies will be taken care by the cmake.

### C++ LSP Neovim Issue:
If you are using neovim (or any other editor with clang lsp server) as your editor and you have clangd server enabled then follow these steps:
```bash
git clone https://github.com/systemcoding/Freeze-Engine
cd Freeze-Engine
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cmake --build . -j5
./bin/Sandbox
```
Since the clangd lsp server requires the compile_commands.json for finding header files and correct linking use the above commands.

### NixOS Users:
Follow the above instructions to clone the project and go to the project directory. From there, run `nix develop` and the build the project as mentioned above.
The flake.nix has all the dependencies required for the project to run.

### Instructions: (Not For Neovim LSP Users!!!)
```bash
git clone --recursive https://github.com/systemcoding/Freeze-Engine
cd Freeze-Engine/
mkdir build
cmake ..
make -j5
./bin/Sandbox
```

## Version 0.4:
- Better Batch Renderer
- Replaced Box2D Debug Renderer with Batch Renderer functions
- Removed some sandbox clutter
- Added Framebuffers
- Added OS and GPU Info to Sandbox
- Fixed a crash when calling the OnClose() Window Event
- Fixed several bugs

Also for debugging, compile with this: `cmake -DCMAKE_BUILD_TYPE=Debug ..`
