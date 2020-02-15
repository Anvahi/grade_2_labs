#include <iostream>

#define n 5
using namespace std;

struct item {
    int key;
};

void HeapSort(item a[]) {
    int left, right;
    item temp;
    void sift(item [], int, int);
    left = (n - 1) / 2 + 1;
    right = n - 1;
    while (left > 1) {
        left--;
        sift(a, left, right);
    }
    while (right > 1) {
        temp = a[1];
        a[1] = a[right];
        a[right] = temp;
        right--;
        sift(a, left, right);
    }
}

int main() {
    item a[n];
    cout << "Please, enter:\n";
    for (int i = 0; i < n; i++)
        cin >> a[i].key;
    HeapSort(a);
    for (int i = 0; i < n; i++)
        cout << a[i].key;
}

void sift(item a[], int left, int right) {
    int i, j;
    item temp;
    i = left;
    j = 2 * i;
    temp = a[i];
    while (j <= right) {
        if (j < right)
            if (a[j].key < a[j + 1].key) j++;
        if (temp.key >= a[j].key) goto L1;
        a[i] = a[j];
        i = j;
        j = 2 * i;
    }
    L1:
    a[i] = temp;
}