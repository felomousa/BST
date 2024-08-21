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
        if (node == nullptr)
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
    bool search(TreeNode *node, int value)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (value == node->nodeValue)
        {
            return true;
        }
        else if (value < node->nodeValue)
        {
            return search(node->nodeLeft, value);
        }
        else // if (value>node->nodeValue)
        {
            return search(node->nodeRight, value);
        }
    }
    void traverseInOrder(TreeNode *node)
    {
        if (node != nullptr)
        {
            traverseInOrder(node->nodeLeft);
            cout << node->nodeValue << "\n";
            traverseInOrder(node->nodeRight);
        }
    }
    void traversePreOrder(TreeNode *node)
    {
        if (node != nullptr)
        {
            cout << node->nodeValue << "\n";
            traversePreOrder(node->nodeLeft);
            traversePreOrder(node->nodeRight);
        }
    }
    void traversePostOrder(TreeNode *node)
    {
        if (node != nullptr)
        {
            traversePostOrder(node->nodeLeft);
            traversePostOrder(node->nodeRight);
            cout << node->nodeValue << "\n";
        }
    }

public:
    void insertNode(int value) { root = insertNode(root, value); };
    bool search(int value) { return search(root, value); }

    void inOrder() { traverseInOrder(root); };
    void preOrder() { traversePreOrder(root); };
    void postOrder() { traversePostOrder(root); };

    BinarySearchTree() { root = nullptr; }
};

int main()
{
    BinarySearchTree BST;

    cout << "In-order traversal:" << endl;
    BST.inOrder();

    cout << "Pre-order traversal:" << endl;
    BST.preOrder();

    cout << "Post-order traversal:" << endl;
    BST.postOrder();

    return 0;
}
