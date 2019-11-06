#include "Statistic_Functions.h"
#include <filesystem>
#include <fstream>
#include <iostream>

uint32_t count_lines(std::filesystem::path filePath) {
	std::ifstream file(filePath);
	uint32_t lines = 0;
	
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filePath << std::endl;
		return lines;
	}



	return lines;
}