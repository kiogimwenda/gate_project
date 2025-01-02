#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define colors
YELLOW='\033[1;33m'
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # No Color

# Function to print colored messages
print_message() {
    echo -e "${YELLOW}$1${NC}"
}

print_message "Updating and upgrading the system..."
sudo apt update
sudo apt full-upgrade -y

print_message "Installing dependencies..."
sudo apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    libgtk-3-dev \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libv4l-dev \
    libxvidcore-dev \
    libx264-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libtbb-dev \
    libopenblas-dev \
    libatlas-base-dev \
    libblas-dev \
    liblapack-dev \
    gfortran \
    python3-dev \
    libprotobuf-dev \
    protobuf-compiler \
    libgoogle-glog-dev \
    libgflags-dev \
    libgphoto2-dev \
    libeigen3-dev \
    libhdf5-dev \
    libhdf5-serial-dev \
    python3-numpy \
    python3-pip \
    python3-scipy \
    wget \
    unzip

print_message "Installing Tesseract and related dependencies..."
sudo apt-get install -y \
    libleptonica-dev \
    tesseract-ocr \
    tesseract-ocr-eng \
    libtesseract-dev

print_message "Downloading OpenCV and OpenCV contrib..."
cd ~
if [ ! -d "opencv-5.x ]; then
   wget -O opencv-5.x.zip https://github.com/opencv/opencv/archive/5.x.zip 
fi

if [ ! -d "opencv_contrib-4.10.0" ]; then
    wget -O opencv_contrib-4.10.0.zip https://github.com/opencv/opencv_contrib/archive/4.10.0.zip
fi

print_message "Extracting downloaded zip files..."
unzip -o opencv-5.x.zip
unzip -o opencv_contrib-4.10.0.zip

print_message "Creating build directory..."
cd ~/opencv-5.x
rm -rf build  # Remove existing build directory if it exists
mkdir -p build
cd build

# Get the Python3 executable path
PYTHON3_EXECUTABLE=$(which python3)
PYTHON3_NUMPY_INCLUDE=$(python3 -c "import numpy; print(numpy.get_include())")
PYTHON3_PACKAGES_PATH=$(python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())")

print_message "Configuring the build with CMake..."
cmake \
    -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-4.10.0/modules \
    -D WITH_TBB=ON \
    -D WITH_V4L=ON \
    -D WITH_QT=OFF \
    -D WITH_OPENGL=ON \
    -D WITH_GSTREAMER=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_PC_FILE_NAME=opencv4.pc \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D OPENCV_PYTHON3_INSTALL_PATH=$PYTHON3_PACKAGES_PATH \
    -D PYTHON_EXECUTABLE=$PYTHON3_EXECUTABLE \
    -D PYTHON3_NUMPY_INCLUDE_DIRS=$PYTHON3_NUMPY_INCLUDE \
    -D PYTHON3_PACKAGES_PATH=$PYTHON3_PACKAGES_PATH \
    -D WITH_CUDA=ON \
    -D WITH_CUDNN=ON \
    -D OPENCV_DNN_CUDA=ON \
    -D ENABLE_FAST_MATH=ON \
    -D BUILD_EXAMPLES=OFF \
    -D BUILD_PERF_TESTS=OFF \
    -D BUILD_TESTS=OFF \
    -D BUILD_JAVA=OFF \
    -D BUILD_opencv_python3=ON \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D INSTALL_C_EXAMPLES=OFF \
    ..

# Check if CMake configuration was successful
if [ $? -ne 0 ]; then
    echo -e "${RED}CMake configuration failed. Please check the error messages above.${NC}"
    exit 1
fi

print_message "Compiling OpenCV..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed. Please check the error messages above.${NC}"
    exit 1
fi

print_message "Installing OpenCV..."
sudo make install
sudo ldconfig

# Verify the installation
print_message "Verifying OpenCV installation..."
pkg-config --modversion opencv4

print_message "Verifying Tesseract installation..."
tesseract --version

# Verify Python installation
print_message "Verifying Python OpenCV installation..."
python3 -c "import cv2; print('OpenCV Python Version:', cv2.__version__)"

echo -e "${GREEN}OpenCV and Tesseract have been successfully installed!${NC}"
echo -e "${YELLOW}Installation Details:${NC}"
echo "OpenCV installation prefix: /usr/local"
echo "Python packages path: $PYTHON3_PACKAGES_PATH"
echo "Python OpenCV package: $(python3 -c "import cv2; print(cv2.__file__)")"1~#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define colors
YELLOW='\033[1;33m'
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # No Color

# Function to print colored messages
print_message() {
    echo -e "${YELLOW}$1${NC}"
}

print_message "Updating and upgrading the system..."
sudo apt update
sudo apt full-upgrade -y

print_message "Installing dependencies..."
sudo apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    libgtk-3-dev \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libv4l-dev \
    libxvidcore-dev \
    libx264-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libtbb-dev \
    libopenblas-dev \
    libatlas-base-dev \
    libblas-dev \
    liblapack-dev \
    gfortran \
    python3-dev \
    libprotobuf-dev \
    protobuf-compiler \
    libgoogle-glog-dev \
    libgflags-dev \
    libgphoto2-dev \
    libeigen3-dev \
    libhdf5-dev \
    libhdf5-serial-dev \
    python3-numpy \
    python3-pip \
    python3-scipy \
    wget \
    unzip

print_message "Installing Tesseract and related dependencies..."
sudo apt-get install -y \
    libleptonica-dev \
    tesseract-ocr \
    tesseract-ocr-eng \
    libtesseract-dev

print_message "Downloading OpenCV and OpenCV contrib..."
cd ~
if [ ! -d "opencv-4.10.0" ]; then
   wget -O opencv-4.10.0.zip https://github.com/opencv/opencv/archive/4.10.0.zip 
fi

if [ ! -d "opencv_contrib-4.10.0" ]; then
    wget -O opencv_contrib-4.10.0.zip https://github.com/opencv/opencv_contrib/archive/4.10.0.zip
fi

print_message "Extracting downloaded zip files..."
unzip -o opencv-4.10.0.zip
unzip -o opencv_contrib-4.10.0.zip

print_message "Creating build directory..."
cd ~/opencv-4.10.0
rm -rf build  # Remove existing build directory if it exists
mkdir -p build
cd build

# Get the Python3 executable path
PYTHON3_EXECUTABLE=$(which python3)
PYTHON3_NUMPY_INCLUDE=$(python3 -c "import numpy; print(numpy.get_include())")
PYTHON3_PACKAGES_PATH=$(python3 -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())")

print_message "Configuring the build with CMake..."
cmake \
    -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-4.10.0/modules \
    -D WITH_TBB=ON \
    -D WITH_V4L=ON \
    -D WITH_QT=OFF \
    -D WITH_OPENGL=ON \
    -D WITH_GSTREAMER=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_PC_FILE_NAME=opencv4.pc \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D OPENCV_PYTHON3_INSTALL_PATH=$PYTHON3_PACKAGES_PATH \
    -D PYTHON_EXECUTABLE=$PYTHON3_EXECUTABLE \
    -D PYTHON3_NUMPY_INCLUDE_DIRS=$PYTHON3_NUMPY_INCLUDE \
    -D PYTHON3_PACKAGES_PATH=$PYTHON3_PACKAGES_PATH \
    -D WITH_CUDA=OFF \
    -D WITH_CUDNN=OFF \
    -D OPENCV_DNN_CUDA=OFF \
    -D ENABLE_FAST_MATH=ON \
    -D BUILD_EXAMPLES=OFF \
    -D BUILD_PERF_TESTS=OFF \
    -D BUILD_TESTS=OFF \
    -D BUILD_JAVA=OFF \
    -D BUILD_opencv_python3=ON \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D INSTALL_C_EXAMPLES=OFF \
    ..

# Check if CMake configuration was successful
if [ $? -ne 0 ]; then
    echo -e "${RED}CMake configuration failed. Please check the error messages above.${NC}"
    exit 1
fi

print_message "Compiling OpenCV..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo -e "${RED}Compilation failed. Please check the error messages above.${NC}"
    exit 1
fi

print_message "Installing OpenCV..."
sudo make install
sudo ldconfig

# Verify the installation
print_message "Verifying OpenCV installation..."
pkg-config --modversion opencv4

print_message "Verifying Tesseract installation..."
tesseract --version

# Verify Python installation
print_message "Verifying Python OpenCV installation..."
python3 -c "import cv2; print('OpenCV Python Version:', cv2.__version__)"

echo -e "${GREEN}OpenCV and Tesseract have been successfully installed!${NC}"
echo -e "${YELLOW}Installation Details:${NC}"
echo "OpenCV installation prefix: /usr/local"
echo "Python packages path: $PYTHON3_PACKAGES_PATH"
echo "Python OpenCV package: $(python3 -c "import cv2; print(cv2.__file__)")"
