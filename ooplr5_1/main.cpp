#include <iostream>
// Интернет-соединение (Dial-Up, ADSL, 4G, выделенная линия).
// Функция вычисления времени передачи файла объемом N ГБ
// (скорости определить самостоятельно).
// Найти самое короткое время передачи файла.
using namespace std;
//скорость в килобитах
class Internet {
public:
    virtual double time (double N) = 0 ;
};

class Dial_Up : public Internet {
private:
    static const int V = 56;
public:
    Dial_Up() = default;

   virtual double time (double N) override {
        return N/Dial_Up::V;
    }

    ~Dial_Up() = default;
};

class ADSL : public Internet {
private:
    static const int V = 8000;
public:
    ADSL() = default;

    virtual double time (double N) override {
        return N/ADSL::V;
    }

    ~ADSL() = default;
};

class four_G : public Internet{
private:
    static const int V = 34234;
public:
    four_G() = default;

    virtual double time (double N) override {
        return N/four_G::V;
    }

    ~four_G() = default;
};

class Ethernet : public Internet {
private:
    static const int V = 456953;
public:
    Ethernet() = default;

    virtual double time (double N) override {
        return N/Ethernet::V;
    }

    ~Ethernet() = default;
};

int main() {
    int N;
    int n = 1;
    cout << "Enter the file size in kilobits:";
    cin >> N;
    double min = INT32_MAX;
    Internet *F[4];
    F[0] = new Dial_Up();
    F[1] = new ADSL();
    F[2] = new four_G();
    F[3] = new Ethernet();
    for (int i = 0; i < 4; i++) {
        if (F[i]->time(N) < min)
            min = F[i]->time(N);
    }
    cout << endl << min << "Kbit" << endl;
    return 0;
}