#include <iostream>

using namespace std;

//Очередь. Вставка элемента. Удаление. Поиск минимального. Очистка. Поиск количества вхождений заданного элемента. Печать
// double
// Линейный список
// Student: Фамилия, Имя, Отчество, Дата рождения,

template<class type>
class que {
    struct Element { // структура представляющая единичный элемент очереди
        type data; // информационное поле (сюда линейный список)
        Element *next; // указатель на следующий элемент
    };
private:
    Element *Head; // указатель на голову
    Element *Tail; // указатель на текущий элемент
public:
    int length = 0; // количество элементов

    que() = default;

    que(type data) {
        Head = nullptr;
        Tail = nullptr;
        length = 0;
        Add(data, 1);
    }

    void Add(type data) {
        auto insert = new Element;
        insert->data = data;
        insert->next = nullptr;
        if (length != 0) {
            Tail->next = insert;
            Tail = insert;
        } else
            Head = Tail = insert;
        length++;
    }

    void out() {
        if (length != 0) {
            Element *temp = Head;
            for (int i = 0; i < length; i++) {
                cout << temp->data << endl;
                temp = temp->next;
            }
        } else
            cout << "Queue is empty\n";
    }

    void del(type data) {
        Element *temp = Head;
        while (temp->next->data != data) {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        delete temp;
        length--;
    }

    void Clear() {
        for (int i = 0; i < length; i++) {
            Element *temp = Head;
            Head = Head->next;
            delete temp;
        }
    }

    void find_min(type &min) {
        if (length != 0) {
            Element *temp = Head;
            min = temp->data;
            for (int i = 0; i < length; i++) {
                temp = temp->next;
                if (temp->data < min)
                    min = temp->data;
            }
        } else
            cout << "Queue is empty\n";
    }

    void find_min(type f, int &count) {
        if (length != 0) {
            Element *temp = Head;
            for (int i = 0; i < length; i++) {
                if (temp->data == f) {
                    count++;
                    temp = temp->next;
                } else
                    temp = temp->next;
            }
        } else
            cout << "Queue is empty\n";
    }

    ~que() = default;
};

class Student {
private:
    string surname = "";
    string name = "";
    string second_name = "";
    int age = 0;
public:
    Student() = default;

//    void set_sur (string sur) {
//        this->surname = sur;
//    }
//
//    void set_nam (string nam) {
//        this->name = nam;
//    }
//
//    void set_sec_nam (string sec_nam) {
//        this->second_name = sec_nam;
//    }
//
//    void set_age (int ag) {
//        this->age = ag;
//    }
//
//    string get_sur() {
//        return this->surname;
//    }
//
//    string get_nam() {
//        return this->name;
//    }
//
//    string get_sec_nam() {
//        return this->second_name;
//    }
//
//    int get_age() {
//        return this->age;
//    }

    void init() {
        cout << "Enter the surname:";
        cin >> this->surname;
        cout << "Enter the name:";
        cin >> this->name;
        cout << "Enter the second name:";
        cin >> this->second_name;
        cout << "Enter the surname:";
        cin >> this->age;
    }

    ~Student() = default;
};

class List {
private:
    Student el;
    List *next = nullptr;
public:
    int count = 0;

    List() = default;

    void create() {
        auto temp = new List;
        temp->el.init();
        temp->next = nullptr;
        count++;
    }

    void add() {
        auto temp = new List;
        temp->el.init();
        temp->next = nullptr;
        count++;
//        string temp;
//        cout << "Enter the surname:";
//        cin >> temp;
//        el.set_sur(temp);
//        cout << "Enter the name:";
//        cin >> temp;
//        el.set_nam(temp);
//        cout << "Enter the second name:";
//        cin >> temp;
//        el.set_sec_nam(temp);
//        cout << "Enter the surname:";
//        cin >> temp;
//        el.set_age(stoi(temp));
    }

    ~List() = default;
};

int main() {
    int choice;
    string temp;
    cout << "1. double\n"
            "2. class\n";
    cin >> choice;
    switch (choice) {
        case 1:
            que <double> f;
            while (true) {
                cout << "If you want to add elements - enter the number, else type \"no\"\n";
                cin >> temp;
                if (temp == "no")
                    break;
                else
                    f.Add(stoi(temp));
            }
            cout << endl;
            f.out();
            break;
//        case 2: ;
//            break;
//        default:
//            break;
    }
    return 0;
}