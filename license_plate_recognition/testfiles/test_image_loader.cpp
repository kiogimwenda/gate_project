
#include <iostream>
#include "image_loader.hpp"

int main() {
    std::string url = "https:192.168.0.105:3658"; // Replace with your video stream URL
    std::string username = "admin";        // Replace with your username
    std::string password = "123";        // Replace with your password

    try {
        cv::Mat image = loadImageFromWeb(url, username, password);

        if (!image.empty()) {
            std::cout << "Image loaded successfully from the web stream." << std::endl;
            cv::imshow("Loaded Image", image);
            cv::waitKey(0); // Wait for a key press to close the window
        } else {
            std::cerr << "Failed to load image from the web stream." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}



