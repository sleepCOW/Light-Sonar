#pragma once
#include <filesystem>
#include "Result.h"

Lines count_lines(std::filesystem::path file);

void scan_directory(std::filesystem::path directoryPath, Result& result);