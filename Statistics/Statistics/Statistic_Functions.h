#pragma once
#include <filesystem>
#include "Result.h"

Lines count_lines(std::filesystem::path file);

void scan_directory(std::filesystem::path directoryPath, Result& result);

void scan_file(std::filesystem::path filePath, Result& result);