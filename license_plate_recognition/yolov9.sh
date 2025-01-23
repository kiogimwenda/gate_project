#!/bin/bash

# Update and upgrade the system
sudo apt update && sudo apt upgrade -y

# Install system dependencies
sudo apt install -y git python3 python3-venv python3-pip wget unzip

# Create and activate a Python virtual environment
python3 -m venv yolov9_env
source yolov9_env/bin/activate

# Upgrade pip
pip install --upgrade pip

# Clone the YOLOv9 repository
git clone https://github.com/WongKinYiu/yolov9.git
cd yolov9

# Install Python dependencies
pip install -r requirements.txt

# Download pre-trained weights (optional)
mkdir weights
cd weights
wget https://github.com/WongKinYiu/yolov9/releases/download/v0.1/yolov9s.pt
cd ..

# Download the dataset
echo "Downloading dataset..."
wget --no-check-certificate https://www.kaggle.com/datasets/fareselmenshawii/large-license-plate-dataset/download -O license_plate_dataset.zip

# Extract the dataset
echo "Extracting dataset..."
unzip license_plate_dataset.zip -d license_plate_dataset
rm license_plate_dataset.zip

# Create a blank data.yaml file
echo "Creating data.yaml file..."
touch data.yaml
echo "# Add your dataset configuration here" > data.yaml

# Test the installation with a sample image
#python detect.py --weights weights/yolov9s.pt --cfg none --source data/images/bus.jpg --device cpu

# Deactivate the virtual environment
deactivate

echo "YOLOv9 installation, dataset download, and setup complete."
