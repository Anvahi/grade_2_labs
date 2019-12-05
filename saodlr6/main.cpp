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

struct tree{
    node *root = nullptr;
};

int insert (node *tr, int n){ //wtf
    if (n > tr->data){
        if (tr->left == nullptr){
            node *tmp = new node;
            tmp->data = n;
            tr->left = tmp;
        }
        else insert(tr->left, n);
    }
    else if (n < tr->data){
        if (tr->right == nullptr){
            node *tmp = new node;
            tmp->data = n;
            tr->right = tmp;
        }
        else insert(tr->right, n);
    }
}

void tree_create(tree * tr, int n) {
    if (tr->root == nullptr){
        node *tmp = new node;
        tr->root = tmp;
        tr->root->data = n;
    }
    else insert(tr->root, n);
}

void symmetric(node * go_tr, int find){
    if (go_tr){
        symmetric(go_tr->left, find);
        std::cout << "\n|" << go_tr->data << "|";
        if (go_tr->data == find)
            std::cout << "\n|||" << go_tr->data << "|||";
        symmetric(go_tr->right, find);
    }
}

void read_file(tree* tr){
    int a;
    std::ifstream f("bin_tr.txt");
    while (!f.eof()){
        f >> a;
        tree_create(tr, a);
    }
    f.close();
}

void print_tree(node *tr){ //along
    if (tr){
        std::cout << "| " << tr->data << " ";
        print_tree(tr->left);
        print_tree(tr->right);
    }
}

int main() {
    tree *bin_tree = new tree;
    read_file(bin_tree);
    print_tree(bin_tree->root);
    int n;
    std::cout << "\nEnter the number what should be find:";
    std::cin >> n;
    symmetric(bin_tree->root, n);
    return 0;
}














//struct tree * tree_create() {
//    tree *new_tr = new tree;
//    new_tr->root = nullptr;
//    return new_tr;
//}

//int insert (tree *sear_tr, int n){
//    node *sear_no, **new_no;
//    new_no = &sear_tr->root;
//    sear_no = sear_tr->root;
//    for(;;){
//        if (sear_no == nullptr){
//            sear_no = *new_no = new node;
//            if(sear_no != nullptr){
//                sear_no->data = n;
//                sear_no->left = sear_no->right = nullptr;
//                return 1;
//            } else
//                return 0;
//        } else if (n == sear_no->data) return 2;
//        else if (n > sear_no->data){
//            new_no = &sear_no->right;
//            sear_no = sear_no->right;
//        }
//        else {
//            new_no = &sear_no->left;
//            sear_no = sear_no->left;
//        }
//    }
//}