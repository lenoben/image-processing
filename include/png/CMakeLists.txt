# libpng CMakeLists.txt

# Add all source files in the src directory
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

# Create a static library (libpng_static.a) from the source files
add_library(png_static STATIC ${SOURCES})

# Specify include directories
target_include_directories(png_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link zlib library
target_link_libraries(png_static zlib_static)