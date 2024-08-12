aux_source_directory(src/Runtime renderer_runtime_sources)
aux_source_directory(src/Platform renderer_platform_sources)

foreach(file in ${renderer_runtime_sources})
message(${file})
endforeach()


add_library(Renderer ${renderer_runtime_sources} ${renderer_platform_sources}) 
target_include_directories(Renderer PUBLIC ./include)
set_target_properties(Renderer PROPERTIES PUBLIC_HEADER "${renderer_headers}")
target_compile_definitions(Renderer PRIVATE USE_CPU_RENDERER=0)
target_compile_definitions(Renderer PRIVATE USE_GPU_RENDERER=1)