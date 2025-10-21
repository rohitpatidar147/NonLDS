#include "IndexedBST.h"

Node* IndexedBST::search(double desiredKey) {
    Node* cur = root;
    while (cur != nullptr) {
        if (cur->key == desiredKey) {
            return cur; // Found exact match
        } 
        else if (desiredKey < cur->key) {
            cur = cur->left;  // Search left subtree
        } 
        else {
            cur = cur->right; // Search right subtree
        }
    }
    return nullptr; // Key not found
}

void IndexedBST::insert(Node* node) {
    if (!root) {
        root = node;  // If tree is empty, new node is root
        return;
    }

    Node* cur = root;
    while (cur) {
        if (node->key < cur->key) {
            cur->leftSize++;  // We're adding to the left, update leftSize

            if (!cur->left) {
                cur->left = node;
                node->parent = cur;
                return;
            }
            cur = cur->left;
        } 
        else {
            if (!cur->right) {
                cur->right = node;
                node->parent = cur;
                return;
            }
            cur = cur->right;
        }
    }
}

bool IndexedBST::remove(double key) {
    Node* cur = root;
    Node* parent = nullptr;

    // Track nodes along the path to adjust leftSize
    Node* path[1000];
    bool wentLeft[1000];
    int pathLen = 0;

    Node* tmp = root;
    while (tmp && tmp->key != key) {
        path[pathLen] = tmp;
        if (key < tmp->key) {
            wentLeft[pathLen] = true;
            tmp = tmp->left;
        } else {
            wentLeft[pathLen] = false;
            tmp = tmp->right;
        }
        pathLen++;
    }

    if (!tmp) return false; // Key not found

    // Decrease leftSize for nodes where we went left
    for (int i = 0; i < pathLen; i++)
        if (wentLeft[i]) path[i]->leftSize--;

    // Standard BST deletion
    while (cur) {
        if (cur->key == key) {
            // Case 1: Leaf node
            if (!cur->left && !cur->right) {
                if (!parent) root = nullptr;
                else if (parent->left == cur) parent->left = nullptr;
                else parent->right = nullptr;
                delete cur;
                return true;
            }
            // Case 2: Node with only left child
            else if (!cur->right) {
                if (!parent) root = cur->left;
                else if (parent->left == cur) parent->left = cur->left;
                else parent->right = cur->left;
                if (cur->left) cur->left->parent = parent;
                delete cur;
                return true;
            }
            // Case 3: Node with only right child
            else if (!cur->left) {
                if (!parent) root = cur->right;
                else if (parent->left == cur) parent->left = cur->right;
                else parent->right = cur->right;
                if (cur->right) cur->right->parent = parent;
                delete cur;
                return true;
            }
            // Case 4: Node with two children
            else {
                Node* succParent = cur;
                Node* succ = cur->right;

                // Find smallest node in right subtree
                while (succ->left) {
                    succParent = succ;
                    succ = succ->left;
                }

                cur->key = succ->key; // Copy successor's key

                // Remove successor node
                if (succParent->left == succ)
                    succParent->left = succ->right;
                else
                    succParent->right = succ->right;

                if (succ->right) succ->right->parent = succParent;

                delete succ;
                return true;
            }
        }
        parent = cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }
    return false;
}

Node* IndexedBST::at(int index) {
    Node* cur = root;
    while (cur != nullptr) {
        if (index == cur->leftSize)
            return cur;  // Found the node at this index
        else if (index < cur->leftSize)
            cur = cur->left; // Look in left subtree
        else {
            index = index - cur->leftSize - 1;
            cur = cur->right; // Look in right subtree
        }
    }
    return nullptr;
}
