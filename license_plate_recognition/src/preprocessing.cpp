#include "preprocessing.hpp"

void showOutput(const std::string& windowTitle, cv::Mat& image)
{
cv::imshow(windowTitle, image);
cv::waitKey(0);
}

PreprocessedImages preprocessImage(const cv::Mat& image){
	PreprocessedImages result;

	if(image.empty()){
		throw std::runtime_error("Input image is empty");
	}

//Convert to grayscale
	cv::cvtColor(image, result.grayscale, cv::COLOR_BGR2GRAY);
	showOutput("Grayscaleimage", result.grayscale);

//Contrast enhancement
	cv::equalizeHist(result.grayscale, result.grayscale);
	showOutput("Contrast Enhanced", result.grayscale);

//Apply bilateral filter for noise reduction
	cv::Mat bilateralFiltered;
	cv::bilateralFilter(result.grayscale, bilateralFiltered, 9, 75,75);
	showOutput("Bilateral Enhanced", bilateralFiltered);

//Edge detection
	cv::Canny(bilateralFiltered,result.edgeDetected, 50, 150);
	showOutput("Edge detected", result.edgeDetected);

//Adaptive thresholding
	cv::adaptiveThreshold(result.edgeDetected, result.threshold,255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 11, 2);
	showOutput("Thresholded Image", result.threshold);

//Morphological Operations
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::morphologyEx(result.threshold, result.morphed, cv::MORPH_OPEN, kernel);
	cv::morphologyEx(result.morphed, result.morphed, cv::MORPH_CLOSE, kernel);
	showOutput("Morphed Image", result.morphed);

//Contour detection
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(result.morphed, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//Filter contours based on aspect ratio and area
for(const auto& contour : contours){
	cv::Rect boundingRect = cv::boundingRect(contour);
	double aspect_ratio = static_cast<double>(boundingRect.width) / boundingRect.height;
	if(aspect_ratio > 2 && aspect_ratio < 5 && cv::contourArea(contour) > 1000){
		result.plateContours.push_back(contour);
	}
}

//Draw filtered contours on the original image
cv::Mat contourImage = image.clone();
cv::drawContours(contourImage, result.plateContours, -1, cv::Scalar(0,255,0), 2);
showOutput("Potential License PLates", contourImage);

return result;
}
