#include <iostream>
#include <set>

using namespace std;

int main() {
    multiset<int> num;
    for (int i = 0;; i++) {
        int temp = 0;
        cout << "Enter the " << i + 1 << " number of set:";
        cin >> temp;
        num.insert(temp);
        string again;
        cout << "Do you want to continue typing? (yes/no)\n";
        cin >> again;
        while (again != "yes" && again != "no") {
            cout << "Please, try again!\n";
            cin >> again;
        }
        if (again == "yes")
            continue;
        else if (again == "no")
            break;
    }
    int max = 0;
    int x = 0;
    for (int i = 0; i < 10; i++) {
        if (num.count(i) > max) {
            max = num.count(i);
            x = i;
        } else
            continue;
    }
    cout << "Number " << x << " is more common than other.";
    return 0;
}