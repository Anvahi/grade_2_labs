#include "osRGR.h"

int main() {
    int n;
    cout << "Enter the number of processes:";
    cin >> n;
    while (n < 2) {
        cout << "Please, try again!\n";
        cin >> n;
    }
    auto* p = new process[n];
    for (int i = 0; i < n; i++) {
        int temp;
        p[i].number = i;
        cout << "Enter the lead time of " << i << " process:";
        cin >> temp;
        p[i].lead_time = temp;
        cout << "Enter the start time of " << i << " process:";
        cin >> temp;
        p[i].start_time = temp;
        p[i].done = false;
    }
    SRR(n, p);
    return 0;
}