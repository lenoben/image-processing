# image-processing

## Settıng the lıb up for a cmake executable project
* clone this repo in you seperate directory
* cd into the directory and create a build directory
* run this cmake command
	```sh
	cmake -DCMAKE_INSTALL_PREFIX=<project-root>/deps ..
	make install
	```
### cmake exe project
```cmake
# Include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/deps/include)

# Add zlib and libpng subdirectories
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/include/zlib/)
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/include/png/)

# Include directories for zlib and libpng
include_directories(${CMAKE_SOURCE_DIR}/deps/include/zlib/)
include_directories(${CMAKE_SOURCE_DIR}/deps/include/png/)

# Add the path to the libraries
set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/deps/lib")

# Link against the static libraries directly from the dependency folder
target_link_libraries(YOUR-EXE PRIVATE
    ${LIBRARY_PATH}/libapp.a
    zlib_static png_static
)
```
