#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <future>
#include <thread>

struct PreprocessedImages {
    cv::Mat grayscale;
    cv::Mat clahe;
    cv::Mat blurred;
    cv::Mat edgeDetected;
    cv::Mat thresholded;
    cv::Mat morphed;
    std::vector<std::vector<cv::Point>> plateContours;
};

class Preprocessor {
public:
    static PreprocessedImages preprocess(const cv::Mat& image);

private:
    static cv::Mat applyCLAHE(const cv::Mat& image);
    static cv::Mat applyGaussianBlur(const cv::Mat& image);
    static cv::Mat detectEdges(const cv::Mat& image);
    static cv::Mat applyAdaptiveThreshold(const cv::Mat& image);
    static cv::Mat applyMorphologicalOperations(const cv::Mat& image);
    static std::vector<std::vector<cv::Point>> filterContours(const cv::Mat& image);
};
