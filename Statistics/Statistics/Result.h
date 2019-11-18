#ifndef RESULT_H
#define RESULT_H

#include <iostream>
#include <set>
#include <filesystem>
#include <map>

#include "ModeEnum.h"

struct Lines {
	uint64_t lines = 0;
	uint64_t emptyLines = 0;

	const uint64_t getTotalLines(){ return lines + emptyLines; }
};

struct Statistic {
	Lines lines = { 0, 0 };
	uint64_t numFiles = 0;
};

class Result {

private:
	std::set<std::filesystem::path> extensions;
	std::map<std::filesystem::path, Statistic> stats;
	ResultMode mode;
public:
	Result();
	Result(std::set<std::filesystem::path>&& neededExtensions);

	std::map<std::filesystem::path, Statistic> getStats();

	void addExtension(const std::filesystem::path& extension);
	void incrementFiles(const std::filesystem::path& extension);
	void addLines(const std::filesystem::path& extension, uint64_t number);
	void addBlanks(const std::filesystem::path& extension, uint64_t number);

	bool operator==(std::filesystem::path extension);
};

std::ostream& operator<<(std::ostream& out, Result& r);

#endif // RESULT_H