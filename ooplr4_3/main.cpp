#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;

//Дан текст. Каких прописных русских букв в нем нет? Определите
//общее количество символов + и - в нем.

void find_symbols (string k) {
    int count = 0;
    for (int i = 0; i < k.size(); i++) {
        if (k[i] == '-' || k[i] == '+')
            count++;
    }
    cout << "Total amount of symbols + and - is " << count << ".\n";
}

void find_letters (string k) {
    string lett;
    bool hz;
    for (int i = 65; i < 91; i++) {
        hz = false;
        for (int j = 0; j < k.size(); j++){
            if (k[j] == i && k[j] < 91 && k[j] > 64)
                hz = true;
        }
        if (!hz)
            lett += i;
    }
    cout << "No capital letters in the text:" << lett << ".\n";
}

int main() {
    chrono::high_resolution_clock::time_point t1, t2;
    string k;
    string temp;
    ifstream f("text.txt");
    while (!f.eof()) {
        getline(f, temp);
        k += temp;
    }
    int ch = 0;
    cout << "Choose the function:\n"
            "1. Find the letter\n"
            "2. Find the symbols\n";
    cin >> ch;
    switch (ch) {
        case 1: {
            t1 = chrono::high_resolution_clock::now();
            find_letters(k);
            t2 = chrono::high_resolution_clock::now();
        } break;
        case 2: {
            t1 = chrono::high_resolution_clock::now();
            find_symbols(k);
            t2 = chrono::high_resolution_clock::now();
        } break;
        default:
            break;
    }
    cout << "\nTime: " << chrono::duration_cast<chrono::nanoseconds>( t2 - t1 ).count() << endl;
    f.close();
    return 0;
}