#include <iostream>
#include<string>

using namespace std;

struct process {
    int number = 0; //имя
    int lead_time = 0; //время выполнения
    int start_time = 0; //время начала
    int progress = 0;
    bool done = false;
};

void PSJF(int np, process *proc);
void RR_SJF(int np, process *proc);

int main() {
    int n = 0;
    cout << "Choose the algorithm:\n1. Round-robin Shortest Job First(RR SJF)\n2. Preemptive Shortest Job First (PSJF)\n";
    cin >> n;
    while (n < 1 || n > 2) {
        cout << "Please, try again!\n";
        cin >> n;
    }
    int np;
    cout << "Enter the number of processes:";
    cin >> np;
    while (np < 2) {
        cout << "Please, try again!\n";
        cin >> np;
    }
    auto *proc = new process[np];
    for (int i = 0; i < np; i++) {
        int temp;
        proc[i].number = i;
        cout << "Enter the lead time of " << i << " process:";
        cin >> temp;
        proc[i].lead_time = temp;
        cout << "Enter the start time of " << i << " process:";
        cin >> temp;
        proc[i].start_time = temp;
        proc[i].done = false;
    }
    switch (n) {
        case 1: RR_SJF(np, proc);
            break;
        case 2: PSJF(np, proc);
            break;
        default:
            break;
    }
    return 0;
}

int Num_quant(int np, process *proc) {
    int temp = 0;
    for (int i = 0; i < np; i++) {
        temp += proc[i].lead_time;
    }
    return temp;
}

void PSJF(int np, process *proc) {
    int p = 0;
    bool h = false;
    int Q = Num_quant(np, proc);
    for (int q = 1; q <= Q; q++) {
        cout << "Quantum " << q << ":";
        int min = INT32_MAX;
        for (int i = 0; i < np; i++) {
            if (proc[i].start_time == q && !h) {
                if (proc[i].lead_time <= (proc[p].lead_time - proc[p].progress)) {
                    p = i;
                }
            } else if (h) {
                for (int j = 0; j < np; j++) {
                    if ((proc[j].lead_time - proc[j].progress) < min && !proc[j].done) {
                        min = proc[j].lead_time - proc[j].progress;
                        p = j;
                    }
                }
            }
        }
        proc[p].progress++;
        cout << "process " << p << "\n";
        if (proc[p].lead_time == proc[p].progress) {
            proc[p].done = true;
            h = true;
        }
    }
}

void RR_SJF(int np, process *proc) {
    int rent = 0;
    cout << "Enter the rental time for all processes:";
    cin >> rent;
    int Q = Num_quant(np, proc);
    int p = 0;
    int count = 0;
    int min = INT32_MAX, k = 0;
    process temp;
    for (int i = 0; i < np; i++) {
        for (int j = i; j < np; j++) {
            if (proc[j].start_time < min) {
                min = proc[j].start_time;
                k = j;
            }
        }
        temp = proc[i];
        proc[i] = proc[k];
        proc[k] = temp;
        min = INT32_MAX;
    }
    int last = 0;
    bool l = false;
    for (int q = 1; q <= Q; q++) {
        cout << "Quantum " << q << ":";
        for (int i = 0; i < np; i++) {
            if (!l && proc[i].start_time == q) {
                p = i;
                l = true;
            }
            if (proc[i].start_time <= q && !proc[i].done && count == 0 && l) {
                if (proc[last].done) {
                    for (int j = 0; j < np; j++) {
                        if ((proc[j].lead_time - proc[j].progress) < min && !proc[j].done) {
                            min = proc[j].lead_time - proc[j].progress;
                            p = j;
                        }
                    }
                } else if (((proc[i].lead_time - proc[i].progress) < (proc[p].lead_time - proc[p].progress))) {
                    p = i;
                }
            }
        }
        proc[p].progress++;
        cout << "process " << proc[p].number << "\n";
        if (proc[p].lead_time == proc[p].progress) {
            proc[p].done = true;
            min = INT32_MAX;
        }
        count++;
        last = p;
        if (count == rent || proc[p].done) {
            count = 0;
            min = INT32_MAX;
        }
    }
}