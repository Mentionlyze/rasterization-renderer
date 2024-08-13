cmake_minimum_required(VERSION 3.25)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  RASTERIZATION
  LANGUAGES CXX
 
)

add_subdirectory(3rdlibs)
add_subdirectory(Renderer)
add_subdirectory(Sandbox)


# file(GLOB_RECURSE IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Assets/*")

# foreach(img in ${IMAGE_FILES})
#   message(${img})
# endforeach()


# add_custom_target(copy_images ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR})

# add_custom_command(
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Assets
  
#   DEPENDS ${IMAGE_FILES}
#   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Assets/images
#   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${IMAGE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/Assets/images
# )

