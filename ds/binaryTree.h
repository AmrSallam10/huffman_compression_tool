// FILE: binaryTree.h
// DEFINITION OF TEMPLATE CLASS BINARY SEARCH
// TREE

#ifndef BIN_TREE_H
#define BIN_TREE_H
#include <queue>
#include <string>
using namespace std;

// Specification of the class

template <class keyType, class dataType>

class binaryTree {
   public:
    // Public Member functions ...
    // CREATE AN EMPTY TREE
    binaryTree();

    // INSERT AN ELEMENT INTO THE TREE
    bool insert(const keyType&, const dataType&);

    // CHECK IF THE TREE IS EMPTY
    bool empty() const;

    // SEARCH FOR A KEY IN THE TREE
    bool search(const keyType&) const;

    // RETRIEVE DATA FOR A GIVEN KEY
    bool retrieve(const keyType&, dataType&) const;

    void update(const keyType&, const dataType&) const;

    // TRAVERSE A TREE
    void traverse(vector<pair<keyType, dataType>>&) const;

    int getNodeCount() const;

    // Iterative Pre-order Traversal
    void preorder(vector<dataType>& output) const;

    // Iterative Level-order Traversal
    void levelorder(vector<dataType>& output) const;

    // REMOVE AN ELEMENT FROM THE TREE
    void remove(const keyType&);

   private:
    // Node Class
    class treeNode {
       public:
        keyType key;      // key
        dataType data;    // Data
        treeNode* left;   // left subtree
        treeNode* right;  // right subtree
    };  // end of class treeNode declaration

    typedef treeNode* NodePointer;
    // Data member ....
    NodePointer root;

    // Private Member functions ...

    // Searches a subtree for a key
    bool search2(NodePointer, const keyType&) const;

    // Searches a subtree for a key and retrieves data
    bool retrieve2(NodePointer, const keyType&, dataType&) const;

    void update2(NodePointer, const keyType&, const dataType&) const;

    // Inserts an item in a subtree
    bool insert2(NodePointer&, const keyType&, const dataType&);

    // Traverses a subtree
    void traverse2(NodePointer, vector<pair<keyType, dataType>>&) const;

    void preorder2(NodePointer, vector<dataType>& output) const;

    int getNodeCount2(NodePointer) const;

    // LOCATE A NODE CONTAINING ELEMENT AND ITS PARENT
    void parentSearch(const keyType& k, bool& found, NodePointer& locptr,
                      NodePointer& parent) const;
};

#endif  // BIN_TREE_H