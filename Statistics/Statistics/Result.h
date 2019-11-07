#pragma once
#include <set>
#include <string>
#include "ModeEnum.h"

struct Lines {
	uint32_t lines;
	uint32_t emptyLines;
};

class Result
{
private:
	std::set<std::string> extensions;
	uint32_t numFiles;
	uint32_t totalLines;
	Lines lines;
	ResultMode mode;
public:
	Result();
	Result(std::set<std::string>&& neededExtensions);

	void addExtension(std::string extension);
	void incrementFiles();
	void incrementLines();
	void incrementBlanks();

	bool operator==(std::string extension);
};

