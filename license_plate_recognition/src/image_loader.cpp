#include "image_loader.hpp"
#include <stdexcept>
#include <curl/curl.h>

//Function to write data fetched by curl into a buffer
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


cv::Mat loadImageFromWeb(const std::string& url, const std::string& username, const std::string& password){
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();

	if (curl){
		std::string userpwd = username + ":" + password;//concatinate username and password
		std::cout << "URL:" << url << std::endl;
		std::cout << "Userpwd:" << userpwd << std::endl;

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	res = curl_easy_perform(curl);
	if(res != CURLE_OK){
		curl_easy_cleanup(curl);
		throw std::runtime_error("curl_easy-perform()failed" + std::string(curl_easy_strerror(res)));

	}

	curl_easy_cleanup(curl);
	}
	else{
		throw std::runtime_error("Could not initialize curl");	
	}
	std::vector<char> data(readBuffer.begin(), readBuffer.end());
	cv::Mat frame = cv::imdecode(data, cv::IMREAD_COLOR);

	if(frame.empty()){
		throw std::runtime_error("Could not decode image from the web stream");
	}

return frame;
}

