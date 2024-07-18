#ifndef PLATE_DETECTION_HPP
#define PLATE_DETECTION_HPP

#include <opencv2/opencv.hpp>

//Function to detect license plates in the image
std::vector<cv::Rect> detectPlates(const cv::Mat& inputImage);

//Function to draw detected plates in the image
cv::Mat drawDetectedPlates(const cv::Mat& inputImage, const std::vector<cv::Rect>& plates);

//Function to initialize the plate cascade
bool initPlateCascade(const std::string& cascadeFilePath);

#endif
