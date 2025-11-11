#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

// A node in the red-black tree that stores a double
class RBTNode {
public:
    double key;
    // Whether the node is red (false denotes black)
    bool red = true;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
    RBTNode* parent = nullptr;

    RBTNode(double nodeKey) {
        key = nodeKey;
    }
};

// A red-black tree that can only insert
class RedBlackTree
{
public:
    RedBlackTree() {};
    ~RedBlackTree();
	
    // Insert a new element and rebalance the tree
    void insert(RBTNode* node);

    // Get the root of the tree (for testing purposes)
    RBTNode* getRoot() const { return root; }
    
    // Get the height of the tree
    int getHeight() const;

private:
    RBTNode* root = nullptr;
    void deleteTree(RBTNode* node);
    
    // Helper functions for Red-Black Tree operations
    void BSTInsert(RBTNode* node);
    void RBTreeBalance(RBTNode* node);
    RBTNode* RBTreeGetGrandparent(RBTNode* node) const;
    RBTNode* RBTreeGetUncle(RBTNode* node) const;
    void RBTreeRotateLeft(RBTNode* node);
    void RBTreeRotateRight(RBTNode* node);
    bool RBTreeSetChild(RBTNode* parent, const char* whichChild, RBTNode* child);
    bool RBTreeReplaceChild(RBTNode* parent, RBTNode* currentChild, RBTNode* newChild);
    int getHeightHelper(RBTNode* node) const;
};

#endif // !REDBLACKTREE_H