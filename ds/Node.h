#pragma once
class Node {
   public:
    Node(char data, int freq, Node* left = nullptr, Node* right = nullptr)
        : data(data), freq(freq), left(left), right(right) {}

    int getFreq() const { return freq; }
    char getData() const { return data; }
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }

    void setLeft(Node* left) { this->left = left; }
    void setRight(Node* right) { this->right = right; }

   private:
    char data;
    int freq;
    Node *left, *right;
};

struct nodeComp {
    bool operator()(Node* l, Node* r) { return l->getFreq() > r->getFreq(); }
};