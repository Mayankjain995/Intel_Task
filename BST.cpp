#include <iostream>
using namespace std;

/* Structure of BST Node */
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

/* Insert a node into BST */
Node* insert(Node* root, int value) {

    // If tree is empty, create new node
    if (root == NULL) {
        return new Node(value);
    }

    // Insert into left subtree
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    // Insert into right subtree
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    // If value is duplicate, ignore insertion

    return root;
}

/* Inorder Traversal (Left, Root, Right) */
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

/* Preorder Traversal (Root, Left, Right) */
void preorder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

/* Postorder Traversal (Left, Right, Root) */
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

/* Main Function */
int main() {
    Node* root = NULL;
    int choice;

    // Given elements to create BST
    int values[] = {6, 9, 5, 2, 8, 15, 24, 14, 7, 8, 5, 2};
    int n = 12;

    do {
        cout << "\n--- BST MENU ---\n";
        cout << "1. Create BST\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Postorder Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            root = NULL;  // Reset tree
            for (int i = 0; i < n; i++) {
                root = insert(root, values[i]);
            }
            cout << "BST created successfully.\n";
            break;

        case 2:
            if (root == NULL)
                cout << "BST is empty. Create it first.\n";
            else {
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
            }
            break;

        case 3:
            if (root == NULL)
                cout << "BST is empty. Create it first.\n";
            else {
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
            }
            break;

        case 4:
            if (root == NULL)
                cout << "BST is empty. Create it first.\n";
            else {
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << endl;
            }
            break;

        case 5:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
