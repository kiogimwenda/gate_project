#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <vector>

struct PreprocessedImages{
	cv::Mat grayscale;
	cv::Mat edgeDetected;
	cv::Mat threshold;
	cv::Mat morphed;
	std::vector<std::vector<cv::Point>> plateContours;
};

PreprocessedImages preprocessImage(const cv::Mat& image);
