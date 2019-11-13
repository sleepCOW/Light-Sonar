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
	AppMode mode = AppMode(argc);
	std::vector<fs::path> directorys;
	std::vector<fs::path> files;

	 
	if (mode == AppMode::CURRENT_FOLDER) {
		directoryPath = fs::current_path();
	}
	else if (mode == AppMode::GIVEN_FOLDER) {
		directoryPath = argv[1];
	}
	else {
		std::set<fs::path> extensions;
		directoryPath = argv[1];
		for (int i = 2; i < argc; ++i) {
			extensions.insert(argv[i]);
		}
		
		Result result(move(extensions));
		
		scan_directory(directoryPath, result);
		std::cout << result;

		return 0;
	}

	Result result;

	auto t1 = std::chrono::high_resolution_clock::now();
	try {
		scan_directory(directoryPath, result);
	}
	catch (fs::filesystem_error & er) {
		std::cout << er.what() << std::endl;
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "Time used: " << duration << " ms" << std::endl;
	std::cout << result;

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
