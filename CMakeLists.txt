cmake_minimum_required(VERSION 3.14)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

# Define the target directory for the binary output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add sandbox source files
file(GLOB_RECURSE SOURCES "sandbox/src/*.cpp" "engine/src/*.cpp")

# Add external dependencies
file(GLOB IMGUI_SOURCES "lib/imgui/*.cpp")

set(IMGUI_BACKEND_FILES
    "lib/imgui/backends/imgui_impl_opengl3.cpp"
    "lib/imgui/backends/imgui_impl_glfw.cpp"
)

# Add the backend files to your source files
set(SOURCES ${SOURCES} ${IMGUI_BACKEND_FILES})

# Create the root_dir.h file
file(WRITE "engine/src/core/root_dir.h" "#pragma once\n\n#include <string>\n\n")
file(APPEND "engine/src/core/root_dir.h" "inline std::string rootDir = \"${CMAKE_SOURCE_DIR}/\";\n")

# Include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Include GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Include GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# Include spdlog
include_directories(lib/spdlog/include)

# Include stb_image
include_directories(lib/stb_image/include)

# Include imgui
include_directories(lib/imgui)

# Include glm
include_directories(lib/glm)

# Include ImGuiFileDialog
include_directories(lib/ImGuiFileDialog)

# Include box2d
add_subdirectory(lib/box2d)
include_directories(lib/box2d/include)

# Include SoLoud
add_subdirectory(lib/soloud)
include_directories(lib/soloud/include)

# Include Engine files
include_directories(engine/src)

# Create the executable
add_executable(Sandbox ${SOURCES} ${IMGUI_SOURCES} ${IMGUI_BACKEND_SOURCES} ${SOLOUD_SOURCES})

# Link libraries
target_link_libraries(Sandbox ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw box2d soloud)


# Set build configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()
