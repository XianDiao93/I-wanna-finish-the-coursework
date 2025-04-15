#include "header.h"
#include "FileManager.h"

#include <fstream>
#include <cstdio>

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
