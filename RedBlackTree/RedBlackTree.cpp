#include "RedBlackTree.h"
#include <algorithm>
#include <cstring>

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

void RedBlackTree::deleteTree(RBTNode* node) {
    // Recursively remove all nodes in the BST (used by the destructor). 
    // By doing this recursively, we start removing nodes from the bottom
    // of the tree (leaf nodes), which is most efficiently because it does
    // not require replacing any nodes.

    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void RedBlackTree::insert(RBTNode* node) {
    BSTInsert(node);
    node->red = true;
    RBTreeBalance(node);
}

void RedBlackTree::BSTInsert(RBTNode* node) {
    if (node == nullptr)
        return;

    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;

    if (root == nullptr) {
        root = node;
        return;
    }

    RBTNode* current = root;
    RBTNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (node->key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (node->key < parent->key)
        RBTreeSetChild(parent, "left", node);
    else
        RBTreeSetChild(parent, "right", node);
}

void RedBlackTree::RBTreeBalance(RBTNode* node) {
    if (node->parent == nullptr) {
        node->red = false;
        root = node;
        return;
    }

    if (node->parent->red == false)
        return;

    RBTNode* parent = node->parent;
    RBTNode* grandparent = RBTreeGetGrandparent(node);
    
    if (grandparent == nullptr)
        return;
    
    RBTNode* uncle = RBTreeGetUncle(node);

    if (uncle != nullptr && uncle->red == true) {
        parent->red = false;
        uncle->red = false;
        grandparent->red = true;
        RBTreeBalance(grandparent);
        return;
    }

    // Handle the "inside" cases that require an initial rotation
    if (node == parent->right && parent == grandparent->left) {
        RBTreeRotateLeft(parent);
        // After rotation, node and parent have swapped roles
        node = parent;
        parent = node->parent;
    }
    else if (node == parent->left && parent == grandparent->right) {
        RBTreeRotateRight(parent);
        // After rotation, node and parent have swapped roles
        node = parent;
        parent = node->parent;
    }

    // Now handle the "outside" case
    parent = node->parent;
    grandparent = RBTreeGetGrandparent(node);
    
    if (grandparent == nullptr) {
        // Parent became root, ensure it's black
        if (parent != nullptr)
            parent->red = false;
        return;
    }

    parent->red = false;
    grandparent->red = true;

    if (node == parent->left)
        RBTreeRotateRight(grandparent);
    else
        RBTreeRotateLeft(grandparent);
    
    // Ensure root is always black
    if (root != nullptr)
        root->red = false;
}

RBTNode* RedBlackTree::RBTreeGetGrandparent(RBTNode* node) const {
    if (node->parent == nullptr)
        return nullptr;
    return node->parent->parent;
}

RBTNode* RedBlackTree::RBTreeGetUncle(RBTNode* node) const {
    RBTNode* grandparent = nullptr;
    if (node->parent != nullptr)
        grandparent = node->parent->parent;
    
    if (grandparent == nullptr)
        return nullptr;
    
    if (grandparent->left == node->parent)
        return grandparent->right;
    else
        return grandparent->left;
}

void RedBlackTree::RBTreeRotateLeft(RBTNode* node) {
    if (node == nullptr || node->right == nullptr)
        return;

    RBTNode* rightLeftChild = node->right->left;

    if (node->parent != nullptr)
        RBTreeReplaceChild(node->parent, node, node->right);
    else {
        root = node->right;
        root->parent = nullptr;
    }

    RBTreeSetChild(node->right, "left", node);
    RBTreeSetChild(node, "right", rightLeftChild);
}

void RedBlackTree::RBTreeRotateRight(RBTNode* node) {
    if (node == nullptr || node->left == nullptr)
        return;

    RBTNode* leftRightChild = node->left->right;

    if (node->parent != nullptr)
        RBTreeReplaceChild(node->parent, node, node->left);
    else {
        root = node->left;
        root->parent = nullptr;
    }

    RBTreeSetChild(node->left, "right", node);
    RBTreeSetChild(node, "left", leftRightChild);
}

bool RedBlackTree::RBTreeSetChild(RBTNode* parent, const char* whichChild, RBTNode* child) {
    if (strcmp(whichChild, "left") != 0 && strcmp(whichChild, "right") != 0)
        return false;

    if (strcmp(whichChild, "left") == 0)
        parent->left = child;
    else
        parent->right = child;

    if (child != nullptr)
        child->parent = parent;

    return true;
}

bool RedBlackTree::RBTreeReplaceChild(RBTNode* parent, RBTNode* currentChild, RBTNode* newChild) {
    if (parent->left == currentChild)
        return RBTreeSetChild(parent, "left", newChild);
    else if (parent->right == currentChild)
        return RBTreeSetChild(parent, "right", newChild);
    
    return false;
}

int RedBlackTree::getHeight() const {
    return getHeightHelper(root);
}

int RedBlackTree::getHeightHelper(RBTNode* node) const {
    if (node == nullptr)
        return -1;
    
    int leftHeight = getHeightHelper(node->left);
    int rightHeight = getHeightHelper(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}
