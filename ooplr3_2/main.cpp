#include <iostream>
#include <list>
#include <string>
#include <fstream>

using namespace std;

//Разработать экзаменационную ведомость для курса. Получать средний балл по
//предмету в группе, по предмету во всех группах, средний по группе и средний по
//факультету, определить группу, в которой учатся отличники.

class sheet {
private:
    string subject = "";
    string faculty = "";
    int course = 0;
    string group = "";
    string surname = "";
    double mark = 0;
public:
    sheet() = default;

    void set_sub(string s) {
        this->subject = s;
    }

    void set_fac(string s) {
        this->faculty = s;
    }

    void set_cour(int a) {
        this->course = a;
    }

    void set_gr(string s) {
        this->group = s;
    }

    string get_gr() {
        return this->group;
    }

    void set_sur(string s) {
        this->surname = s;
    }

    void set_mark(double a) {
        this->mark = a;
    }

    double aver_subj_gr(list<sheet> sh, string gr, string subj) {
        double count = 0;
        double sum = 0;
        for (auto iter = sh.begin(); iter != sh.end(); iter++) {
            if (iter->group == gr && iter->subject == subj) {
                sum += iter->mark;
                count++;
            }
        }
        return (sum /= count);
    }

    double aver_subj(list<sheet> sh, string subj) {
        double count = 0;
        double sum = 0;
        for (auto iter = sh.begin(); iter != sh.end(); iter++) {
            if (iter->subject == subj) {
                sum += iter->mark;
                count++;
            }
        }
        return (sum /= count);
    }

    double aver_gr(list<sheet> sh, string gr) {
        double count = 0;
        double sum = 0;
        for (auto iter = sh.begin(); iter != sh.end(); iter++) {
            if (iter->group == gr) {
                sum += iter->mark;
                count++;
            }
        }
        return (sum /= count);
    }

    double aver_fact(list<sheet> sh, string fact) {
        double count = 0;
        double sum = 0;
        for (auto iter = sh.begin(); iter != sh.end(); iter++) {
            if (iter->faculty == fact) {
                sum += iter->mark;
                count++;
            }
        }
        return (sum /= count);
    }

    double aver_all_gr(list<sheet> sh) {
        double count = 0;
        double sum = 0;
        for (auto iter = sh.begin(); iter != sh.end(); iter++) {
            sum += iter->mark;
            count++;
        }
        return (sum /= count);
    }

    ~sheet() = default;
};

void read_file(list<sheet> &sh) {
    ifstream read("sheet.txt");
    string tmp;
    while (!read.eof()) {
        sheet temp;
        getline(read, tmp);
        temp.set_sub(tmp);
        getline(read, tmp);
        temp.set_fac(tmp);
        getline(read, tmp);
        temp.set_cour(stoi(tmp));
        getline(read, tmp);
        temp.set_gr(tmp);
        getline(read, tmp);
        temp.set_sur(tmp);
        getline(read, tmp);
        temp.set_mark(stod(tmp));
        sh.push_back(temp);
    }
    read.close();
}

void read_key(list<sheet> &sh) {
    string tmp;
    while (true) {
        sheet temp;
        cout << "Enter subject:";
        cin >> tmp;
        temp.set_sub(tmp);
        cout << "Enter faculty:";
        cin >> tmp;
        temp.set_fac(tmp);
        cout << "Enter course:";
        cin >> tmp;
        while (stoi(tmp) < 1 || stoi(tmp) > 5) {
            cout << "Please, try again!\n";
            cin >> tmp;
        }
        temp.set_cour(stoi(tmp));
        cout << "Enter group:";
        cin >> tmp;
        temp.set_gr(tmp);
        cout << "Enter surname:";
        cin >> tmp;
        temp.set_sur(tmp);
        cout << "Enter mark:";
        cin >> tmp;
        while (stod(tmp) < 1 || stod(tmp) > 5) {
            cout << "Please, try again!\n";
            cin >> tmp;
        }
        temp.set_mark(stod(tmp));
        sh.push_back(temp);

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
}

int main() {
    list<sheet> sh;

    int choice;
    cout << "How are you want to enter the information?\n"
            "1. From file\n"
            "2. From keyboard\n";
    cin >> choice;
    while (choice < 1 || choice > 2) {
        cout << "Please, try again!\n";
        cin >> choice;
    }
    switch (choice) {
        case 1:
            read_file(sh);
            break;
        case 2:
            read_key(sh);
            break;
        default:
            break;
    }
    sheet tmp;
    string a, b;
    cout << "What are you want to do?\n"
            "1. Find average mark in group on subject\n"
            "2. Find average mark on subject\n"
            "3. Find average mark in group\n"
            "4. Find average mark in faculty\n"
            "5. Find the group with best marks\n";
    cin >> choice;
    while (choice < 1 || choice > 5) {
        cout << "Please, try again!\n";
        cin >> choice;
    }
    switch (choice) {
        case 1: {
            cout << "Please, enter group:";
            cin >> a;
            cout << "Please, enter subject:";
            cin >> b;
            cout << "Average mark in group on subject is " << tmp.aver_subj_gr(sh, a, b) << ".\n";
        }
            break;
        case 2: {
            cout << "Please, enter subject:";
            cin >> b;
            cout << "Average mark on subject is " << tmp.aver_subj(sh, b) << ".\n";
        }
            break;
        case 3: {
            cout << "Please, enter group:";
            cin >> a;
            cout << "Average mark in group is " << tmp.aver_gr(sh, a) << ".\n";
        }
            break;
        case 4: {
            cout << "Please, enter faculty:";
            cin >> a;
            cout << "Average mark in faculty is " << tmp.aver_fact(sh, a) << ".\n";
        }
            break;
        case 5: {
            double max = 0;
            for (auto iter = sh.begin(); iter != sh.end(); iter++) {
                if (iter->aver_all_gr(sh) > max)
                    b = iter->get_gr();
            }
            cout << "Group with the best mark is " << b << ".";
        }
        default:
            break;
    }
    return 0;
}