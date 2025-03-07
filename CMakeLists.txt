cmake_minimum_required(VERSION 3.20)

project(Helix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Configuration options
set(CMAKE_CONFIGURATION_TYPES Debug Release Dist)

# Dependencies
add_subdirectory(Helix/vendor/GLFW)
add_subdirectory(Helix/vendor/Glad)
add_subdirectory(Helix/vendor/imgui)

# Include directories
include_directories(Helix/src)
include_directories(Helix/vendor/spdlog/include)
include_directories(Helix/vendor/stb_image)
include_directories(Helix/vendor/glm)
include_directories(Helix/vendor/GLFW/include)
include_directories(Helix/vendor/Glad/include)
include_directories(Helix/vendor/imgui)

# Helix Library
add_library(Helix STATIC
    Helix/src/hxpch.cpp
    Helix/src/**.h
    Helix/src/**.cpp
    Helix/vendor/stb_image/**.h
    Helix/vendor/stb_image/**.cpp
    Helix/vendor/glm/glm/**.hpp
    Helix/vendor/glm/glm/**.inl
)

# Platform-specific files
if(UNIX)
    target_compile_definitions(Helix PRIVATE HX_PLATFORM_LINUX)
    file(GLOB_RECURSE LINUX_SOURCES Helix/src/Platform/Linux/*.cpp)
    target_sources(Helix PRIVATE ${LINUX_SOURCES})
endif()

if(WIN32)
    target_compile_options(Helix PRIVATE /utf-8)
    target_compile_definitions(Helix PRIVATE HX_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)
    file(GLOB_RECURSE WINDOWS_SOURCES Helix/src/Platform/Windows/*.cpp)
    target_sources(Helix PRIVATE ${WINDOWS_SOURCES})
endif()

# Linking
target_link_libraries(Helix PRIVATE GLFW Glad imgui)
if(WIN32)
    target_link_libraries(Helix PRIVATE opengl32 gdi32 user32 kernel32)
endif()

# Configurations
target_compile_definitions(Helix PRIVATE $<$<CONFIG:Debug>:HX_DEBUG>)
target_compile_definitions(Helix PRIVATE $<$<CONFIG:Release>:HX_RELEASE>)
target_compile_definitions(Helix PRIVATE $<$<CONFIG:Dist>:HX_DIST>)

# Sandbox Application
add_executable(Sandbox
    Sandbox/src/**.h
    Sandbox/src/**.cpp
)

# Sandbox includes and linking
target_include_directories(Sandbox PRIVATE Helix/src Helix/vendor/spdlog/include Helix/vendor/imgui Helix/vendor/glm)
target_link_libraries(Sandbox PRIVATE Helix)

# Sandbox configurations
target_compile_definitions(Sandbox PRIVATE $<$<CONFIG:Debug>:HX_DEBUG>)
target_compile_definitions(Sandbox PRIVATE $<$<CONFIG:Release>:HX_RELEASE>)
target_compile_definitions(Sandbox PRIVATE $<$<CONFIG:Dist>:HX_DIST>)
