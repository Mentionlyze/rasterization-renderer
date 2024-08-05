aux_source_directory(src renderer_sources)
file(GLOB_RECURSE renderer_headers ./include/**.hpp)

foreach(file in ${renderer_headers})
message(${file})
endforeach()


add_library(Renderer ${renderer_sources}) 
target_sources(Renderer PRIVATE ${renderer_sources})
target_sources(Renderer PUBLIC ${renderer_headers})
target_include_directories(Renderer PUBLIC ./include)
# set_target_properties(Renderer PROPERTIES PUBLIC_HEADER ${renderer_headers})