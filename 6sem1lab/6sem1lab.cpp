#include "TreeAVL.h"
#include "TreeRB.h"

struct node {
    int key;
    struct node* left, * right, * parent;
};

struct node* newNode(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = temp->parent = NULL;
    return temp;
}

int findDepth(node* root)
{
    int ret = 0;
    if (root)
    {
        int lDepth = findDepth(root->left);
        int rDepth = findDepth(root->right);
        ret = max(lDepth + 1, rDepth + 1);
    }
    return ret;
}


struct node* insert(struct node* node, int key) {

    if (node == NULL) return newNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
        node->left->parent = node;
    }
    else {
        node->right = insert(node->right, key);
        node->right->parent = node;
    }
    return node;
}


int main() {

    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    //int count = 30000;
    int count;
    cout << "Введите колличество элементов: ";
    cin >> count;
    cout << endl << endl;

    int countTry = 100;

    struct node* root = NULL;
    for (int i = 0; i < count; i++)
    {
        root = insert(root, rand() % 1000);
    }
    cout << "Глубина двоичного дерева поиска = " << findDepth(root) << endl;


    cout << endl << endl;


    RBT rbTree;
    double rbTime = 0;
    chrono::duration<double, micro> duration;
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    for (int j = 0; j < countTry; j++)
    {
        rbTree.clear();
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < count; i++)
        {
            rbTree.insert(rand() % 1000);
        }
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        rbTime += duration.count();
    }
    cout << "Глубина красно-чёрного дерева = "; rbTree.findDepthCout();
    cout << "Время красно-чёрного дерева = " << rbTime / countTry << " мкс\n";


    cout << endl << endl;


    AVL treeAVL;
    double avlTime = 0;
    for (int j = 0; j < countTry; j++)
    {
        treeAVL.clear();
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < count; i++)
        {
            treeAVL.insert(rand() % 1000);
        }
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        avlTime += duration.count();
    }

    cout << "Глубина АВЛ-дерева = "; treeAVL.findDepthCout();
    cout << "Время АВЛ-дерева = " << avlTime / countTry << " мкс\n";

    cout << endl;
    system("pause");

}