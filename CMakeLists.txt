cmake_minimum_required(VERSION 3.10)
project(app VERSION 0.1.0 LANGUAGES C CXX)

# Set required standard to C++20.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add zlib and libpng subdirectories
add_subdirectory(zlib/)
add_subdirectory(png/)

# Include directories for zlib and libpng
include_directories(zlib/)
include_directories(png/)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)


# Add source files with src/main.cpp
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Build executable
add_executable(app ${SOURCES})

# Link the libraries
target_link_libraries(app PRIVATE zlib_static png_static)

# This ensures its able to run as a standalone executable on a new device
target_link_options(app PRIVATE -static-libgcc -static-libstdc++ -static)

# Set output directory
set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)

# Copy resources to output directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/ DESTINATION ${CMAKE_SOURCE_DIR}/out/)
