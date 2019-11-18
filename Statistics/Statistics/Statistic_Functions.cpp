#include "Statistic_Functions.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Result.h"

Lines countLines(std::filesystem::path filePath) {
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

void scanDirectory(std::filesystem::path directoryPath, Result& result) {
	for (auto& iter : std::filesystem::directory_iterator(directoryPath)) {
		if (iter.is_directory()) {
			try {
				scanDirectory(iter.path(), result);
			}
			catch (std::filesystem::filesystem_error & er) {
				std::cout << er.what() << std::endl;
			}
		}
		else {
			scanFile(iter.path(), result);
		}
	}
}

void scanFile(std::filesystem::path filePath, Result& result) {
	if (auto extension = filePath.extension(); result == extension) {
		auto [lines, blanks] = countLines(filePath);
		result.addLines(extension, lines);
		result.addBlanks(extension, blanks);
		result.incrementFiles(extension);
	}
}
