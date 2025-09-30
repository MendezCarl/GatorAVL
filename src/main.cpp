#include "AVL.h"


//input: insert name id
const std::regex insertNameId(
    R"(^\s*insert\s+"([^"]+)\s+(\d{8})\s*$)"
);

//input: insert id name
const std::regex insertIdName(
    R"(^\s*insert\s+(\d{8})\s+"([^"]+)\s*$)"
);

//input: insert "name" id
const std::regex insertFlex(
    R"(^\s*insert\s+["“]([^"”]+)["”]\s+(\d{8})\s*$)"
);

//input: search id
std::regex searchId(
    R"(^\s*search\s+(\d{8})\s*$)"
);

//input: search "name"
std::regex searchName(
    R"re(^\s*search\s+"([^"]+)"\s*$)re"
);

//input: remove id
std::regex removeId(
    R"(^\s*remove\s+(\d{8})\s*$)"
);

//input: remove num
std::regex removeInorder(
    R"(^\s*removeInorder\s+(\d+)\s*$)"
);

//input: inorder/preorder/postorder
//links them to the right function in AVL.cpp
std::regex traversal(
    R"(^\s*(inorder|preorder|postorder|levelCount)\s*$)"
);

//input: printInorder/printPreorder/printPostorder
//links them to the right function in AVL.cpp
std::regex traversalPrint(
    R"(^\s*print(Inorder|Preorder|Postorder|LevelCount)\s*$)"
);


int main() {
    AVL tree;
    std::string line;
    std::smatch m;

    while (std::getline(std::cin, line)) {

        if (std::regex_match(line, m, insertNameId)) {
            std::string name = m[1].str();
            int id = std::stoi(m[2].str());
            tree.insert(name, id);
            continue;
        }
        if (std::regex_match(line, m, insertIdName)) {
            int id = std::stoi(m[1].str());
            std::string name = m[2].str();
            tree.insert(name, id);
            continue;
        }
        if (std::regex_match(line, m, insertFlex)) {
            std::string name = m[1].str();
            int id = std::stoi(m[2].str());
            tree.insert(name, id);
            continue;
        }

        if (std::regex_match(line, m, searchId)) {
            int id = std::stoi(m[1].str());
            (void)tree.search(id);
            continue;
        }
        if (std::regex_match(line, m, searchName)) {
            const std::string name = m[1].str();
            (void)tree.search(name);
            continue;
        }

        if (std::regex_match(line, m, removeId)) {
            int id = std::stoi(m[1].str());
            tree.removeUser(id);
            continue;
        }
        if (std::regex_match(line, m, removeInorder)) {
            int n = std::stoi(m[1].str());
            tree.removeInorder(n);
            continue;
        }

        if (std::regex_match(line, m, traversal)) {
            std::string cmd = m[1].str();
            if (cmd == "inorder")
                tree.printInorder();
            else if (cmd == "preorder")
                tree.printPreorder();
            else if (cmd == "postorder")
                tree.printPostorder();
            else if (cmd == "levelCount")
                tree.levelCount();
            continue;
        }

        if (std::regex_match(line, m, traversalPrint)) {
            const std::string which = m[1];
            if (which == "Inorder")
                tree.printInorder();
            else if (which == "Preorder")
                tree.printPreorder();
            else if (which == "Postorder")
                tree.printPostorder();
            else if (which == "LevelCount")
                tree.levelCount();
            continue;
        }

        if (std::regex_match(line, std::regex(R"(^\s*\d+\s*$)")))
        {
            continue;
        }

        // std::cout << "Invalid input" << std::endl;
    }
}
