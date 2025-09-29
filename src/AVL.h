//
// Created by Carlos Mendez on 9/19/25.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>

#endif //AVLTREE_H

class AVL {
    struct Node {
        std::string name;
        int id;
        int height = 0;
        Node* left;
        Node* right;
        Node(std::string name, int x) :name(name),  id(x), left(nullptr), right(nullptr){}
    };
    int numOfUsers = 0;
    Node* root = nullptr;

    void setRoot(Node* root);
    Node* helperInsert(Node* helpRoot,std::string name, int id);

    int getHeight(Node* node);
    void updateHeight(Node* node);
    int getBalanceFactor(Node* helpRoot);

    Node* balanceNode(Node* node);
    Node* leftRotation(Node* helpRoot);
    Node* rightRotation(Node* helpRoot);

    void helperInOrderImplementation(Node* helpRoot, std::vector<int>& output);
    std::vector<int> helperInOrder(Node* helpRoot);

    void helperPostOrderImplementation(Node* helpRoot, std::vector<int>& output);
    std::vector<int> helperPostOrder(Node* helpRoot);

    void helperPreOrderImplementation(Node* helpRoot, std::vector<int>& output);
    std::vector<int> helperPreOrder(Node* helpRoot);

    Node* findInOrderSuccessor(Node* node);
    void updateID(Node* node, int id);
    void updateName(Node* node, std::string name);

public:
    Node* getRoot();
    int getID(Node* node);
    std::string getName(Node* node);
    void insert(std::string name, int id);
    void removeUser(int id);
    void removeInorder(int n); //0 is the first item

    void printInorder();
    void printPreorder();
    void printPostorder();
    void levelCount();

    Node* search(int id);
    Node* search(std::string name);
};
