#include <iostream>
#include "preprocessing.hpp"
#include "plate_detection.hpp"

int main(){

	//Initialize the plate cascade
	std::string cascadeFilePath = "haarcascade_russian_plate_number.xml";
	if(!initPlateCascade(cascadeFilePath)){
		std::cerr << "Failed to load plate cascade file: " << cascadeFilePath << std::endl;
		return -1;
	}

//Load an Image from file
	cv::Mat inputImage = cv::imread("sample2.jpg");

	if (inputImage.empty()){
		std::cerr << "Failed to load image" << std::endl;
		return -1;
	}

//preprocess the image
	cv::Mat processedImage = preprocessImage(inputImage);

//Detect plates
	std::vector<cv::Rect> plates = detectPlates(processedImage);
	if(!plates.empty()){
	
		std::cout << "plates detected: " << plates.size() << std::endl;
		cv::Mat outputImage = drawDetectedPlates(inputImage, plates);
		cv::imshow("Detected Plates", outputImage);
	}else{
		std::cout << "No plates detected" << std::endl;
	}

	cv::waitKey(0);
	return 0;
}
