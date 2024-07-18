#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include <opencv2/opencv.hpp>

cv::Mat loadImageFromWeb(const std::string& url, const std::string& username, const std::string& password);

#endif
