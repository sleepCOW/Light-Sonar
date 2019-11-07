#include "Statistic_Functions.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Result.h"

Lines count_lines(std::filesystem::path filePath) {
	std::ifstream file(filePath);
	std::string buffer;
	Lines count{ 0, 0 };
	
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filePath << std::endl;
		return count;
	}

	while (getline(file, buffer)) {
		if (buffer.size()) {
			count.lines++;
		}
		else {
			count.emptyLines++;
		}
	}

	return count;
}