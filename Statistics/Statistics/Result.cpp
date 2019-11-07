#include "Result.h"
#include "ModeEnum.h"

Result::Result()
{
	numFiles = 0;
	totalLines = 0;
	lines = { 0, 0 };
	mode = ResultMode::ALL_EXTENSIONS;
}

Result::Result(std::set<std::string>&& neededExtensions)
{
	extensions = neededExtensions;
	numFiles = 0;
	totalLines = 0;
	lines = { 0, 0 };
	mode = ResultMode::GIVEN_EXTENSIONS;
}

void Result::addExtension(std::string extension)
{
	extensions.insert(extension);
}

void Result::incrementFiles()
{
	numFiles++;
}

void Result::incrementLines()
{
	lines.lines++;
}

void Result::incrementBlanks()
{
	lines.emptyLines++;
}

bool Result::operator==(std::string extension)
{
	if (mode == ResultMode::ALL_EXTENSIONS) {
		addExtension(extension);
		return true;
	}
	else if (auto found = extensions.find(extension); found != extensions.end()) {
		return true;
	}
	return false;
}
