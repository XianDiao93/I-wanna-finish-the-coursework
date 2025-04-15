#pragma once
#include <vector>
#include <string>

class FileManager {
public:
	static void writeIntsToFile(const std::string& filename, const std::vector<int>& vec);
	static void writeStringsToFile(const std::string& filename, const std::vector<std::string>& vec);
	static std::vector<int> readIntsFromFile(const std::string& filename);
	static std::vector<std::string> readStringsFromFile(const std::string& filename);
	static bool checkOrCreateFile(const std::string& filename);
};