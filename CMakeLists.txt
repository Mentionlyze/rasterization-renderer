cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET "RASTERIZATION")

project(
  ${TARGET}
  LANGUAGES C CXX
  DESCRIPTION "a tiny renderer with rasterization by cpp"
  VERSION 0.0.1
)

add_subdirectory(Renderer)
add_subdirectory(Sandbox)

