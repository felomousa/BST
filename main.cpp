#include <iostream>
using namespace std;

struct TreeNode
{
    int nodeValue;
    TreeNode *nodeLeft;
    TreeNode *nodeRight;
    TreeNode(int nodeValue) : nodeValue(nodeValue), nodeLeft(nullptr), nodeRight(nullptr) {};
};

class BinarySearchTree
{
private:
    TreeNode *root;
    TreeNode *insertNode(TreeNode *node, int value)
    {
        if (root == nullptr)
        {
            root = new TreeNode(value);
            return root;
        }

        if (value < node->nodeValue)
        {
            node->nodeLeft = insertNode(node->nodeLeft, value);
        }
        else
        {
            node->nodeRight = insertNode(node->nodeRight, value);
        }

        return node;
    }

public:
    void insertNode(int value) { root = insertNode(root, value); };
    BinarySearchTree() { root = nullptr; }
};

int main() {};