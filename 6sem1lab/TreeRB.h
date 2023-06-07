#pragma once

#include "Header.h"

class RBT
{

    struct nodeRB {
        int key;
        struct nodeRB* left, * right, * parent;
        int height;
        bool color = true;

        nodeRB(int key, nodeRB* left = nullptr, nodeRB* right = nullptr, int height = 1)
        {
            this->key = key;
            this->left = left;
            this->right = right;
            this->height = height;
        }
    };

    nodeRB* root;
    nodeRB* TNULL;

    void insertFix(nodeRB* x)
    {
        nodeRB* y;
        while (x->parent->color == 1)
        {
            if (x->parent == x->parent->parent->right)
            {
                y = x->parent->parent->left;
                if (y->color == 1)
                {
                    y->color = 0;
                    x->parent->color = 0;
                    x->parent->parent->color = 1;
                    x = x->parent->parent;
                }
                else
                {
                    if (x == x->parent->left)
                    {
                        x = x->parent;
                        rightRotate(x);
                    }
                    x->parent->color = 0;
                    x->parent->parent->color = 1;
                    leftRotate(x->parent->parent);
                }
            }
            else
            {
                y = x->parent->parent->right;

                if (y->color == 1)
                {
                    y->color = 0;
                    x->parent->color = 0;
                    x->parent->parent->color = 1;
                    x = x->parent->parent;
                }
                else
                {
                    if (x == x->parent->right)
                    {
                        x = x->parent;
                        leftRotate(x);
                    }
                    x->parent->color = 0;
                    x->parent->parent->color = 1;
                    rightRotate(x->parent->parent);
                }
            }
            if (x == root)
            {
                break;
            }
        }
        root->color = 0;
    }

    void leftRotate(nodeRB* x)
    {
        nodeRB* y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(nodeRB* x)
    {
        nodeRB* y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    nodeRB* minimum(nodeRB* NodeRBT)
    {
        while (NodeRBT->left != TNULL)
        {
            NodeRBT = NodeRBT->left;
        }
        return NodeRBT;
    }

    void deleteFix(nodeRB* x)
    {
        nodeRB* y;
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                y = x->parent->right;
                if (y->color == 1)
                {
                    y->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    y = x->parent->right;
                }

                if (y->left->color == 0 && y->right->color == 0)
                {
                    y->color = 1;
                    x = x->parent;
                }
                else {
                    if (y->right->color == 0)
                    {
                        y->left->color = 0;
                        y->color = 1;
                        rightRotate(y);
                        y = x->parent->right;
                    }

                    y->color = x->parent->color;
                    x->parent->color = 0;
                    y->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                y = x->parent->left;
                if (y->color == 1)
                {
                    y->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    y = x->parent->left;
                }

                if (y->right->color == 0 && y->left->color == 0)
                {
                    y->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (y->left->color == 0)
                    {
                        y->right->color = 0;
                        y->color = 1;
                        leftRotate(y);
                        y = x->parent->left;
                    }

                    y->color = x->parent->color;
                    x->parent->color = 0;
                    y->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    int findDepth(nodeRB* root)
    {
        int ret = 0;
        if (root)
        {
            int leftDepth = findDepth(root->left);
            int rightDepth = findDepth(root->right);
            ret = max(leftDepth + 1, rightDepth + 1);
        }
        return ret;
    }

    void rbTransplant(nodeRB* x, nodeRB* y)
    {
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->parent = x->parent;
    }

    void deleteNodeRBTHelper(nodeRB* NodeRBT, int key)
    {
        nodeRB* z = TNULL;
        nodeRB* x, * y;
        while (NodeRBT != TNULL)
        {
            if (NodeRBT->key == key)
            {
                z = NodeRBT;
            }

            if (NodeRBT->key <= key)
            {
                NodeRBT = NodeRBT->right;
            }
            else
            {
                NodeRBT = NodeRBT->left;
            }
        }

        if (z == TNULL)
        {
            cout << "Значение не найдено в дереве!" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0)
        {
            deleteFix(x);
        }
    }

    void del(nodeRB* curr)
    {

        if (curr && curr != TNULL)
        {
            del(curr->left);
            del(curr->right);
            delete curr;
        }
    }

public:
    RBT()
    {
        TNULL = new nodeRB(-1);
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    ~RBT() {
        clear();
    }

    void insert(int key)
    {
        nodeRB* Node = new nodeRB(key);
        Node->parent = nullptr;
        Node->key = key;
        Node->left = TNULL;
        Node->right = TNULL;
        Node->color = 1;

        nodeRB* y = nullptr;
        nodeRB* x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (Node->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        Node->parent = y;
        if (y == nullptr)
        {
            root = Node;
        }
        else if (Node->key < y->key)
        {
            y->left = Node;
        }
        else
        {
            y->right = Node;
        }

        if (Node->parent == nullptr)
        {
            Node->color = 0;
            return;
        }

        if (Node->parent->parent == nullptr)
        {
            return;
        }

        insertFix(Node);
    }

    void remove(int key)
    {
        deleteNodeRBTHelper(this->root, key);
    }

    void clear()
    {
        del(this->root);
        root = TNULL;
    }

    void findDepthCout()
    {
        cout << findDepth(root) << endl;
    }

};