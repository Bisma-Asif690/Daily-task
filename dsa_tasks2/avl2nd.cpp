#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct AVLNode {
    int data, height;
    AVLNode *left, *right;
    AVLNode(int data, AVLNode *left=NULL, AVLNode *right=NULL) {
        this->data = data;
        this->left = left;
        this->right = right;
        this->height = 0;
    }
};

int max(const int a, const int b) {
    return (a < b ? b : a);
}

class BST {
    AVLNode *root;

public:
    BST() { root = NULL; }

    AVLNode* leftRotation(AVLNode* temp) {
        AVLNode* temp_right = temp->right;
        temp->right	= temp_right->left;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        temp_right->left = temp;
        temp = temp_right;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }

    AVLNode* rightRotation(AVLNode* temp) {
        AVLNode* temp_left = temp->left;
        temp->left	= temp_left->right;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        temp_left->right = temp;
        temp = temp_left;
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }

    int getHeight(AVLNode* t) const {
        if (!t)	return -1;
        return t->height;
    }

    int getHeight() const {
        if (!root)	return 0;
        int lh = getHeight(root->left);
        int rh = getHeight(root->right);
        return max(lh, rh) + 1;
    }

    AVLNode* doRightRotation(AVLNode* temp) {
        int balance = getHeight(temp->left->left) - getHeight(temp->left->right);
        if (balance < 0) temp->left = leftRotation(temp->left);
        return rightRotation(temp);
    }

    AVLNode* doLeftRotation(AVLNode* temp) {
        int balance = getHeight(temp->right->left) - getHeight(temp->right->right);
        if (balance > 0) temp->right = rightRotation(temp->right);
        return leftRotation(temp);
    }

    AVLNode* doRotation(AVLNode* temp) {
        int lh = getHeight(temp->left);
        int rh = getHeight(temp->right);
        int balance = lh - rh;

        if (balance > 1)
            temp = doRightRotation(temp);
        else if (balance < -1)
            temp = doLeftRotation(temp);

        return temp;
    }

    AVLNode* insert(int d, AVLNode *temp) {
        if (temp == NULL) return new AVLNode(d);

        if (d < temp->data) temp->left = insert(d, temp->left);
        else if (d > temp->data) temp->right = insert(d, temp->right);

        temp = doRotation(temp);
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }

    void insert(int d) {
        root = insert(d, root);
    }

    AVLNode* findLeftMost(AVLNode *t) {
        return (t->left == NULL ? t : findLeftMost(t->left));
    }

    AVLNode* remove(int d, AVLNode *temp) {
        if (temp == NULL) return NULL;

        if (d < temp->data) temp->left = remove(d, temp->left);
        else if (d > temp->data) temp->right = remove(d, temp->right);
        else {
            if (temp->left == NULL && temp->right == NULL) {
                delete temp; 
                return NULL;
            }
            else if (temp->left == NULL) {
                AVLNode *tempR = temp->right;
                delete temp;
                return tempR;
            }
            else if (temp->right == NULL) {
                AVLNode *tempL = temp->left;
                delete temp;
                return tempL;
            }
            else {
                AVLNode *rep = findLeftMost(temp->right);
                temp->data = rep->data;
                temp->right = remove(rep->data, temp->right);
            }
        }

        temp = doRotation(temp);
        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        return temp;
    }

    void remove(int d) {
        root = remove(d, root);
    }

    void inorder(AVLNode* t) {
        if (t != NULL) {
            inorder(t->left);
            cout << t->data << ' ';
            inorder(t->right);
        }
    }

    void inorder() {
        inorder(root);
        cout << '\n';
    }

    void preorder(AVLNode* t) {
        if (t != NULL) {
            cout << t->data << ' ';
            preorder(t->left);
            preorder(t->right);
        }
    }

    void preorder() {
        preorder(root);
        cout << '\n';
    }

    bool recSearch(int key) {
        return recSearch(root, key);
    }
    bool recSearch(AVLNode* t, int key) {
        if (!t) return false;
        if (key == t->data) return true;
        if (key < t->data) return recSearch(t->left, key);
        return recSearch(t->right, key);
    }

    int countNodes() { return countNodes(root); }
    int countNodes(AVLNode* t) {
        if (!t) return 0;
        return 1 + countNodes(t->left) + countNodes(t->right);
    }

    int getHeightRec() { return getHeightRec(root); }
    int getHeightRec(AVLNode* t) {
        if (!t) return -1;
        return 1 + max(getHeightRec(t->left), getHeightRec(t->right));
    }

    void doubleTree() { doubleTree(root); }
    void doubleTree(AVLNode* t) {
        if (!t) return;

        doubleTree(t->left);
        doubleTree(t->right);

        AVLNode* oldLeft = t->left;
        t->left = new AVLNode(t->data);
        t->left->left = oldLeft;
    }

    void printAllPaths() {
        int path[100];
        printAllPaths(root, path, 0);
    }

    void printAllPaths(AVLNode* r, int path[], int pl) {
        if (!r) return;

        path[pl] = r->data;
        pl++;

        if (!r->left && !r->right) {
            for (int i = 0; i < pl; i++) {
                cout << path[i];
                if (i < pl - 1) cout << " -> ";
            }
            cout << endl;
            return;
        }

        printAllPaths(r->left, path, pl);
        printAllPaths(r->right, path, pl);
    }

    void removeNodes(AVLNode* t) {
        if (t != NULL) {
            removeNodes(t->left);
            removeNodes(t->right);
            delete t;
        }
    }

    ~BST() {
        removeNodes(root);
    }
};


int main() {
    BST tree;

    tree.insert(50);
    tree.insert(40);
    tree.insert(75);
    tree.insert(25);
    tree.insert(65);
    tree.insert(80);

    cout << "Height: " << tree.getHeight() << '\n';

    cout << "\nPre Order:\t";
    tree.preorder();

    cout << "In Order:\t";
    tree.inorder();

    cout << "\nRecursive Search 50: " << tree.recSearch(50) << endl;
    cout << "Node Count: " << tree.countNodes() << endl;
    cout << "Recursive Height: " << tree.getHeightRec() << endl;

    cout << "\nAll Root-to-Leaf Paths:\n";
    tree.printAllPaths();

    cout << "\nAfter doubleTree():\n";
    tree.doubleTree();
    tree.printAllPaths();

    return 0;
}
