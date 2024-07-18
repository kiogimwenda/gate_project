#include "preprocessing.hpp"
#include <iostream>

int main(){

cv::Mat image = cv::imread("sample2.jpg");

if(image.empty()){
	std::cerr << "Could not read image." << std::endl;
	return -1;
}

cv::Mat preprocessedImage = preprocessImage(image);

if(!preprocessedImage.empty()){
	std::cout << "Image preprocessed successfully" << std::endl;
	cv::imshow("preprocessed Image", preprocessedImage);
	cv::waitKey(0);
}else{
	std::cerr << "Failed to process the Image." << std::endl;
}

return 0;
}
