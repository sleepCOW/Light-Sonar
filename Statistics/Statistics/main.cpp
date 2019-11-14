// Statistics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <chrono>
#include <set>
#include <vector>

#include "Statistic_Functions.h"
#include "ModeEnum.h"

int main(int argc, const char** argv) {
	namespace fs = std::filesystem;

	std::vector<fs::path> directories; // Nitpick: directories and files could be in one line
	std::vector<fs::path> files;
	std::set<fs::path> extensions;
	Result* result = nullptr;

	for (int i = 1; i < argc; ++i) {
		fs::path argument = { argv[i] };
		
		if (fs::is_directory(argument)) {
			directories.push_back(argument);
		}
		else if (fs::is_regular_file(argument)) {
			files.push_back(argument);
		}
		else {
			extensions.insert(argument);
		}
	}
	 
	if (extensions.size()) {
		result = new Result(move(extensions));
	}
	else {
		result = new Result();
	}
	
	auto t1 = std::chrono::high_resolution_clock::now();
	if (directories.size()) {
		for (auto& directory : directories) {
			try {
				scanDirectory(directory, *result);
			}
			catch (fs::filesystem_error & er) {
				std::cout << er.what() << std::endl;
			}
		}
	} else if (!files.size()) {
		try {
			scanDirectory(fs::current_path(), *result);
		}
		catch (fs::filesystem_error & er) {
			std::cout << er.what() << std::endl;
		}
	}

	for (auto& file : files) {
		result->addExtension(file.extension());
		scanFile(file, *result);
	}
	
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "Time used: " << duration << " ms" << std::endl;
	std::cout << *result;

	return 0;
}