#include <iostream>
#include <fstream>

using namespace std;

//В первоначально пустое АВЛ-дерево были занесены
//(согласно стандартному алгоритму вставки) в указанном порядке
//следующие ключи: 20, 15, 9, 18, 40, 35, 51, 27, 37, 36. Сформировать и
//напечатать АВЛ-деревья, которые получаются после добавления
//каждого из этих ключей.

struct node { // структура для представления узлов дерева
    int key;
    unsigned char height;
    node *left;
    node *right;

    explicit node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

unsigned char height(node *p) {
    return p ? p->height : 0;
}

int bfactor(node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *rotateright(node *p) { // правый поворот вокруг p
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotateleft(node *q) { // левый поворот вокруг q
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *balance(node *p) { // балансировка узла p
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

node *insert(node *p, int k) { // вставка ключа k в дерево с корнем p
    if (!p) return new node(k);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

void print_tree(node *tr) {
    if (tr) {
        print_tree(tr->left);
        cout << "| " << tr->key << " ";
        print_tree(tr->right);
    }
}

int main() {
    node *t = nullptr;
    string temp;
    ifstream f("tree.txt");
    while (!f.eof()) {
        getline(f, temp);
        t = insert(t, stoi(temp));
        print_tree(t);
        cout << "\n\n";
    }
    return 0;
}