#include "Result.h"
#include "ModeEnum.h"

Result::Result()
{
	mode = ResultMode::ALL_EXTENSIONS;
}

Result::Result(std::set<std::filesystem::path>&& neededExtensions)
{
	extensions = neededExtensions;
	mode = ResultMode::GIVEN_EXTENSIONS;
}

std::map<std::filesystem::path, Statistic> Result::getStats()
{
	return stats;
}


void Result::addExtension(std::filesystem::path& extension)
{
	extensions.insert(extension);
}

void Result::incrementFiles(std::filesystem::path& extension)
{
	stats[extension].numFiles += 1;
}

void Result::addLines(std::filesystem::path& extension, uint32_t number)
{
	stats[extension].lines.lines += number;
}

void Result::addBlanks(std::filesystem::path& extension, uint32_t number)
{
	stats[extension].lines.emptyLines += number;
}

bool Result::operator==(std::filesystem::path extension)
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

std::ostream& operator<<(std::ostream& out, Result& r)
{
	std::map<std::filesystem::path, Statistic> stats = r.getStats();

	for (auto& it : stats) {
		out << "Extension: " << it.first << " Lines: " << it.second.lines.lines << " Blanks: " 
			<< it.second.lines.emptyLines << " Files : " << it.second.numFiles << std::endl;
	}

	return out;
}
