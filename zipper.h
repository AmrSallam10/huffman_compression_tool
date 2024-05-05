#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include <string>

struct Node {
    char data;
    int freq;
    Node *left, *right;
    Node(char data, int freq, Node* left = nullptr, Node* right = nullptr)
        : data(data), freq(freq), left(left), right(right) {}
};

struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

class HuffmanCompression {
public:
    void compress(const std::string& inputFilename, const std::string& outputFilename);
    void decompress(const std::string& inputFilename, const std::string& outputFilename);

private:
    std::map<char, int> buildFrequencyTable(const std::string& text);
    Node* buildHuffmanTree(const std::map<char, int>& freqTable);
    std::unordered_map<char, std::string> generateHuffmanCodes(Node* root);
    void generateHuffmanCodesRec(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode);
    std::vector<uint8_t> encode(const std::string& text, const std::unordered_map<char, std::string>& huffmanCodes);
    std::string decode(const std::string& encodedData, const std::unordered_map<char, std::string>& huffmanCodest);
    void writeToFile(const std::string& filename, const std::vector<uint8_t>& encodedData, const std::map<char, int>& freqTable);
    std::pair<std::string, std::map<char, int>> readFromFile(const std::string& filename);
};