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

void scan_directory(std::filesystem::path directoryPath, Result& result) {
	for (auto& iter : std::filesystem::directory_iterator(directoryPath)) {
		if (iter.is_directory()) {
			try {
				scan_directory(iter.path(), result);
			}
			catch (std::filesystem::filesystem_error & er) {
				std::cout << er.what() << std::endl;
			}
		}
		else {
			scan_file(iter.path(), result);
		}
	}
}

void scan_file(std::filesystem::path filePath, Result& result) {
	if (auto extension = filePath.extension(); result == extension) {
		auto [lines, blanks] = count_lines(filePath);
		result.addLines(extension, lines);
		result.addBlanks(extension, blanks);
		result.incrementFiles(extension);
	}
}
