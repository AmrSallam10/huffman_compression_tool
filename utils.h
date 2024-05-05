#pragma once
#include <fstream>
#include <string>
#include <vector>

std::ifstream openFileForReading(const std::string& filename);
std::ofstream openFileForWriting(const std::string& filename);
void str_to_byte(std::string& str, std::vector<uint8_t>& bytes);
std::string byte_to_str(const std::vector<uint8_t>& bytes);
std::string getFilename(const std::string& path);
std::string extractOriginalFilename(const std::string& filename);