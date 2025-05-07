#pragma once
#include <vector>
#include <string>
#include "Utilities.h"

class FileManager {
public:
	static void writeIntsToFile(const std::string& filename, const std::vector<int>& vec);
	static void writeStringsToFile(const std::string& filename, const std::vector<std::string>& vec);
	static std::vector<int> readIntsFromFile(const std::string& filename);
	static std::vector<std::string> readStringsFromFile(const std::string& filename);
	static bool checkOrCreateFile(const std::string& filename);
	static std::vector<std::vector<int>> readMapFromFile(const std::string& filename, int rows, int cols);
	// static bool checkFile(const std::string& filename);
	static std::vector<Utilities::coordinate> readSavesFromFile(const std::string& filename);
	static std::vector<int> readSavesTypeFromFile(const std::string& filename);
	static std::vector<Utilities::coordinate> readObjectsFromFile(const std::string& filename);
	static std::vector<int> readObjectsTypeFromFile(const std::string& filename);
};