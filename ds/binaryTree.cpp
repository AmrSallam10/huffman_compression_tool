// File: binaryTree.cpp
// Implementation of template class binary search tree

#include <iostream>
#include <iomanip>
#include "binaryTree.h"
#include "Queuet.cpp"
using namespace std;

// Member functions ...

// constructor - create an empty tree
template <class keyType, class dataType>
binaryTree<keyType, dataType>::binaryTree() {
    root = NULL;
}

//____________ Public search __________________
// Searches for the item with same key as k
//  in a binary search tree.
// Pre : k is defined.
// Returns true if key is located,
//   otherwise, returns false.
template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::search(const keyType& k) const {
    return search2(root, k);
}  // end of public search

//____________ Private search __________________
// Searches for the item with same key as k
// in the subtree pointed to by aRoot. Called
// by public search.
// Pre : k and aRoot are defined.
// Returns true if key is located,
// otherwise, returns false.
template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::search2(NodePointer aRoot, const keyType& k) const {
    if (aRoot == NULL)
        return false;
    else if (k == aRoot->key)
        return true;
    else if (k < aRoot->key)
        return search2(aRoot->left, k);
    else
        return search2(aRoot->right, k);
}  // end of private search

//____________ Public retrieve __________________
// Searches for the item with same key as k
//  and retrieves data part if found
// Pre : k is defined.
// Returns true if key is located,
//   otherwise, returns false.
template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::retrieve(const keyType& k, dataType& d) const {
    return retrieve2(root, k, d);
}  // end of public retrieve

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::update(const keyType& k, const dataType& d) const {
    update2(root, k, d);
}  // end of public retrieve

//____________ Private retrieve __________________
// Searches for the item with same key as k
// in the subtree pointed to by aRoot and retrieves
// data part if key is found.Called by public retrieve.
// Pre : k and aRoot are defined.
// Returns true if key is located,
// otherwise, returns false.
template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::retrieve2(NodePointer aRoot, const keyType& k,
                                              dataType& d) const {
    if (aRoot == NULL)
        return false;
    else if (k == aRoot->key) {
        d = aRoot->data;
        return true;
    } else if (k < aRoot->key)
        return retrieve2(aRoot->left, k, d);
    else
        return retrieve2(aRoot->right, k, d);
}  // end of private retrieve

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::update2(NodePointer aRoot, const keyType& k,
                                            const dataType& d) const {
    if (aRoot == NULL)
        return;
    else if (k == aRoot->key) {
        aRoot->data = d;
    } else if (k < aRoot->key)
        update2(aRoot->left, k, d);
    else
        update2(aRoot->right, k, d);
}

//____________ Public insert __________________
// Inserts element into a binary search tree.
// Pre : key k is defined.
// Post: Inserts element if k is not in the tree.
// Returns true if the insertion is performed.
// If there is a node with the same key value
// as k, returns false.
template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::insert(const keyType& k, const dataType& d) {
    return insert2(root, k, d);
}  // end of public insert

//____________ Private insert __________________
// Inserts element in the tree pointed to by
// aRoot.Called by public insert.
// Pre : aRoot k and d are defined.
// Post: If a node with same key as k is found,
// returns false. If an empty tree is reached,
// inserts element as a leaf node and returns true.
template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::insert2(NodePointer& aRoot, const keyType& k,
                                            const dataType& d) {
    // Check for empty tree.
    if (aRoot == NULL) {  // Attach new node
        aRoot = new treeNode;
        aRoot->left = NULL;
        aRoot->right = NULL;
        aRoot->key = k;
        aRoot->data = d;
        return true;
    } else if (k == aRoot->key)
        return false;
    else if (k < aRoot->key)
        return insert2(aRoot->left, k, d);
    else
        return insert2(aRoot->right, k, d);
}  // end of private insert

//____________ Public empty __________________
// Check if tree is empty
// Pre : none
// Post: Returns true if tree is empty, false
// otherwise
template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::empty() const {
    return (root == NULL);
}  // end of empty

//____________ Public traverse__________________
// Traverses a binary search tree in key order.
// Pre : none
// Post: Each element of the tree is displayed.
// Elements are displayed in key order.
template <class keyType, class dataType>
void binaryTree<keyType, dataType>::traverse(vector<pair<keyType, dataType>>& output) const {
    traverse2(root, output);
}  // end of public traverse

//____________ Private traverse__________________
// Traverses the binary search tree pointed to
// by aRoot in key order. Called by traverse.
// Pre : aRoot is defined.
// Post: displays each node in key order.
template <class keyType, class dataType>
void binaryTree<keyType, dataType>::traverse2(NodePointer aRoot,
                                              vector<pair<keyType, dataType>>& output) const {
    if (aRoot != NULL) {  // recursive in-order traversal
        traverse2(aRoot->left, output);
        pair<keyType, dataType> nodePair = pair<keyType, dataType>(aRoot->key, aRoot->data);
        output.push_back(nodePair);
        // cout << aRoot->key << " " << aRoot->data << endl;
        traverse2(aRoot->right, output);
    }

}  // end of private traverse

template <class keyType, class dataType>
int binaryTree<keyType, dataType>::getNodeCount() const {
    return getNodeCount2(root);
}

template <class keyType, class dataType>
int binaryTree<keyType, dataType>::getNodeCount2(NodePointer aRoot) const {
    if (aRoot == NULL) {
        return 0;
    }

    return 1 + getNodeCount2(aRoot->left) + getNodeCount2(aRoot->right);
}

//____Public pre-order traversal (Iterative)______
template <class keyType, class dataType>
void binaryTree<keyType, dataType>::preorder(vector<dataType>& output) const {
    preorder2(root, output);
}

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::preorder2(NodePointer aRoot, vector<dataType>& output) const {
    if (aRoot != NULL) {  // recursive in-order traversal
        // cout << aRoot->key << " " << aRoot->data << endl;
        output.push_back(aRoot->data);
        preorder2(aRoot->left, output);
        preorder2(aRoot->right, output);
    }

}  // end of private traverse

//____Public Level-order traversal (Iterative)______
template <class keyType, class dataType>
void binaryTree<keyType, dataType>::levelorder(vector<dataType>& output) const {
    Queuet<NodePointer> q;
    NodePointer t = root;
    q.enqueue(t);
    while (!q.queueIsEmpty()) {
        q.dequeue(t);
        output.push_back(t->data);
        if (t->left != NULL) q.enqueue(t->left);
        if (t->right != NULL) q.enqueue(t->right);
    }
}

//____________ Public remove __________________
// Remove an element from the binary search tree
// Pre : k is defined.
// Post: if k is present, its node will be
// removed and tree will be modified
template <class keyType, class dataType>
void binaryTree<keyType, dataType>::remove(const keyType& k) {
    bool found;
    NodePointer x, parent;
    // Search for element and its parent
    parentSearch(k, found, x, parent);
    if (!found) {
        cout << "Item not in BST\n";
        return;
    }
    // else, element is found
    if ((x->left != NULL) && (x->right != NULL)) {  // Node has two children
        // Find inorder successor and its parent
        NodePointer xSucc = x->right;
        parent = x;
        while (xSucc->left != NULL)  // descend left
        {
            parent = xSucc;
            xSucc = xSucc->left;
        }
        // Move contents of xSucc to x and change x
        // to point to successor, which will be removed
        x->key = xSucc->key;
        x->data = xSucc->data;
        x = xSucc;
    }  // end if node has two children
    // Now, node has 0 or 1 child
    NodePointer subtree = x->left;  // subtree of x
    if (subtree == NULL) subtree = x->right;
    if (parent == NULL)
        root = subtree;          // remove root
    else if (parent->left == x)  // parent left child
        parent->left = subtree;
    else
        parent->right = subtree;  // right child
    delete x;
}  // end of public remove

//____________ Private parentSearch __________________
// Locate a node containing key k and its parent
// Pre : none.
// Post: locptr points to node containing k
// or is NULL if not found, and parent points to
// its parent. Used by remove
template <class keyType, class dataType>
void binaryTree<keyType, dataType>::parentSearch(const keyType& k, bool& found, NodePointer& locptr,
                                                 NodePointer& parent) const {
    locptr = root;
    parent = NULL;
    found = false;
    while (!found && locptr != NULL) {
        if (k < locptr->key)  // descend left
        {
            parent = locptr;
            locptr = locptr->left;
        } else if (locptr->key < k)  // descend right
        {
            parent = locptr;
            locptr = locptr->right;
        } else
            found = true;  // el found
    }  // end while
}  // end of private parentSearch
