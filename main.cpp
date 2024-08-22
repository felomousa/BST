#include <iostream>
using namespace std;

template <typename T>
struct TreeNode
{
    T nodeValue;
    TreeNode *nodeLeft;
    TreeNode *nodeRight;
    TreeNode(T nodeValue) : nodeValue(nodeValue), nodeLeft(nullptr), nodeRight(nullptr) {};
};

template <typename T>
class BinarySearchTree
{
private:
    TreeNode<T> *root;
    TreeNode<T> *insertNode(TreeNode<T> *node, T value)
    {
        if (node == nullptr)
        {
            root = new TreeNode<T>(value);
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
    bool search(TreeNode<T> *node, T value)
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
    void traverseInOrder(TreeNode<T> *node)
    {
        if (node != nullptr)
        {
            traverseInOrder(node->nodeLeft);
            cout << node->nodeValue << " → ";
            traverseInOrder(node->nodeRight);
        }
    }
    void traversePreOrder(TreeNode<T> *node)
    {
        if (node != nullptr)
        {
            cout << node->nodeValue << " → ";
            traversePreOrder(node->nodeLeft);
            traversePreOrder(node->nodeRight);
        }
    }
    void traversePostOrder(TreeNode<T> *node)
    {
        if (node != nullptr)
        {
            traversePostOrder(node->nodeLeft);
            traversePostOrder(node->nodeRight);
            cout << node->nodeValue << " → ";
        }
    }

    T minValue(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            throw invalid_argument("Invalid Tree");
        }
        if (node->nodeLeft == nullptr)
        {
            return node->nodeValue;
        }
        return minValue(node->nodeLeft);
    }

    T maxValue(TreeNode<T> *node)
    {
        if (node == nullptr)
        {
            throw invalid_argument("Invalid Tree");
        }
        if (node->nodeRight == nullptr)
        {
            return node->nodeValue;
        }
        return maxValue(node->nodeRight);
    }

    void dispTree(TreeNode<T> *node, bool leftNode = true, string prefix = "")
    {
        if (node == nullptr)
            return;
        cout << prefix;
        cout << (leftNode ? "├─ " : "└─ ") << node->nodeValue << (leftNode ? " (L)" : " (R)") << endl;
        dispTree(node->nodeLeft, true, prefix + (leftNode ? "│  " : "   "));
        dispTree(node->nodeRight, false, prefix + (leftNode ? "│  " : "   "));
    }

public:
    void insertNode(T value) { root = insertNode(root, value); };
    bool search(T value) { return search(root, value); }

    void inOrder() { traverseInOrder(root); };
    void preOrder() { traversePreOrder(root); };
    void postOrder() { traversePostOrder(root); };

    T minValue() { return minValue(root); }
    T maxValue() { return maxValue(root); }

    void dispTree() { dispTree(root); }

    BinarySearchTree() { root = nullptr; }
};

template <typename T>
void bstFiller(BinarySearchTree<T> &bst)
{
    srand(time(NULL));

    for (int i = 0; i < 5; ++i)
    {
        T randomValue = (rand() % 20000) / 1000.0;
        bst.insertNode(randomValue);
    }
}

int main()
{
    int inputType;
    cout << "Choose a data type (by selecting the number): \n1. int\n2. double\n3. stirng \n";
    cin >> inputType;

    BinarySearchTree<double> BST; // default

    // if (inputType == 1) // This doesn't work. need to find another way to select type, BST is only declared locally within the IF statement.
    // {
    //     BinarySearchTree<int> BST;
    //     cout << "Selected <int>\n";
    // }
    // else if (inputType == 2)
    // {
    //     BinarySearchTree<double> BST;
    //     cout << "Selected <double>\n";
    // }

    char choice{};
    cout << "Would you like to use randomly generated values to populate the BST? (y/n)";
    cin >> choice;

    if (choice == 'y')
    {
        bstFiller(BST);
    }
    else
    {
        cout << "Enter values to insert into the BST. Enter -1 to stop :D\n";

        while (true)
        {
            float value;
            cin >> value;
            if (value == -1)
                break;
            cout << "\n\n\n\n\n";

            BST.insertNode(value);
            BST.dispTree();
            cout << endl;
        }
    }

    cout << endl;
    cout << "In-order traversal:" << endl; // Ascending Order
    BST.inOrder();
    cout << endl;

    cout << "Pre-order traversal:" << endl;
    BST.preOrder();
    cout << endl;

    cout << "Post-order traversal:" << endl;
    BST.postOrder();
    cout << endl;

    cout << "Search for value 15, drumroll please..." << (BST.search(15) ? " FOUND!" : " NOT FOUND!") << endl;

    cout << "Max Value: " << BST.maxValue() << endl;
    cout << "Min Value: " << BST.minValue() << endl;

    cout << "Completed BST: \n";
    BST.dispTree();

    return 0;
}
