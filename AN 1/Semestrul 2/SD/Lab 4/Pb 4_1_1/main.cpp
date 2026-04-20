// Idee ca sa fie cat de cat balansat
// fac mediana din 5 a vectorului de input si folosesc aceasta mediana ca root

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> ud(0, 100);

struct Node{
    int key, priority;
    Node *left, *right;

    Node(int key) : 
    key(key), priority(ud(gen)), left(nullptr), right(nullptr)
    {}
};

class Treap{
private:
    Node* _root;

    Node* rightRotate(Node* y){
        Node *x = y->left, *T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    Node* leftRotate(Node* x){
        Node *y = x->right, *T2 = y->left;
        y->left = x;
        x->right = T2;
        return y;
    }

    bool exists(Node* root, int key){
        if(root == nullptr){
            return false;
        }
        if(root->key == key){
            return true;
        }
        if(root->key < key){
            return exists(root->right, key);
        }
        return exists(root->left, key);
    }

    Node* insert(Node* root, int key){
        if(root == nullptr){
            return new Node(key);
        }
        if(key < root->key){
            root->left = insert(root->left, key);
            if(root->left->priority > root->priority){
                root = rightRotate(root);
            }
        }
        else if(key > root->key){
            root->right = insert(root->right, key);
            if(root->right->priority > root->priority){
                root = leftRotate(root);
            }
        }
        return root;
    }

    Node* erase(Node* root, int key){
        if(root == nullptr){
            return root;
        }
        if(key < root->key){
            root->left = erase(root->left, key);
        }
        else if(key > root->key){
            root->right = erase(root->right, key);
        }
        else if(root->left == nullptr){
            Node* aux = root->right;
            delete root;
            root = aux;
        }
        else if(root->right == nullptr){
            Node* aux = root->left;
            delete root;
            root = aux;
        }
        else if(root->left->priority < root->right->priority){
            root = leftRotate(root);
            root->left = erase(root->left, key);
        }
        else{
            root = rightRotate(root);
            root->right = erase(root->right, key);
        }
        return root;
    }

    void destroy(Node* root){
        if(root == nullptr) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

public:
    Treap() : _root(nullptr) {}
    ~Treap() { destroy(_root); }

    bool exists(int key) { return exists(_root, key); }
    void insert(int key) { _root = insert(_root, key); }
    void erase(int key) { _root = erase(_root, key); }
    Node* root() const { return _root; }

    void construct(const std::vector<int>& v){
        for(int x : v) insert(x);
    }

    int predecessor(int x){
        Node* cur = _root;
        int res = -1;
        while(cur){
            if(cur->key < x){
                res = cur->key;
                cur = cur->right;
            }else{
                cur = cur->left;
            }
        }
        return res;
    }

    int successor(int x){
        Node* cur = _root;
        int res = -1;
        while(cur){
            if(cur->key > x){
                res = cur->key;
                cur = cur->left;
            }else{
                cur = cur->right;
            }
        }
        return res;
    }
};