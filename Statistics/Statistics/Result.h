#pragma once
#include <set>
#include <filesystem>
#include <map>
#include <iostream>
#include "ModeEnum.h"

struct Lines {
	uint32_t lines = 0;
	uint32_t emptyLines = 0;

	uint32_t get_total_lines(){ return lines + emptyLines; }
};

struct Statistic {
	Lines lines = { 0, 0 };
	uint32_t numFiles = 0;
};

class Result
{
private:
	std::set<std::filesystem::path> extensions;
	std::map<std::filesystem::path, Statistic> stats;
	ResultMode mode;
public:
	Result();
	Result(std::set<std::filesystem::path>&& neededExtensions);

	std::map<std::filesystem::path, Statistic> getStats();

	void addExtension(std::filesystem::path& extension);
	void incrementFiles(std::filesystem::path& extension);
	void addLines(std::filesystem::path& extension, uint32_t number);
	void addBlanks(std::filesystem::path& extension, uint32_t number);

	bool operator==(std::filesystem::path extension);
};

std::ostream& operator<<(std::ostream& out, Result& r);