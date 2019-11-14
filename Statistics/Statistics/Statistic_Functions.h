#ifndef STATISTIC_FUNCTIONS_H
#define STATISTIC_FUNCTIONS_H

#include <filesystem>

#include "Result.h"

Lines countLines(std::filesystem::path file);

void scanDirectory(std::filesystem::path directoryPath, Result& result);

void scanFile(std::filesystem::path filePath, Result& result);

#endif // STATISTIC_FUNCTIONS_H