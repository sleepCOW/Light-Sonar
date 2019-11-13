// Statistics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include <vector>
#include <filesystem>
#include <chrono>
#include "Statistic_Functions.h"
#include "ModeEnum.h"

int main(int argc, const char** argv) {
	namespace fs = std::filesystem;
	std::vector<fs::path> directories;
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
				scan_directory(directory, *result);
			}
			catch (fs::filesystem_error & er) {
				std::cout << er.what() << std::endl;
			}
		}
	} else if (!files.size()) {
		try {
			scan_directory(fs::current_path(), *result);
		}
		catch (fs::filesystem_error & er) {
			std::cout << er.what() << std::endl;
		}
	}

	for (auto& file : files) {
		result->addExtension(file.extension());
		scan_file(file, *result);
	}
	
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "Time used: " << duration << " ms" << std::endl;
	std::cout << *result;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
