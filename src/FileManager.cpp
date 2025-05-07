#include "header.h"
#include "FileManager.h"

#include <fstream>
#include <cstdio>
#include <sstream>
#include <regex>

void FileManager::writeIntsToFile(const std::string& filename, const std::vector<int>& vec)
{
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    for (int num : vec) {
        outFile << num << '\n';
    }

    outFile.close();
}

void FileManager::writeStringsToFile(const std::string& filename, const std::vector<std::string>& vec)
{
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    for (const std::string& str : vec) {
        outFile << str << '\n';
    }
    outFile.close();
}

std::vector<int> FileManager::readIntsFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    std::vector<int> vec;

    if (!inFile) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return vec;
    }

    int num;
    while (inFile >> num) {
        vec.push_back(num);
    }

    inFile.close();
    return vec;
}

std::vector<std::string> FileManager::readStringsFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    std::vector<std::string> vec;
    if (!inFile) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return vec;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        vec.push_back(line);
    }
    inFile.close();
    return vec;
}

bool FileManager::checkOrCreateFile(const std::string& filename)
{
    std::ifstream infile(filename);
    if (infile.good()) {
        infile.close();
        return true;
    }
    else {
        std::ofstream outfile(filename);
        if (!outfile) {
            std::cerr << "Cannot create file: " << filename << std::endl;
            return false;
        }
        outfile.close();
        return false;
    }
}

std::vector<std::vector<int>> FileManager::readMapFromFile(const std::string& filename, int rows, int cols)
{
    std::ifstream inFile(filename);
    std::vector<std::vector<int>> map(rows, std::vector<int>(cols));

    if (!inFile) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return map;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(inFile >> map[i][j])) {
                std::cerr << "Error reading map data at [" << i << "][" << j << "]" << std::endl;
                return map;
            }
        }
    }

    inFile.close();
    return map;
}

std::vector<Utilities::coordinate> FileManager::readSavesFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<Utilities::coordinate> saves;
    std::string line;

    if (std::getline(file, line))
    {
        std::regex coordRegex(R"(\((\d+),(\d+)\))");
        std::smatch match;
        std::string::const_iterator searchStart(line.cbegin());

        while (std::regex_search(searchStart, line.cend(), match, coordRegex))
        {
            int x = std::stoi(match[1]);
            int y = std::stoi(match[2]);
            saves.push_back({ x, y });
            searchStart = match.suffix().first;
        }
    }

    return saves;
}

std::vector<int> FileManager::readSavesTypeFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<int> types;
    std::string line;

    std::getline(file, line); // skip coordinates

    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        int value;
        while (iss >> value)
            types.push_back(value);
    }

    return types;
}

std::vector<Utilities::coordinate> FileManager::readObjectsFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<Utilities::coordinate> objects;
    std::string line;

    std::getline(file, line); // skip saves
    std::getline(file, line); // skip save types

    if (std::getline(file, line))
    {
        std::regex coordRegex(R"(\((\d+),(\d+)\))");
        std::smatch match;
        std::string::const_iterator searchStart(line.cbegin());

        while (std::regex_search(searchStart, line.cend(), match, coordRegex))
        {
            int x = std::stoi(match[1]);
            int y = std::stoi(match[2]);
            objects.push_back({ x, y });
            searchStart = match.suffix().first;
        }
    }

    return objects;
}

std::vector<int> FileManager::readObjectsTypeFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<int> types;
    std::string line;

    std::getline(file, line); // skip saves
    std::getline(file, line); // skip save types
    std::getline(file, line); // skip object coordinates

    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        int value;
        while (iss >> value)
            types.push_back(value);
    }

    return types;
}
