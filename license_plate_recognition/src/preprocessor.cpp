#include "preprocessor.hpp"
#include <stdexcept>
#include <future>
#include <omp.h>

PreprocessedImages Preprocessor::preprocess(const cv::Mat& image) {
    if (image.empty()) {
        throw std::runtime_error("Input image is empty");
    }

    PreprocessedImages result;

    auto grayscaleTask = std::async(std::launch::async, [&]() {
        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        return gray;
    });

    result.grayscale = grayscaleTask.get();
    
    auto claheTask = std::async(std::launch::async, &Preprocessor::applyCLAHE, result.grayscale);
    result.clahe = claheTask.get();

    auto blurredTask = std::async(std::launch::async, &Preprocessor::applyGaussianBlur, result.clahe);
    result.blurred = blurredTask.get();

    auto edgesTask = std::async(std::launch::async, &Preprocessor::detectEdges, result.blurred);
    result.edgeDetected = edgesTask.get();

    auto thresholdTask = std::async(std::launch::async, &Preprocessor::applyAdaptiveThreshold, result.edgeDetected);
    result.thresholded = thresholdTask.get();

    auto morphTask = std::async(std::launch::async, &Preprocessor::applyMorphologicalOperations, result.thresholded);
    result.morphed = morphTask.get();

    auto filterContoursTask = std::async(std::launch::async, &Preprocessor::filterContours, result.morphed);
    result.plateContours = filterContoursTask.get();

    return result;
}

cv::Mat Preprocessor::applyCLAHE(const cv::Mat& image) {
    cv::Mat claheImage;
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(2.0);
    clahe->setTilesGridSize(cv::Size(8, 8));
    clahe->apply(image, claheImage);
    return claheImage;
}

cv::Mat Preprocessor::applyGaussianBlur(const cv::Mat& image) {
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(5, 5), 0);
    return blurredImage;
}

cv::Mat Preprocessor::detectEdges(const cv::Mat& image) {
    cv::Mat edges;
    cv::Canny(image, edges, 50, 150);
    return edges;
}

cv::Mat Preprocessor::applyAdaptiveThreshold(const cv::Mat& image) {
    cv::Mat thresholdedImage;
    cv::adaptiveThreshold(image, thresholdedImage, 255, 
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
                          cv::THRESH_BINARY_INV, 11, 2);
    return thresholdedImage;
}

cv::Mat Preprocessor::applyMorphologicalOperations(const cv::Mat& image) {
    cv::Mat morphedImage;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(image, morphedImage, kernel, cv::Point(-1, -1), 1);
    cv::erode(morphedImage, morphedImage, kernel, cv::Point(-1, -1), 1);
    return morphedImage;
}

std::vector<std::vector<cv::Point>> Preprocessor::filterContours(const cv::Mat& image) {
    std::vector<std::vector<cv::Point>> contours, filteredContours;
    cv::findContours(image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

   // #pragma omp parallel for
    for (size_t i = 0; i < contours.size(); i++) {
        cv::Rect boundingRect = cv::boundingRect(contours[i]);
        double aspect_ratio = static_cast<double>(boundingRect.width) / boundingRect.height;

        if (aspect_ratio > 2 && aspect_ratio < 5 && cv::contourArea(contours[i]) > 1000) {
           // #pragma omp critical
            filteredContours.push_back(contours[i]);
        }
    }

    return filteredContours;
}





