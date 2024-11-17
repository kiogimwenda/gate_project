#!/bin/bash

# Exit on any error
set -e

echo "Installing YOLOv8 and dependencies on Raspberry Pi..."

# Install system dependencies
echo "Installing system dependencies..."
sudo apt-get update
sudo apt-get install -y \
    python3-pip \
    python3-venv \
    libopencv-dev \
    python3-opencv \
    git \
    cmake \
    build-essential \
    libatlas-base-dev \
    libopenmpi-dev

# Create a virtual environment in /opt for system-wide access
sudo mkdir -p /opt/yolo
sudo chown $USER:$USER /opt/yolo
python3 -m venv /opt/yolo/venv

# Activate virtual environment
source /opt/yolo/venv/bin/activate

# Upgrade pip
pip install --upgrade pip

# Install PyTorch (optimized for Raspberry Pi)
echo "Installing PyTorch..."
pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu

# Install YOLOv8
echo "Installing YOLOv8..."
pip install ultralytics

# Create symbolic links for system-wide access
sudo ln -s /opt/yolo/venv/bin/yolo /usr/local/bin/yolo

# Create activation script
cat << EOF > /opt/yolo/activate_yolo.sh
#!/bin/bash
source /opt/yolo/venv/bin/activate
EOF

chmod +x /opt/yolo/activate_yolo.sh
sudo ln -s /opt/yolo/activate_yolo.sh /usr/local/bin/activate_yolo

# Create a small test script
cat << EOF > /opt/yolo/test_yolo.py
from ultralytics import YOLO

# Load a model
model = YOLO('yolov8n.pt')

print("YOLOv8 installation test successful!")
print("Model loaded successfully:", model)
EOF

echo "Installation complete!"
echo "To activate the YOLO environment, run: source activate_yolo"
echo "To test the installation, run: python /opt/yolo/test_yolo.py"
echo "To use YOLO directly, simply use the 'yolo' command"
