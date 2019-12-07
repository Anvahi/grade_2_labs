#include <iostream>
#include <fstream>
//Написать программу построения бинарного дерева с
//помощью связных структур и поиска в дереве при симметричном
//порядке обхода его.

struct node {
    int data;
    node *left = nullptr;
    node *right = nullptr;
};

struct tree {
    node *root = nullptr;
    int count = 0;
    int number_of_elem = 0;
};

void symmetric(node *go_tr, int find) {
    if (go_tr) {
        symmetric(go_tr->left, find);
        if (go_tr->data == find)
            std::cout << "\n|||" << go_tr->data << "|||";
        else
            std::cout << "\n|" << go_tr->data << "|";
        symmetric(go_tr->right, find);
    }
}

void add(node *tr, int n) {
    if (tr != nullptr) {
        if (tr->left == nullptr) {
            tr->left = new node;
            tr->left->data = n;
            tr->left->left = nullptr;
            tr->left->right = nullptr;
        } else if (tr->right == nullptr) {
            tr->right = new node;
            tr->right->data = n;
            tr->right->left = nullptr;
            tr->right->right = nullptr;
        }
    }
}

node *search(node *tr, int count, int lvl) {
    node *temp;
    if (lvl == count - 1) {
        if (tr->left == nullptr || tr->right == nullptr)
            return tr;
        else
            return nullptr;
    }
    temp = search(tr->left, count, lvl + 1);
    if (temp != nullptr)
        return temp;
    else
        tr = search(tr->right, count, lvl + 1);
    return tr;
}

void tree_create(tree *tr, int n) {
    node *tmp = new node;
    tr->root = tmp;
    tr->root->data = n;
    tr->count = 1;
    tr->number_of_elem = 1;
}

void read_file(tree *tr) {
    int a;
    std::ifstream f("bin_tr.txt");
    f >> a;
    tree_create(tr, a);
    while (!f.eof()) {
        f >> a;
        add(search(tr->root, tr->count, 0), a);
        ++tr->number_of_elem;
        for (unsigned int i = UINT32_MAX; i > 0; i >>= 1) {
            if (!(tr->number_of_elem ^ i)) {
                ++tr->count;
                break;
            }
        }
    }
    f.close();
}

void print_tree(node *tr, int count) {
    if (tr) {
        std::cout << "| " << tr->data << "(" << count << ")";
        print_tree(tr->left, count + 1);
        print_tree(tr->right, count + 1);
    }
}

int main() {
    tree *bin_tree = new tree;
    read_file(bin_tree);
    print_tree(bin_tree->root, 0);
    int n;
    std::cout << "\nEnter the number what should be find:";
    std::cin >> n;
    symmetric(bin_tree->root, n);
    return 0;
}