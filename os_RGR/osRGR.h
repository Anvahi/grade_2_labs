#ifndef OSRGR_OSRGR_H
#define OSRGR_OSRGR_H

#include <iostream>
#include<string>

using namespace std;

struct process {
    bool accepted = false;
    int number = 0; //имя
    int lead_time = 0; //время выполнения
    int start_time = 0; //время начала
    int priority = 0;
    int progress = 0;
    bool done = false;
};

int Num_quant(int n, process* p) {
    int temp = 0;
    for (int i = 0; i < n; i++) {
        temp += p[i].lead_time;
    }
    return temp;
}

void SRR(int n, process* p) {
    int rent = 0;
    cout << "Enter the rental time for all processes:";
    cin >> rent;
    while (rent < 1) {
        cout << "Please, try again!\n";
        cin >> rent;
    }
    int dA = 0, dB = 0;
    cout << "Enter the dA speed:";
    cin >> dA;
    while (dA < 1) {
        cout << "Please, try again!\n";
        cin >> dA;
    }
    cout << "Enter the dB speed:";
    cin >> dB;
    while (dB < 1) {
        cout << "Please, try again!\n";
        cin >> dB;
    }
    cout << endl;
    int Q = Num_quant(n, p);
    int min = INT32_MAX, k = 0;
    process temp;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (p[j].start_time < min) {
                min = p[j].start_time;
                k = j;
            }
        }
        temp = p[i];
        p[i] = p[k];
        p[k] = temp;
        min = INT32_MAX;
    }
    int count = 0;
    int last = 0;
    int t = 0;
    k = 0;
    for (int q = 1; q <= Q; q++) {
        int max = INT32_MIN;
        int flag = 0;
        cout << "Quantum " << q << ":";
        for (int i = 0; i < n; i++) {
            if (p[i].accepted && p[i].done) {
                flag++;
            }
        }
        if (q == 1) {
            t = 0;
            p[t].accepted = true;
        }
        if (q != 1) {
            if (count == 0) {
                if (k != flag) {
                    for (int i = 0; i < n; i++) {
                        if (p[i].start_time <= q && !p[i].done) {
                            if (p[i].accepted && p[i].progress == 0) {
                                t = i;
                                break;
                            }
                        }
                    }
                    if (q > 1 && t == last) {
                        while (true) {
                            if (!p[(t + 1) % k].done) {
                                t++;
                                t %= k;
                                break;
                            } else
                                t++;
                        }
                    }
                } else {
                    int tmp = 0;
                    for (int i = 0; i < n; i++) {
                        if (!p[i].done && p[i].priority > max) {
                            max = p[i].priority;
                            tmp = i;
                        }
                    }
                    p[tmp].accepted = true;
                    t = tmp;
                }
            }
        }
        p[t].progress++;
        cout << " process " << p[t].number << " with priority " << p[t].priority << "\n";
        for (int i = 0; i < n; i++) {
            if (p[i].accepted && !p[i].done)
                p[i].priority += dB;
            if (!p[i].accepted && p[i].start_time <= q && p[i].progress == 0)
                p[i].priority += dA;
        }
        k = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].priority == p[t].priority)
                p[i].accepted = true;
            if (p[i].accepted)
                k++;
        }
        if (p[t].lead_time == p[t].progress) {
            p[t].done = true;
        }
        count++;
        last = t;
        if (count == rent || p[t].done) {
            count = 0;
        }
        for (int i = 0; i < n; i++) {
            cout << "\tprocess " << p[i].number << " priority " << p[i].priority << " accepted " << p[i].accepted << " is dead " << p[i].done << "\n";
        }
    }
}

#endif