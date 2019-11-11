#include <array>
#include "Result.h"
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

	if (stats.size()) {

		constexpr int extensionWidth = 20;
		constexpr int fileWidth = 15;
		constexpr int lineWidth = 15;
		constexpr int blankWidth = 15;
		constexpr int sumWidth = 15;
		constexpr int totalWidth = extensionWidth + fileWidth + lineWidth + blankWidth + sumWidth + COLUMNSIZE;

		auto print_break = [&totalWidth]
		{
			std::cout.width(totalWidth);
			std::cout.fill('-');
			std::cout << '-' << std::endl;
			std::cout.fill(' ');
		};
		auto print_headers = [&extensionWidth, &fileWidth, &lineWidth, &blankWidth, &sumWidth]
		{
			using table_t = std::array<std::string, COLUMNSIZE>;
			table_t headers{ {"Extensions", "Files", "Lines", "Blanks", "Total"} };
			auto& [extension, file, line, blank, total] = headers;
			std::cout.width(extensionWidth);
			std::cout << ("| " + extension) << '|';

			std::cout.width(fileWidth);
			std::cout << (' ' + file) << '|';

			std::cout.width(lineWidth);
			std::cout << (' ' + line) << '|';

			std::cout.width(blankWidth);
			std::cout << (' ' + blank) << '|';

			std::cout.width(sumWidth);
			std::cout << (' ' + total) << '|';

			std::cout << '\n';
		};

		std::cout.setf(std::ios::left, std::ios::adjustfield);
		print_break();
		print_headers();
		print_break();
		for (auto& it : stats) {
			out << "Extension: " << it.first << " Lines: " << it.second.lines.lines << " Blanks: " 
				<< it.second.lines.emptyLines << " Files : " << it.second.numFiles << std::endl;
		}
	}
	else {

	}

	return out;
}
