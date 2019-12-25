#include <iostream>
#include <string>

using namespace std;

//Создать класс машина, имеющий марку (указатель на строку), число цилиндров,
//мощность. Определить конструкторы, деструктор и функцию печати.
//Создать public-производный класс - грузовики, имеющий грузоподъемность кузова.
//Определить конструкторы по умолчанию и с разным числом параметров, деструкторы,
//функцию печати. Определить функции переназначения марки и грузоподъемности.
//Написать программу, демонстрирующую все разработанные элементы класса.

class car {
protected:
    string Car_make;
    int cylinder;
    int power;
public:
    car() = default;

    void print() {
        cout << "Car brand is " << this->Car_make << ".\n";
        cout << "The number of cylinders is " << this->cylinder << ".\n";
        cout << "Power is " << this->power << ".\n";
    }

    ~car() = default;
};

class truck : public car {
private:
    int body_capacity;
public:
    truck() = default;

    truck(int _body_capacity) {
        this->body_capacity = _body_capacity;
    }

    truck(string s, int a, int b, int c) {
        this->Car_make = s;
        this->cylinder = a;
        this->power = b;
        this->body_capacity = c;
    }

    void set_make (string s) {
        this->Car_make = s;
    }

    void set_capas (int a) {
        this->body_capacity = a;
    }

    void print_t() {
        cout << "\nCar brand is " << this->Car_make << ".\n";
        cout << "The number of cylinders is " << this->cylinder << ".\n";
        cout << "Power is " << this->power << ".\n";
        cout << "Body capacity is " << this->body_capacity << ".\n";
    }

    ~truck() = default;
};

int main() {
    auto c = new truck("BMW", 6, 200, 40);
    c->print();
    c->print_t();

    string temp;
    cout << "Enter the new car make:";
    cin >> temp;
    c->set_make(temp);
    cout << "Enter new body capacity:";
    cin >> temp;
    c->set_capas(stoi(temp));

    c->print_t();

    return 0;
}