#ifndef AVLTREE_H
#define AVLTREE_H

// A node in the AVL tree that stores a double
class Node {
public:
    double key;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(double nodeKey) {
        key = nodeKey;
    }
};

// An AVL tree that can insert with and without rebalancing
class AVLTree
{
public:
    AVLTree() {};
    ~AVLTree();

    // Insert a new element and rebalance the tree
    void insert(Node* node);
    // Insert a new element without rebalancing the tree
    void insertWithoutRebalance(Node* node);

    int getHeight() const;

private:
    Node* root = nullptr;
    void deleteTree(Node* node);
    Node* findParentForInsert(Node* node);
    void updateHeight(Node* node);
    int getBalance(Node* node) const;
    bool setChild(Node* parent, bool isLeftChild, Node* child);
    bool replaceChild(Node* parent, Node* currentChild, Node* newChild);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void rebalance(Node* node);
    void rebalanceUpwards(Node* node);
    void updateHeightPath(Node* node);
};

#endif // !AVLTREE_H