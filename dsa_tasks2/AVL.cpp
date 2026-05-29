#include <iostream>
using namespace std;

class Node {
public:
    Node* lchild;
    int data;
    int height;
    Node* rchild;

    Node(int val) : lchild(nullptr), data(val), height(1), rchild(nullptr) {}
};

class AVL {
private:
    Node* root;

public:
    AVL() : root(nullptr) {}

    // Helper methods
    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    Node* LLRotation(Node* p);
    Node* RRRotation(Node* p);
    Node* LRRotation(Node* p);
    Node* RLRotation(Node* p);

    // Insert public wrapper
    void Insert(int key) { root = rInsert(root, key); }
    Node* rInsert(Node* p, int key);

    // Traversal
    void Inorder(Node* p);
    void Inorder() { Inorder(root); }
    Node* getRoot() { return root; }

    // Delete
    Node* deleteNode(Node* p, int key);
    Node* InPre(Node* p);
    Node* InSucc(Node* p);
};

// return 0 for nullptr, 1 for leaf, etc.
int AVL::NodeHeight(Node* p) {
    if (!p) return 0;
    int hl = p->lchild ? p->lchild->height : 0;
    int hr = p->rchild ? p->rchild->height : 0;
    return (hl > hr ? hl : hr) + 1;
}

int AVL::BalanceFactor(Node* p) {
    if (!p) return 0;
    int hl = p->lchild ? p->lchild->height : 0;
    int hr = p->rchild ? p->rchild->height : 0;
    return hl - hr;
}

Node* AVL::LLRotation(Node* p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;

    pl->rchild = p;
    p->lchild = plr;

    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);

    return pl;
}

Node* AVL::RRRotation(Node* p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);

    return pr;
}

Node* AVL::LRRotation(Node* p) {
    // First rotate left child to left (RR on left child), then LL on p
    p->lchild = RRRotation(p->lchild);
    return LLRotation(p);
}

Node* AVL::RLRotation(Node* p) {
    // First rotate right child to right (LL on right child), then RR on p
    p->rchild = LLRotation(p->rchild);
    return RRRotation(p);
}

Node* AVL::rInsert(Node* p, int key) {
    if (p == nullptr) {
        return new Node(key);
    }

    if (key < p->data) {
        p->lchild = rInsert(p->lchild, key);
    } else if (key > p->data) {
        p->rchild = rInsert(p->rchild, key);
    } else {
        // duplicate key - do nothing (or handle as needed)
        return p;
    }

    // update height
    p->height = NodeHeight(p);

    int bf = BalanceFactor(p);

    // Left heavy
    if (bf == 2) {
        int left_bf = BalanceFactor(p->lchild); // safe even if lchild == nullptr
        if (left_bf >= 0) {
            // LL
            return LLRotation(p);
        } else {
            // LR
            return LRRotation(p);
        }
    }
    // Right heavy
    if (bf == -2) {
        int right_bf = BalanceFactor(p->rchild);
        if (right_bf <= 0) {
            // RR
            return RRRotation(p);
        } else {
            // RL
            return RLRotation(p);
        }
    }

    return p;
}

void AVL::Inorder(Node* p) {
    if (p) {
        Inorder(p->lchild);
        cout << p->data << " ";
        Inorder(p->rchild);
    }
}

// Optional helpers for delete
Node* AVL::InPre(Node* p) {
    if (!p) return nullptr;
    while (p->rchild) p = p->rchild;
    return p;
}

Node* AVL::InSucc(Node* p) {
    if (!p) return nullptr;
    while (p->lchild) p = p->lchild;
    return p;
}

Node* AVL::deleteNode(Node* p, int key) {
    if (!p) return nullptr;

    if (key < p->data) {
        p->lchild = deleteNode(p->lchild, key);
    } else if (key > p->data) {
        p->rchild = deleteNode(p->rchild, key);
    } else {
        // found
        if (!p->lchild && !p->rchild) {
            delete p;
            return nullptr;
        } else if (p->lchild && !p->rchild) {
            Node* q = p->lchild;
            *p = *q; // copy contents (simple approach)
            // Note: copying like this leaks node q; a safer approach is restructure pointers.
            // For simplicity, replace node via standard method below instead.
        }

        if (p->lchild && p->rchild) {
            // both children: use inorder predecessor or successor
            if (NodeHeight(p->lchild) > NodeHeight(p->rchild)) {
                Node* q = InPre(p->lchild);
                p->data = q->data;
                p->lchild = deleteNode(p->lchild, q->data);
            } else {
                Node* q = InSucc(p->rchild);
                p->data = q->data;
                p->rchild = deleteNode(p->rchild, q->data);
            }
        } else if (p->lchild) {
            Node* tmp = p->lchild;
            delete p;
            return tmp;
        } else if (p->rchild) {
            Node* tmp = p->rchild;
            delete p;
            return tmp;
        }
    }

    // update height and balance
    p->height = NodeHeight(p);
    int bf = BalanceFactor(p);

    if (bf == 2) {
        int left_bf = BalanceFactor(p->lchild);
        if (left_bf >= 0) return LLRotation(p);
        else return LRRotation(p);
    } else if (bf == -2) {
        int right_bf = BalanceFactor(p->rchild);
        if (right_bf <= 0) return RRRotation(p);
        else return RLRotation(p);
    }

    return p;
}

int main() {
    AVL tree;

    // Use public Insert so root is updated properly
    tree.Insert(50);
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(30);
    tree.Insert(40);
    tree.Insert(25);

    cout << "Inorder traversal of AVL tree: ";
    tree.Inorder();
    cout << endl;

    // Second test
    AVL tree2;
    int arr[] = {10, 20, 30, 25, 28, 27, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        tree2.Insert(arr[i]);
    }

    cout << "Inorder traversal of second AVL tree: ";
    tree2.Inorder();
    cout << endl;

    return 0;
}
