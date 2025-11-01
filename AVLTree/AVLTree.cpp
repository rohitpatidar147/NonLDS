#include "AVLTree.h"
#include <algorithm>

AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::deleteTree(Node* node) {
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

Node* AVLTree::findParentForInsert(Node* node) {
    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (node->key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return parent;
}

void AVLTree::insert(Node* node) {
    if (node == nullptr)
        return;

    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;

    if (root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* parent = findParentForInsert(node);
    bool goLeft = node->key < parent->key;
    setChild(parent, goLeft, node);

    rebalanceUpwards(parent);
}

void AVLTree::insertWithoutRebalance(Node* node) {
    if (node == nullptr)
        return;

    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;

    if (root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* parent = findParentForInsert(node);
    bool goLeft = node->key < parent->key;
    setChild(parent, goLeft, node);

    updateHeightPath(parent);
}

int AVLTree::getHeight() const {
    return root == nullptr ? -1 : root->height;
}

void AVLTree::updateHeight(Node* node) {
    if (node == nullptr)
        return;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;
    node->height = std::max(leftHeight, rightHeight) + 1;
}

int AVLTree::getBalance(Node* node) const {
    if (node == nullptr)
        return 0;

    int leftHeight = node->left ? node->left->height : -1;
    int rightHeight = node->right ? node->right->height : -1;
    return leftHeight - rightHeight;
}

bool AVLTree::setChild(Node* parent, bool isLeftChild, Node* child) {
    if (parent == nullptr)
        return false;

    Node*& target = isLeftChild ? parent->left : parent->right;
    target = child;

    if (child != nullptr)
        child->parent = parent;

    updateHeight(parent);
    return true;
}

bool AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild) {
    if (parent == nullptr)
        return false;

    if (parent->left == currentChild)
        return setChild(parent, true, newChild);
    if (parent->right == currentChild)
        return setChild(parent, false, newChild);
    return false;
}

void AVLTree::rotateLeft(Node* node) {
    if (node == nullptr || node->right == nullptr)
        return;

    Node* newRoot = node->right;
    Node* movedSubtree = newRoot->left;

    Node* parent = node->parent;
    if (parent != nullptr)
        replaceChild(parent, node, newRoot);
    else {
        root = newRoot;
        root->parent = nullptr;
    }

    setChild(newRoot, true, node);
    setChild(node, false, movedSubtree);

    updateHeight(node);
    updateHeight(newRoot);
}

void AVLTree::rotateRight(Node* node) {
    if (node == nullptr || node->left == nullptr)
        return;

    Node* newRoot = node->left;
    Node* movedSubtree = newRoot->right;

    Node* parent = node->parent;
    if (parent != nullptr)
        replaceChild(parent, node, newRoot);
    else {
        root = newRoot;
        root->parent = nullptr;
    }

    setChild(newRoot, false, node);
    setChild(node, true, movedSubtree);

    updateHeight(node);
    updateHeight(newRoot);
}

void AVLTree::rebalance(Node* node) {
    if (node == nullptr)
        return;

    updateHeight(node);
    int balance = getBalance(node);

    if (balance <= -2) {
        if (getBalance(node->right) > 0)
            rotateRight(node->right);
        rotateLeft(node);
    } else if (balance >= 2) {
        if (getBalance(node->left) < 0)
            rotateLeft(node->left);
        rotateRight(node);
    }
}

void AVLTree::rebalanceUpwards(Node* node) {
    for (Node* current = node; current != nullptr; current = current->parent)
        rebalance(current);
}

void AVLTree::updateHeightPath(Node* node) {
    for (Node* current = node; current != nullptr; current = current->parent)
        updateHeight(current);
}