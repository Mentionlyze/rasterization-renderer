cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



project(
  RASTERIZATION
  LANGUAGES CXX C
)

add_subdirectory(3rdlibs)
add_subdirectory(Renderer)


aux_source_directory(./Sandbox sandbox_sources)
file(GLOB_RECURSE sandbox_headers "./Sandbox/*.hpp")

add_executable(Rasterization ${sandbox_sources})
target_include_directories(Rasterization PRIVATE Include)
target_link_libraries(Rasterization PRIVATE Renderer)

target_compile_definitions(Rasterization PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")

# file(GLOB_RECURSE IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Assets/*")

# foreach(img in ${IMAGE_FILES})
#   message(${img})
# endforeach()


# add_custom_target(copy_images ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
  TARGET Rasterization PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ $<TARGET_FILE_DIR:Rasterization>/Assets/ 
)


