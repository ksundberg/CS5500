add_executable( torus_run # Executable name.
                main.cpp )

# Executable is placed in the directory cmake was run in.
set_target_properties( torus_run PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
