#include <gtest/gtest.h>
#include "preprocessing.hpp"

class PreprocessingTest : public ::testing::Test{
protected:
	cv::Mat testImage;

	void SetUp() override{
		//Load a test image
		testImage  = cv::imread("sample.jpeg");
		ASSERT_FALSE(testImage.empty()) << "Test image could not be loaded";
	}
};

TEST_F(PreprocessingTest, PreprocessImageOutputsAreNotEmpty){
	PreprocessedImages result = preprocessImage(testImage);
	EXPECT_FALSE(result.grayscale.empty());
	EXPECT_FALSE(result.edgeDetected.empty());
	EXPECT_FALSE(result.threshold.empty());
	EXPECT_FALSE(result.morphed.empty());
}

TEST_F(PreprocessingTest, GrayscaleImageHasCorrectChannels){
	PreprocessedImages result = preprocessImage(testImage);
	EXPECT_EQ(result.grayscale.channels(), 1);
}

TEST_F(PreprocessingTest, EdgeDetectedImageisBinary){
	PreprocessedImages result = preprocessImage(testImage);
	EXPECT_EQ(result.edgeDetected.type(), CV_8UC1);
}
TEST_F(PreprocessingTest, ThresholdedImageisBinary){
	PreprocessedImages result = preprocessImage(testImage);
	EXPECT_EQ(result.threshold.type(), CV_8UC1);
}

TEST_F(PreprocessingTest, PlateContoursAreDetected){
	PreprocessedImages result = preprocessImage(testImage);
	EXPECT_GT(result.plateContours.size(), 0);
}

TEST_F(PreprocessingTest, EmptyImageThrowException){
	cv::Mat emptyImage;
	EXPECT_THROW(preprocessImage(emptyImage), std::runtime_error);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
