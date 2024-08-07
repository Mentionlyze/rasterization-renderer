aux_source_directory(. sandbox_sources)
file(GLOB_RECURSE sandbox_headers "./*.hpp")

add_executable(Sandbox ${sandbox_sources})
target_include_directories(Sandbox PRIVATE Include)
target_link_libraries(Sandbox PRIVATE Renderer)