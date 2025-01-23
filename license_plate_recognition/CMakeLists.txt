cmake_minimum_required(VERSION 3.10)
project(LicensePlateRecognition)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#Find Python/YOLO
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Find Tesseract
find_package(Tesseract REQUIRED)

#Google Test
find_package(GTest REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Tesseract_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${Python3_INCLUDE_DIRS})
include_directories(include)

# Add executable
add_executable( src/main.cpp src/image_loader.cpp src/preprocessing.cpp src/plate_detection.cpp src/ocr.cpp)
add_executable(test_preprocessor tests/test_preprocessor.cpp, src/preprocessor.cpp)
# Link libraries
target_link_libraries(main ${OpenCV_LIBS} ${Tesseract_LIBRARIES})
target_link_librarries(test_preprocessor ${GTEST_LIBRARIES} ${OPENCV_LIBS} pthread)

#add test
add_test(NAME PreprocessrTest COMMAND test_preprocessor)
