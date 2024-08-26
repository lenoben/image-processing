# zlib CMakeLists.txt

# Add all source files in the src directory
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

# Create a static library (libzlib_static.a) from the source files
add_library(zlib_static STATIC ${SOURCES})

# Specify include directories
target_include_directories(zlib_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
