cmake_minimum_required(VERSION 3.5.0)
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

# Build library
add_library(app ${SOURCES})

# Link the libraries
target_link_libraries(app PUBLIC zlib_static png_static)

# Make the library installable
install(TARGETS app DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Add CPack for packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "lenoben002@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "a simple image processing package")
set(CPACK_PACKAGE_VENDOR "len")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

# Specify the generator (e.g., TGZ for .tar.gz, ZIP for .zip, DEB for Debian package, etc.)
# set(CPACK_GENERATOR "TGZ;ZIP")

include(CPack)

# Enable testing
include(CTest)
enable_testing()

# Add test executable
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)
add_executable(apptests ${TEST_SOURCES})

# Link test executable with the library
target_link_libraries(apptests PRIVATE app)

# Set output directory
set_target_properties(apptests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)

# Copy resources to output directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/ DESTINATION ${CMAKE_SOURCE_DIR}/out/)

# Add tests
add_test(NAME AppTest COMMAND ${CMAKE_SOURCE_DIR}/out/apptests)

# Change the working directory for the test to `out/`
set_tests_properties(AppTest PROPERTIES
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)
