#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include <opencv2/opencv.hpp>

cv::Mat preprocessImage(const cv::Mat& image);
cv::Mat infraredProcessing(const cv::Mat& grayImage);
cv::Mat applyHybridThreshold(const cv::Mat& blurredImage);

#endif
