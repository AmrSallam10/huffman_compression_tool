#include <iostream>
#include <fstream>
#include <vector>

#include "utils.h"

std::ifstream openFileForReading(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("");
    }
    return inFile;
}

std::ofstream openFileForWriting(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("");
    }
    return outFile;
}

void str_to_byte(std::string& str, std::vector<uint8_t>& bytes) {
    // pad the last byte with 0s if it is not a full byte
    uint8_t padding = 8 - str.size() % 8;
    for (int i = 0; i < padding; i++) {
        str += '0';
    }
    for (int i = 0; i < (int)str.size(); i += 8) {
        uint8_t byte = 0;
        for (int j = 0; j < 8; j++) {
            byte = (byte << 1) | (str[i + j] - '0');
        }
        bytes.push_back(byte);
    }
    // store the padding in the last byte
    bytes.push_back(padding);
}

std::string byte_to_str(const std::vector<uint8_t>& bytes) {
    std::string str = "";
    uint8_t padding = bytes.back();
    for (int i = 0; i < (int)bytes.size() - 1; i++) {
        for (int j = 7; j >= 0; j--) {
            str += ((bytes[i] >> j) & 1) + '0';
        }
    }
    // remove the padding
    str = str.substr(0, str.size() - padding);
    return str;
}

std::string getFilename(const std::string& path) {
    std::string inputFilename;
    std::cout << "Enter input file path: ";
    std::cin >> inputFilename;
    return inputFilename;
}

std::string extractOriginalFilename(const std::string& filename) {
    std::string originalFilename;
    size_t pos = filename.find_last_of(".");
    originalFilename = pos ? filename.substr(0, pos) : filename;
    pos = filename.find_last_of("_");
    originalFilename = pos ? originalFilename.substr(0, pos) : originalFilename;
    return originalFilename;
}