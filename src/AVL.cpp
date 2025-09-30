//
// Created by Carlos Mendez on 9/19/25.
//
#include "AVL.h"

#include <random>
#include <queue>

// #include "../cmake-build-debug/_deps/catch2-src/src/catch2/generators/catch_generators.hpp"

AVL::Node* AVL::getRoot() {
    return this->root;
}

int AVL::getID(Node* node) {
    return node->id;
}

std::string AVL::getName(Node *node) {
    return node->name;
}

void AVL::setRoot(Node *root) {
    this->root = root;
}

//recursive insertion
AVL::Node *AVL::helperInsert(Node* helpRoot, std::string name, int id) {
    //keeps on iterating until it reaches the leaf node
    if (helpRoot == nullptr) {
        this->numOfUsers++;
        return new Node(name,id);
    } else if (id < helpRoot->id) {
        helpRoot->left = helperInsert(helpRoot->left, name, id);
        // this->numOfUsers++;
    } else if (id > helpRoot->id) {
        helpRoot->right = helperInsert(helpRoot->right, name, id);
        // this->numOfUsers++;
    } else {
        return helpRoot;
    }

    updateHeight(helpRoot);
    return balanceNode(helpRoot);
}

void AVL::insert(std::string name, int id) {
    if (id < 10000000 || id > 99999999) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    if (searchNoPrint(id) != nullptr)
    {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    this->root = helperInsert(this->getRoot(), name, id);
    updateHeight(this->root);
    std::cout << "successful" << std::endl;
}

void AVL::updateID(Node* node, int id) {
    node->id = id;
}

void AVL::updateName(Node *node, std::string name) {
    node->name = name;
}

//returns itself if node has no children
//returns successor if all conditions are met
//returns the child if there is only 1

//only works with node->right
AVL::Node *AVL::findInOrderSuccessor(Node *node) {
    if (!node->left) {
        return node;
    }

    return findInOrderSuccessor(node->left);
}

//node has 2 children, right-left is the successor
//if right-left does not exist just right is successor
//
//node has one child, that child becomes the successor
//don't have to rebalance, if implemented right
void AVL::removeUser(int id) {
    Node* prev = nullptr;
    Node* currentNode = this->root;

    //sees if the node exists
    while (currentNode && currentNode->id != id) {
        // std::cout << "running" << std::endl;
        prev = currentNode;
        if (currentNode->id < id) {
            currentNode = currentNode->right;
        } else if (currentNode->id > id) {
            currentNode = currentNode->left;
        }
    }

    //if node doesn't exist it returns unsuccessful
    if (!currentNode) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }

    if (currentNode->left && currentNode->right) {
        if (currentNode->right && currentNode->left) { //when root has 2 children
            Node* parentSuccessor = currentNode;
            Node* successor = currentNode->right;

            while (successor->left) {
                parentSuccessor = successor;
                successor = successor->left;
            }

            updateName(currentNode, getName(successor));
            updateID(currentNode, getID(successor));

            if (currentNode == parentSuccessor) {
                currentNode->right = successor->right;
            }else {
                parentSuccessor->left = successor->right;
            }
            std::cout << "successful" << std::endl;
            delete successor;
            return;
        }

        if (currentNode->right) {
            this->root = currentNode->right;
            delete currentNode;
            std::cout << "successful" << std::endl;
            return;
        }

        if (currentNode->left) {
            this->root = currentNode->left;
            delete currentNode;
            std::cout << "successful" << std::endl;
            return;
        }

        //if node is leaf node
        if (!currentNode->right && !currentNode->left) {
            this->root = nullptr;
            delete currentNode;
            std::cout << "successful" << std::endl;
            return;
        }
    } else {
        Node* child = nullptr;
        if (currentNode->left != nullptr)
            child = currentNode->left;
        else
            child = currentNode->right;

        if (prev == nullptr) {
            this->root = child;
        } else if (prev->left == currentNode) {
            prev->left = child;
        } else
            prev->right = child;
        delete currentNode;
        std::cout << "successful" << std::endl;
    }

}

void AVL::removeInorder(int n) {
    auto data = helperInOrder(this->root);
    int target = data.first[n];
    try
    {
        removeUser(target);
        // std::cout << "successful" << std::endl;
    } catch (...)
    {
        std::cout << "unsuccessful" << std::endl;
    }

}

int AVL::getHeight(Node* node) {
    if (node)
        return node->height;
    return 0;
}

void AVL::updateHeight(Node* node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

AVL::Node* AVL::leftRotation(Node* helpRoot) {
    Node* grandchild = helpRoot->right->left;
    Node* newParent = helpRoot->right;
    newParent->left = helpRoot;
    helpRoot->right = grandchild;
    updateHeight(helpRoot);
    updateHeight(newParent);

    return newParent;
}

AVL::Node* AVL::rightRotation(Node *helpRoot) {
    Node* grandchild = helpRoot->left->right;
    Node* newParent = helpRoot->left;
    newParent->right = helpRoot;
    helpRoot->left = grandchild;
    updateHeight(helpRoot);
    updateHeight(newParent);

    return newParent;
}

int AVL::getBalanceFactor(Node *helpRoot) {
    return getHeight(helpRoot->left) - getHeight(helpRoot->right);
}

AVL::Node* AVL::balanceNode(Node* node) {
    updateHeight(node);
    int nodeBalanceFactor = getBalanceFactor(node);
    //root: positive, child: positive, left rotation
    //root: negative, child: negative, right rotation
    //root: positive, child negative, right then left rotation, right-left scenario
    //root: negative, child: positive, left then right rotation, left-right scenario

    //More nodes on left side
    if (nodeBalanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) { //right-left
            node->left = leftRotation(node->left);
        }
        return rightRotation(node); //left-left
    }

    //more nodes on right side
    if (nodeBalanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0 ) {
            node->right = rightRotation(node->right); //left-right
        }
        return leftRotation(node); //right-right
    }

    return node;
}

AVL::Node* AVL::search(int id) {
    Node* currentNode = this->root;

    while (currentNode != nullptr) {
        if (currentNode->id == id) {
            std::cout << getName(currentNode)<< std::endl;
            return currentNode;
        } else if (currentNode->id < id) {
            currentNode = currentNode->right;
        } else if (currentNode->id > id) {
            currentNode = currentNode->left;
        }
    }

    std::cout << "unsuccessful" << std::endl;
    return nullptr;
}

AVL::Node* AVL::searchNoPrint(int id) {
    Node* currentNode = this->root;

    while (currentNode != nullptr) {
        if (currentNode->id == id) {
            return currentNode;
        } else if (currentNode->id < id) {
            currentNode = currentNode->right;
        } else if (currentNode->id > id) {
            currentNode = currentNode->left;
        }
    }

    return nullptr;
}

AVL::Node* AVL::search(std::string name) {
    auto data = helperInOrder(this->root);
    bool printed = false;
    // Node* currentNode = this->root;

    if (!getRoot()) {
        std::cout << "unsuccessful" << std::endl;
        return nullptr;
    }

    for (size_t i = 0; i < data.second.size(); i++) {
        if (name == data.second[i]) {
            printed = true;
            std::cout << data.first[i] << std::endl;
        }
    }

    if (!printed)
    {
    std::cout << "unsuccessful" << std::endl;
    return nullptr;
    }

    return nullptr;
}


//LNR
void AVL::helperInOrderImplementation(Node *helpRoot, std::vector<int> &outputId, std::vector<std::string> &outputName) {
    if (!helpRoot)
        return;
    helperInOrderImplementation(helpRoot->left, outputId, outputName);
    outputId.push_back(helpRoot->id);
    outputName.push_back(helpRoot->name);
    helperInOrderImplementation(helpRoot->right, outputId, outputName);
}

std::pair<std::vector<int>, std::vector<std::string>> AVL::helperInOrder(Node *helpRoot) {
    std::vector<int> result;
    std::vector<std::string> outputName;
    helperInOrderImplementation(helpRoot, result, outputName);
    return {result, outputName};
}

void AVL::printInorder() {
    auto result = helperInOrder(this->root);


    for (size_t i = 0; i < result.second.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << result.second[i];
    }
    std::cout << std::endl;
}

//LRN
void AVL::helperPostOrderImplementation(Node *helpRoot, std::vector<int> &outputId, std::vector<std::string> &outputName) {
    if (!helpRoot)
        return;
    helperPostOrderImplementation(helpRoot->left, outputId, outputName);
    helperPostOrderImplementation(helpRoot->right, outputId, outputName);
    outputId.push_back(helpRoot->id);
    outputName.push_back(helpRoot->name);

}

std::pair<std::vector<int>, std::vector<std::string>> AVL::helperPostOrder(Node *helpRoot) {
    std::vector<int> result;
    std::vector<std::string> outputName;
    helperPostOrderImplementation(helpRoot, result, outputName);
    return {result, outputName};
}

void AVL::printPostorder() {
    auto result = helperPostOrder(this->root);


    for (size_t i = 0; i < result.second.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << result.second[i];
    }
    std::cout << std::endl;
}

// NLR
void AVL::helperPreOrderImplementation(Node *helpRoot, std::vector<int> &outputId, std::vector<std::string> &outputName) {
    if (!helpRoot)
        return;
    outputId.push_back(helpRoot->id);
    outputName.push_back(helpRoot->name);
    helperPreOrderImplementation(helpRoot->left, outputId, outputName);
    helperPreOrderImplementation(helpRoot->right, outputId, outputName);
}

std::pair<std::vector<int>, std::vector<std::string>> AVL::helperPreOrder(Node *helpRoot) {
    std::vector<int> result;
    std::vector<std::string> outputName;
    helperPreOrderImplementation(helpRoot, result,outputName);
    return {result, outputName};
}

void AVL::printPreorder() {
    auto result = helperPreOrder(this->root);


    for (size_t i = 0; i < result.second.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << result.second[i];
    }
    std::cout << std::endl;
}

void AVL::levelCount() {
    std::cout << getHeight(this->root) << std::endl;
}
