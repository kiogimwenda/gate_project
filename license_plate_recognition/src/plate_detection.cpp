#include "plate_detection.hpp"

//load the pre-trained Haar Cascade for license plate detection
cv::CascadeClassifier plateCascade;

//Initialize the cascade classifier
bool initPlateCascade(const std::string& cascadeFilePath){
	return plateCascade.load(cascadeFilePath);

}

//Function to detect license plates in the image
std::vector<cv::Rect> detectPlates(const cv::Mat& inputImage){
	std::vector<cv::Rect> plates;
	//Check if the cascade classifier is loaded
	if(!plateCascade.empty()){
		plateCascade.detectMultiScale(inputImage, plates, 1.1, 10, 0, cv::Size(30,30));

	}
return plates;
}

//Function to draw detected plates on the image
cv::Mat drawDetectedPlates(const cv::Mat& inputImage, const std::vector<cv::Rect>& plates){

	cv::Mat outputImage = inputImage.clone();

	for(const auto& plate : plates){
	
		cv::rectangle(outputImage, plate, cv::Scalar(0, 255,0), 2);
	}

return outputImage;
}
