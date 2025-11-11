#include "RedBlackTree.h"
#include <iostream>

int main() {
    /*Test red-black tree inserts*/
    RedBlackTree a;
    RBTNode* aRoot = new RBTNode(22);
    a.insert(aRoot);
    a.insert(new RBTNode(11));
    a.insert(new RBTNode(33));
    a.insert(new RBTNode(55));
    a.insert(new RBTNode(44));

    RBTNode* root = a.getRoot();
    
    std::cout << root->key << std::endl;
    std::cout << root->left->key << " " << root->right->key << std::endl;
    std::cout << root->right->left->key << " " << root->right->right->key << std::endl;

    return 0;
}

