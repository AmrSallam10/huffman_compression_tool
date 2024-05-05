#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdexcept>

#include "zipper.h"
#include "utils.cpp"

std::map<char, int> HuffmanCompression::buildFrequencyTable(const std::string& text) {
    std::map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }
    return freq;
}

Node* HuffmanCompression::buildHuffmanTree(const std::map<char, int>& freqTable) {

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    for (auto pair: freqTable) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {

        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    return pq.top();
}

std::unordered_map<char, std::string> HuffmanCompression::generateHuffmanCodes(Node* root) {
    std::unordered_map<char, std::string> huffmanCode;
    generateHuffmanCodesRec(root, "", huffmanCode);
    return huffmanCode;
}

void HuffmanCompression::generateHuffmanCodesRec(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode) {
    if (root == nullptr)
        return;

    // found a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->data] = str;
    }

    generateHuffmanCodesRec(root->left, str + "0", huffmanCode);
    generateHuffmanCodesRec(root->right, str + "1", huffmanCode);
}

std::vector<uint8_t> HuffmanCompression::encode(const std::string& text, const std::unordered_map<char, std::string>& huffmanCodes) {
    std::string str = "";
    for (char ch: text) {
        str += huffmanCodes.at(ch);
    }

    std::vector<uint8_t> encodedData;
    str_to_byte(str, encodedData);
    return encodedData;
}

std::string HuffmanCompression::decode(const std::string& encodedData,const std::unordered_map<char, std::string>& huffmanCodes) {
    std::string decodedText = "";
    std::string code = "";
    for (char ch: encodedData) {
        code += ch;
        for (auto pair: huffmanCodes) {
            if (pair.second == code) {
                decodedText += pair.first;
                code = "";
                break;
            }
        }
    }
    return decodedText;
}

void HuffmanCompression::writeToFile(const std::string& filename, const std::vector<uint8_t>& encodedData, const std::map<char, int>& freqTable) {
    try{
        auto outFile = openFileForWriting(filename);

        for (const auto& pair: freqTable) {
            std::string ch;
            if (pair.first == ' '){
                ch = '_';
            } else if (pair.first == '\n') {
                ch = "\\n";
            } else if (pair.first == '\r') {
                ch = "\\r";
            } else {
                ch = pair.first;
            }
            outFile << ch << " " << pair.second << '\n';
        }

        outFile << std::endl;
        for (uint8_t byte: encodedData) {
            outFile << byte;
        }
        outFile.close();
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("");
    }
}

std::pair<std::string, std::map<char, int>> HuffmanCompression::readFromFile(const std::string& filename ) {
    try {
        auto inFile = openFileForReading(filename);

        std::map<char, int> freqTable;
        std::string ch;
        int freq;
        std::string line;
        while (getline(inFile, line) && line != "") {
            std::istringstream iss(line);
            iss >> ch >> freq;
            ch = ch == "_" ? " " : ch;
            ch = ch == "\\n" ? "\n" : ch;
            ch = ch == "\\r" ? "\r" : ch;
            freqTable[ch[0]] = freq;
        }

        std::string encodedDataStr((std::istreambuf_iterator<char>(inFile)),
                                std::istreambuf_iterator<char>());
        std::vector<uint8_t> encodedDataBytes(encodedDataStr.begin(), encodedDataStr.end());
        encodedDataStr = byte_to_str(encodedDataBytes);

        inFile.close();
        return {encodedDataStr, freqTable};
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("");
    }
}

void HuffmanCompression::compress(const std::string& inputFilename, const std::string& outputFilename) {
    try{
        auto inFile = openFileForReading(inputFilename);

        std::string text((std::istreambuf_iterator<char>(inFile)),
                        std::istreambuf_iterator<char>());
        std::map<char, int> freqTable = buildFrequencyTable(text);
        Node* root = buildHuffmanTree(freqTable);
        std::unordered_map<char, std::string> huffmanCodes = generateHuffmanCodes(root);
        std::vector<uint8_t> encodedData = encode(text, huffmanCodes);
        writeToFile(outputFilename, encodedData, freqTable);

        inFile.close();
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("");
    }
}

void HuffmanCompression::decompress(const std::string& inputFilename, const std::string& outputFilename) {
    try{
        auto [encodedDataStr, freqTable] = readFromFile(inputFilename);
        Node* root = buildHuffmanTree(freqTable);
        std::unordered_map<char, std::string> huffmanCodes = generateHuffmanCodes(root);
        std::string decodedData = decode(encodedDataStr, huffmanCodes);
        auto outFile = openFileForWriting(outputFilename);
        outFile << decodedData;
        outFile.close();
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("");
    }
}
