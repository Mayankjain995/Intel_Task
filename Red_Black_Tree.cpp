#include <iostream>
using namespace std;

/* Colors of Red-Black Tree nodes */
enum Color { RED, BLACK };

/* Structure of a Red-Black Tree Node */
struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int value) {
        data = value;
        color = RED;          // New node is always RED
        left = right = parent = NULL;
    }
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;   // Sentinel node (acts like NULL, but BLACK)

    /* Left Rotation */
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NULL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    /* Right Rotation */
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != NIL)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == NULL)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    /* Fix Red-Black Tree property violations */
    void fixInsert(Node* z) {
        while (z->parent != NULL && z->parent->color == RED) {

            // Parent is left child of grandparent
            if (z->parent == z->parent->parent->left) {
                Node* uncle = z->parent->parent->right;

                // Case 1: Uncle is RED (recoloring)
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    // Case 2: z is right child
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }

                    // Case 3: z is left child
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            // Parent is right child of grandparent
            else {
                Node* uncle = z->parent->parent->left;

                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        // Root must always be BLACK
        root->color = BLACK;
    }

    /* Inorder traversal */
    void inorder(Node* node) {
        if (node != NIL) {
            inorder(node->left);
            cout << node->data << " (" << (node->color == RED ? "R" : "B") << ") ";
            inorder(node->right);
        }
    }

public:
    /* Constructor */
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    /* Insert a new node */
    void insert(int value) {
        Node* z = new Node(value);
        z->left = z->right = NIL;

        Node* parent = NULL;
        Node* current = root;

        // Standard BST insertion
        while (current != NIL) {
            parent = current;
            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        z->parent = parent;

        if (parent == NULL)
            root = z;
        else if (value < parent->data)
            parent->left = z;
        else
            parent->right = z;

        // Fix Red-Black Tree properties
        fixInsert(z);
    }

    /* Print tree in inorder */
    void display() {
        inorder(root);
        cout << endl;
    }
};

/* Main function */
int main() {
    RedBlackTree tree;

    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(10);
    tree.insert(18);
    tree.insert(22);
    tree.insert(30);
    tree.insert(5);

    cout << "Inorder Traversal (Value(Color)):\n";
    tree.display();

    return 0;
}
