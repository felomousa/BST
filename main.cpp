#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

vector<string> randomWords(const string path)
{
    vector<string> words;
    string word;
    ifstream file(path);
    while (getline(file, word))
    {
        words.push_back(word);
    }
    file.close();
    return words;
}

template <typename T>
void bstStringFiller(BinarySearchTree<T> &bst, vector<string> words)
{
    srand(time(NULL));

    for (int i = 0; i < 10; ++i)
    {
        int randLine = rand() % words.size();

        T randomWord = words[randLine];
        bst.insertNode(randomWord);
    }
}

template <typename T>
bool terminateValue(const T &value)
{
    if constexpr (is_same_v<T, string>)
    {
        return value == "stop";
    }
    else
    {
        return value == static_cast<T>(-1);
    }
}

template <typename T>
void helperFunction(BinarySearchTree<T> &BST, const vector<string> &words = {})
{
    char choice{};
    cout << "Would you like to use randomly generated values to populate the BST? (y/n)\n";
    cin >> choice;

    if (choice == 'y')
    {
        if constexpr (!is_same_v<T, string>)
        {
            bstFiller(BST);
        }
        else
        {
            bstStringFiller(BST, words);
        }
    }
    else
    {
        cout << "Enter values to insert into the BST. type 'stop' if using strings or '-1' if using numeric types\n";

        while (true)
        {
            T value;
            cin >> value;
            if (terminateValue(value))
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

    if constexpr (is_arithmetic_v<T>)
    {
        cout << "Search for value 15, drumroll please..." << (BST.search(static_cast<T>(15)) ? " FOUND!" : " NOT FOUND!") << endl;
    }

    if constexpr (!is_arithmetic_v<T>)
    {
        cout << "Search for value 'Xanax', drumroll please..." << (BST.search("Xanax") ? " FOUND!" : " NOT FOUND!") << endl;
    }

    cout << "Max Value: " << BST.maxValue() << endl;
    cout << "Min Value: " << BST.minValue() << endl;

    cout << "Completed BST: \n";
    BST.dispTree();
}

int main()
{
    int inputType;
    cout << "Choose a data type (by selecting the number): \n1. int\n2. double\n3. stirng \n";
    cin >> inputType;

    if (inputType == 1)
    {
        BinarySearchTree<int> BST;
        cout << "Selected <int>\n";
        helperFunction(BST);
    }
    else if (inputType == 2)
    {
        BinarySearchTree<double> BST;
        cout << "Selected <double>\n";
        helperFunction(BST);
    }
    else if (inputType == 3)
    {
        BinarySearchTree<string> BST;
        cout << "Selected <string>\n";
        vector<string> words = randomWords("words.txt");
        helperFunction(BST, words);
    }
    else
    {
        cout << "improper response. bye!\n";
        return 1;
    }

    return 0;
}
