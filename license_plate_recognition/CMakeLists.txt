cmake_minimum_required(VERSION 3.10)
project(LicensePlateRecognition VERSION 1.0 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for all executables to the 'bin' folder in the project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Find required packages
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

# Include directories for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

# Build a static library for the preprocessor module
set(PREPROCESSOR_SRC
    src/preprocessor.cpp
)

add_library(lpr ${PREPROCESSOR_SRC})
target_link_libraries(lpr ${OpenCV_LIBS})

# Enable testing
enable_testing()

# Build the preprocessor test executable
add_executable(test_preprocessor tests/test_preprocessor.cpp)
target_link_libraries(test_preprocessor lpr ${OpenCV_LIBS} GTest::GTest GTest::Main pthread)

# Register the test with CTest
add_test(NAME TestPreprocessor COMMAND test_preprocessor)
