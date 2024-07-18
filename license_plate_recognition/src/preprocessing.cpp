#include "preprocessing.hpp"

void showOutput(const std::string& windowTitle, cv::Mat& image);

cv::Mat preprocessImage(const cv::Mat& image){

	cv::Mat grayImage, infraredImage, blurredImage, threshImage, morphedImage;
	//convert to grayscale
	cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
	showOutput("grayscale image", grayImage);

	//Apply infrared processing
	infraredImage = infraredProcessing(grayImage);
	showOutput(" Grayed infrared Image", infraredImage);

	//Apply gaussian blur
	cv::GaussianBlur(infraredImage, blurredImage, cv::Size(5,5),0);
	showOutput("blurred Image",blurredImage);

	//Apply adaptive thresholding
	threshImage = applyHybridThreshold(blurredImage);
	showOutput("Threshed Image", threshImage);

	//Apply morphological operations
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9,9));
	cv::morphologyEx(threshImage, morphedImage, cv::MORPH_CLOSE,kernel);

	return morphedImage;

}

cv::Mat infraredProcessing(const cv::Mat& grayImage){
	cv::Mat infrared = grayImage.clone();

	//Simulte infrared gprocessing
	cv::Mat infraredEnhanced;
	cv::applyColorMap(infrared, infraredEnhanced, cv::COLORMAP_JET);
	showOutput("Enhanced Infrared", infraredEnhanced);

	//Convert back to grayscale
	cv::cvtColor(infraredEnhanced, infrared, cv::COLOR_BGR2GRAY);

	return infrared;
}

cv::Mat applyHybridThreshold(const cv::Mat& blurredImage){

	//1. Adaptive Thresholding
	cv::Mat adaptiveThresholded;
	cv::adaptiveThreshold(blurredImage, adaptiveThresholded, 155, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11,2);

	//2. Otsu Thresholding
	double otsuThreshold = cv::threshold(blurredImage, blurredImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	//Combine the results(adjust weights as needed)
	cv::Mat hybridResult = 0.2*adaptiveThresholded + 0.8*blurredImage;

return hybridResult;

}

void showOutput(const std::string& windowTitle, cv::Mat& image){
	cv::imshow(windowTitle, image);
	cv::waitKey(0);
}
