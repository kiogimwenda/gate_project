#include <gtest/gtest.h>
#ifdef UNIT_TEST
#define private public
#endif
#include "preprocessor.hpp"
#ifdef UNIT_TEST
#undef private
#endif
#include <opencv2/opencv.hpp>
#include <future>
#include <vector>
#include <filesystem>  // C++17

// Helper function to compare two images
bool areImagesEqual(const cv::Mat& img1, const cv::Mat& img2) {
    if (img1.size() != img2.size() || img1.type() != img2.type())
        return false;
    cv::Mat diff;
    cv::absdiff(img1, img2, diff);
    return (cv::countNonZero(diff) == 0);
}

// Test fixture for Preprocessor tests
class PreprocessorTest : public ::testing::Test {
protected:
    cv::Mat sampleImage;

    void SetUp() override {
        // Update the path to a valid sample image on your system.
	std::filesystem::path image_path = std::filesystem::path("../bin/test_images")/ "sample1.jpg";
        sampleImage = cv::imread(image_path.string());
        ASSERT_FALSE(sampleImage.empty()) << "Sample image not found!";
    }
};

/*TEST_F(PreprocessorTest, TestApplyCLAHE) {
    cv::Mat grayImage;
    cv::cvtColor(sampleImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat claheImage = Preprocessor::applyCLAHE(grayImage);
    ASSERT_EQ(claheImage.channels(), 1);
    ASSERT_EQ(claheImage.size(), grayImage.size());
}

TEST_F(PreprocessorTest, TestApplyGaussianBlur) {
    cv::Mat grayImage;
    cv::cvtColor(sampleImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat blurredImage = Preprocessor::applyGaussianBlur(grayImage);
    ASSERT_EQ(blurredImage.channels(), 1);
    ASSERT_EQ(blurredImage.size(), grayImage.size());
}

TEST_F(PreprocessorTest, TestDetectEdges) {
    cv::Mat grayImage;
    cv::cvtColor(sampleImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat edges = Preprocessor::detectEdges(grayImage);
    ASSERT_EQ(edges.channels(), 1);
    ASSERT_EQ(edges.size(), grayImage.size());
}

TEST_F(PreprocessorTest, TestApplyAdaptiveThreshold) {
    cv::Mat grayImage;
    cv::cvtColor(sampleImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat thresholdedImage = Preprocessor::applyAdaptiveThreshold(grayImage);
    ASSERT_EQ(thresholdedImage.channels(), 1);
    ASSERT_EQ(thresholdedImage.size(), grayImage.size());
}

TEST_F(PreprocessorTest, TestApplyMorphologicalOperations) {
    cv::Mat grayImage;
    cv::cvtColor(sampleImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat morphedImage = Preprocessor::applyMorphologicalOperations(grayImage);
    ASSERT_EQ(morphedImage.channels(), 1);
    ASSERT_EQ(morphedImage.size(), grayImage.size());
}

TEST_F(PreprocessorTest, TestFilterContours) {
    cv::Mat grayImage;
    cv::cvtColor(sampleImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat thresholdedImage = Preprocessor::applyAdaptiveThreshold(grayImage);
    std::vector<std::vector<cv::Point>> contours = Preprocessor::filterContours(thresholdedImage);
    ASSERT_FALSE(contours.empty());
}
*/
TEST_F(PreprocessorTest, TestPreprocess) {
    PreprocessedImages result = Preprocessor::preprocess(sampleImage);
    ASSERT_EQ(result.grayscale.channels(), 1);
    ASSERT_EQ(result.clahe.channels(), 1);
    ASSERT_EQ(result.blurred.channels(), 1);
    ASSERT_EQ(result.edgeDetected.channels(), 1);
    ASSERT_EQ(result.thresholded.channels(), 1);
    ASSERT_EQ(result.morphed.channels(), 1);
    ASSERT_FALSE(result.plateContours.empty());
}

TEST_F(PreprocessorTest, TestConcurrentPreprocessing) {
    const int numThreads = 4;
    std::vector<std::future<PreprocessedImages>> futures;
    for (int i = 0; i < numThreads; ++i) {
        futures.push_back(std::async(std::launch::async, [&]() {
            return Preprocessor::preprocess(sampleImage);
        }));
    }
    std::vector<PreprocessedImages> results;
    for (auto& fut : futures) {
        results.push_back(fut.get());
    }
    for (size_t i = 1; i < results.size(); i++) {
        ASSERT_EQ(results[i].grayscale.size(), results[0].grayscale.size());
        ASSERT_EQ(results[i].grayscale.type(), results[0].grayscale.type());
    }
}

TEST_F(PreprocessorTest, TestSavePreprocessedSteps) {
    namespace fs = std::filesystem;
    // Define the output directory (adjust the path if necessary)
    fs::path outputDir = fs::current_path() / "data" / "results" / "preprocessed";
    fs::create_directories(outputDir);

    PreprocessedImages result = Preprocessor::preprocess(sampleImage);

    // Save intermediate images
    cv::imwrite((outputDir / "grayscale.jpg").string(), result.grayscale);
    cv::imwrite((outputDir / "clahe.jpg").string(), result.clahe);
    cv::imwrite((outputDir / "blurred.jpg").string(), result.blurred);
    cv::imwrite((outputDir / "edgeDetected.jpg").string(), result.edgeDetected);
    cv::imwrite((outputDir / "thresholded.jpg").string(), result.thresholded);
    cv::imwrite((outputDir / "morphed.jpg").string(), result.morphed);

    // Draw and save contours on top of the grayscale image
    cv::Mat contourImage;
    cv::cvtColor(result.grayscale, contourImage, cv::COLOR_GRAY2BGR);
    cv::drawContours(contourImage, result.plateContours, -1, cv::Scalar(0, 255, 0), 2);
    cv::imwrite((outputDir / "contours.jpg").string(), contourImage);

    SUCCEED(); // Test passes if saving succeeded without error
}
