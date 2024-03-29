#include "Result.h"

#include <array>
#include <string>

#include "ModeEnum.h"

#define COLUMNSIZE 5

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


void Result::addExtension(const std::filesystem::path& extension)
{
	extensions.insert(extension);
}

void Result::incrementFiles(const std::filesystem::path& extension)
{
	stats[extension].numFiles += 1;
}

void Result::addLines(const std::filesystem::path& extension, uint64_t number)
{
	stats[extension].lines.lines += number;
}

void Result::addBlanks(const std::filesystem::path& extension, uint64_t number)
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

	if (stats.size()) {

		Statistic sum;
		constexpr int extensionWidth = 15;
		constexpr int fileWidth = 15;
		constexpr int lineWidth = 15;
		constexpr int blankWidth = 15;
		constexpr int sumWidth = 15;
		constexpr int totalWidth = extensionWidth + fileWidth + lineWidth + blankWidth + sumWidth + COLUMNSIZE;

		auto print_break = [&totalWidth, &out]
		{
			out.width(totalWidth);
			out.fill('-');
			out << '-' << std::endl;
			out.fill(' ');
		};
		auto print_headers = [&extensionWidth, &fileWidth, &lineWidth, &blankWidth, &sumWidth, &out]
		{
			using table_t = std::array<std::string, COLUMNSIZE>;
			table_t headers{ {"Extensions", "Files", "Lines", "Blanks", "Total"} };
			auto& [extension, file, line, blank, total] = headers;
			out.width(extensionWidth);
			out << ("| " + extension) << '|';

			out.width(fileWidth);
			out << (' ' + file) << '|';

			out.width(lineWidth);
			out << (' ' + line) << '|';

			out.width(blankWidth);
			out << (' ' + blank) << '|';

			out.width(sumWidth);
			out << (' ' + total) << '|' << std::endl;
		};

		std::cout.setf(std::ios::left, std::ios::adjustfield);
		print_break();
		print_headers();
		print_break();

		for (auto& it : stats) {
			out.width(extensionWidth);
			out << ("| " + it.first.string()) << '|';

			out.width(fileWidth);
			out << (' ' + std::to_string(it.second.numFiles)) << '|';

			out.width(lineWidth);
			out << (' ' + std::to_string(it.second.lines.lines)) << '|';

			out.width(blankWidth);
			out << (' ' + std::to_string(it.second.lines.emptyLines)) << '|';

			out.width(sumWidth);
			out << (' ' + std::to_string(it.second.lines.getTotalLines())) << '|' << std::endl;

			print_break();

			sum.numFiles += it.second.numFiles;
			sum.lines.lines += it.second.lines.lines;
			sum.lines.emptyLines += it.second.lines.emptyLines;
		}

		out.width(extensionWidth);
		out << ("| SUM") << '|';

		out.width(fileWidth);
		out << (' ' + std::to_string(sum.numFiles)) << '|';

		out.width(lineWidth);
		out << (' ' + std::to_string(sum.lines.lines)) << '|';

		out.width(blankWidth);
		out << (' ' + std::to_string(sum.lines.emptyLines)) << '|';

		out.width(sumWidth);
		out << (' ' + std::to_string(sum.lines.getTotalLines())) << '|' << std::endl;

		print_break();
	}
	else {
		out << "No needed files have been found :<" << std::endl;
	}

	return out;
}
