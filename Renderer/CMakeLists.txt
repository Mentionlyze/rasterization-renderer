aux_source_directory(src/Core renderer_core_sources)
aux_source_directory(src/Runtime renderer_runtime_sources)
aux_source_directory(src/Platform renderer_platform_sources)

foreach(file in ${renderer_runtime_sources})
message(${file})
endforeach()


add_library(Renderer ${renderer_core_sources} ${renderer_runtime_sources} ${renderer_platform_sources}) 
target_include_directories(Renderer PUBLIC ./include)
set_target_properties(Renderer PROPERTIES PUBLIC_HEADER "${renderer_headers}")
target_link_libraries(Renderer PUBLIC stb_image)
target_compile_definitions(Renderer PRIVATE USE_CPU_RENDERER=1)
target_compile_definitions(Renderer PRIVATE USE_GPU_RENDERER=0)