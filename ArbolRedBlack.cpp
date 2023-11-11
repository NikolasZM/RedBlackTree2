// Implementing Red-Black Tree in C++

#include <iostream>
using namespace std;

struct Nodo {
    int data;
    Nodo* parent;
    Nodo* left;
    Nodo* right;
    int color; //0 red 1 black
};



class RedBlackTree {
private:
    Nodo* root;
    Nodo* TNULL;
 

    // For balancing the tree after insertion
    void insertFix(Nodo* k) {
        Nodo* u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper(Nodo* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RedBlackTree() {
        TNULL = new Nodo;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }


    void leftRotate(Nodo* x) {
        Nodo* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Nodo* x) {
        Nodo* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a nodo
    void insert(int key) {
        Nodo* nodo = new Nodo;
        nodo->parent = nullptr;
        nodo->data = key;
        nodo->left = TNULL;
        nodo->right = TNULL;
        nodo->color = 1;

        Nodo* y = nullptr;
        Nodo* x = this->root;

        while (x != TNULL) {
            y = x;
            if (nodo->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        nodo->parent = y;
        if (y == nullptr) {
            root = nodo;
        }
        else if (nodo->data < y->data) {
            y->left = nodo;
        }
        else {
            y->right = nodo;
        }

        if (nodo->parent == nullptr) {
            nodo->color = 0;
            return;
        }

        if (nodo->parent->parent == nullptr) {
            return;
        }

        insertFix(nodo);
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};

int main() {
    RedBlackTree bst;
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(57);

    bst.printTree();
    cout << endl;
}