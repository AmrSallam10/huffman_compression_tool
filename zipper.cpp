#include "zipper.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "ds/PQ.cpp"
#include "utils.h"

bool comp(Node* l, Node* r) { return l->freq > r->freq; }

struct compareee {
    bool operator()(Node* l, Node* r) { return l->freq > r->freq; }
};

binaryTree<char, int> HuffmanCompression::buildFrequencyTable(const std::string& text) {
    binaryTree<char, int> freq;
    for (char ch : text) {
        int data;

        if (freq.retrieve(ch, data)) {
            freq.update(ch, data + 1);
        } else {
            freq.insert(ch, 1);
        }
    }
    return freq;
}

Node* HuffmanCompression::buildHuffmanTree(binaryTree<char, int>& freqTable) {
    PQ<Node*> pq(100000, comp, new Node(NULL, -1));
    std::vector<std::pair<char, int>> pairs;
    freqTable.traverse(pairs);
    // std::priority_queue<Node*, std::vector<Node*>, comp> pq;s
    for (auto pair : pairs) {
        pq.insert(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.remove();
        Node* right = pq.remove();
        int sum = left->freq + right->freq;
        pq.insert(new Node('\0', sum, left, right));
    }
    return pq.remove();
}

binaryTree<char, std::string> HuffmanCompression::generateHuffmanCodes(Node* root) {
    binaryTree<char, std::string> huffmanCodes;
    generateHuffmanCodesRec(root, "", huffmanCodes);
    return huffmanCodes;
}

void HuffmanCompression::generateHuffmanCodesRec(Node* root, std::string str,
                                                 binaryTree<char, std::string>& huffmanCodes) {
    if (root == nullptr) return;
    // leaf node
    if (!root->left && !root->right) {
        std::string data;
        if (huffmanCodes.retrieve(root->data, data)) {
            huffmanCodes.update(root->data, str);
        }
        huffmanCodes.insert(root->data, str);
    }
    generateHuffmanCodesRec(root->left, str + "0", huffmanCodes);
    generateHuffmanCodesRec(root->right, str + "1", huffmanCodes);
}

std::vector<uint8_t> HuffmanCompression::encode(const std::string& text,
                                                binaryTree<char, std::string>& huffmanCodes) {
    std::string str = "";
    for (char ch : text) {
        std::string data;
        huffmanCodes.retrieve(ch, data);
        str += data;
    }
    std::vector<uint8_t> encodedData;
    str_to_byte(str, encodedData);
    return encodedData;
}

std::string HuffmanCompression::decode(const std::string& encodedData,
                                       binaryTree<char, std::string>& huffmanCodes) {
    std::string decodedText = "";
    std::string code = "";
    for (char ch : encodedData) {
        code += ch;
        std::vector<std::pair<char, std::string>> pairs;
        huffmanCodes.traverse(pairs);
        for (auto pair : pairs) {
            if (pair.second == code) {
                decodedText += pair.first;
                code = "";
                break;
            }
        }
    }
    return decodedText;
}

void HuffmanCompression::writeToFile(const std::string& filename,
                                     const std::vector<uint8_t>& encodedData,
                                     binaryTree<char, int>& freqTable) {
    try {
        auto outFile = openFileForWriting(filename);
        std::vector<std::pair<char, int>> pairs;
        freqTable.traverse(pairs);

        for (const auto& pair : pairs) {
            std::string ch;
            if (pair.first == ' ') {
                ch = "_";
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
        for (uint8_t byte : encodedData) {
            outFile << byte;
        }
        outFile.close();
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("");
    }
}

std::pair<std::string, binaryTree<char, int>> HuffmanCompression::readFromFile(
    const std::string& filename) {
    try {
        auto inFile = openFileForReading(filename);
        binaryTree<char, int> freqTable;
        std::string ch;
        int freq;
        std::string line;
        while (getline(inFile, line) && line != "") {
            std::istringstream iss(line);
            iss >> ch >> freq;
            ch = ch == "_" ? " " : ch;
            ch = ch == "\\n" ? "\n" : ch;
            ch = ch == "\\r" ? "\r" : ch;
            int data;
            if (freqTable.retrieve(ch[0], data)) {
                freqTable.update(ch[0], freq);
            } else {
                freqTable.insert(ch[0], freq);
            }
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

void HuffmanCompression::compress(const std::string& inputFilename,
                                  const std::string& outputFilename) {
    try {
        auto inFile = openFileForReading(inputFilename);
        std::string text((std::istreambuf_iterator<char>(inFile)),
                         std::istreambuf_iterator<char>());
        binaryTree<char, int> freqTable = buildFrequencyTable(text);
        Node* root = buildHuffmanTree(freqTable);
        binaryTree<char, std::string> huffmanCodes = generateHuffmanCodes(root);
        std::vector<uint8_t> encodedData = encode(text, huffmanCodes);
        writeToFile(outputFilename, encodedData, freqTable);
        inFile.close();
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("");
    }
}

void HuffmanCompression::decompress(const std::string& inputFilename,
                                    const std::string& outputFilename) {
    try {
        std::pair<std::string, binaryTree<char, int>> fileoutput = readFromFile(inputFilename);
        std::string encodedDataStr = fileoutput.first;
        binaryTree<char, int> freqTable = fileoutput.second;
        Node* root = buildHuffmanTree(freqTable);
        binaryTree<char, std::string> huffmanCodes = generateHuffmanCodes(root);
        std::string decodedData = decode(encodedDataStr, huffmanCodes);
        auto outFile = openFileForWriting(outputFilename);
        outFile << decodedData;
        outFile.close();
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("");
    }
}