// Heapuri

#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> range(0, 1);

struct Node {
    int value;
    Node *st, *dr;
    Node *parent;

    Node() : value(0), st(nullptr), dr(nullptr), parent(nullptr) {}
    Node(int value) : value(value), st(nullptr), dr(nullptr), parent(nullptr) {}
    Node(int value, Node *parent) : value(value), st(nullptr), dr(nullptr), parent(parent) {}
    Node(Node* other) : value(other->value), 
    st(other->st), dr(other->dr), parent(other->parent) {}
};

Node* join(Node* a, Node* b){
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->value < b->value) {
        if(range(gen) == 0){
            a->st = join(a->st, b);
            a->st->parent = a;
        }
        else{
            a->dr = join(a->dr, b);
            a->dr->parent = a;
        }
    }
    else{
        if(range(gen) == 0){
            b->st = join(a, b->st);
            b->st->parent = b;
        }
        else{
            b->dr = join(a, b->dr);
            b->dr->parent = b;
        }
    }
}

void insert(Node* root, int x){
    root = join(new Node(x), root);
}

int extract_min(Node* root){
    int minim = root->value;
    root = join(root->st, root->dr);
    return minim;
}

void decrease_key(Node* node, int x){
    
}

int main(){

}