#include "binaryTree.cpp"
#include <string>
#include <vector>

struct Node {
    char data;
    int freq;
    Node* left, * right;
    Node(char data, int freq, Node* left = nullptr, Node* right = nullptr)
        : data(data), freq(freq), left(left), right(right) {}
};

class HuffmanCompression {
public:
    void compress(const std::string& inputFilename, const std::string& outputFilename);
    void decompress(const std::string& inputFilename, const std::string& outputFilename);

private:
    binaryTree<char, int> buildFrequencyTable(const std::string& text);
    Node* buildHuffmanTree(binaryTree<char, int>& freqTable);
    binaryTree<char, std::string> generateHuffmanCodes(Node* root);
    void generateHuffmanCodesRec(Node* root, std::string str,
        binaryTree<char, std::string>& huffmanCode);
    std::vector<uint8_t> encode(const std::string& text,
        binaryTree<char, std::string>& huffmanCodes);
    std::string decode(const std::string& encodedData,
        binaryTree<char, std::string>& huffmanCodest);
    void writeToFile(const std::string& filename, const std::vector<uint8_t>& encodedData,
        binaryTree<char, int>& freqTable);
    std::pair<std::string, binaryTree<char, int>> readFromFile(const std::string& filename);
};