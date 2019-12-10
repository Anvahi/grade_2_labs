#include <iostream>
#include <fstream>

class Complex {
private:
    double val;
    double img;
public:
    Complex() = default;

    explicit Complex(double va, double im) {
        this->val = va;
        this->img = im;
    }

    void set_val(int a) {
        val = a;
    }

    void set_img(int b) {
        img = b;
    }

    double get_val() {
        return val;
    }

    double get_img() {
        return img;
    }

    void print(Complex &a) {
        if (a.img == 0)
            std::cout << a.val << "\n";
        if (a.img < 0)
            std::cout << a.val << a.img << "i" << "\n";
        else
            std::cout << a.val << "+" << a.img << "i" << "\n";
    }

    friend std::ostream &operator<<(std::ostream &out, const Complex &a);

    Complex operator+(const Complex &a);

    Complex operator-(const Complex &a);

    Complex operator*(const Complex &a);

    Complex operator/(const Complex &a);

    ~Complex() = default;
};

std::ostream &operator<<(std::ostream &out, const Complex &a) {
    if (a.img == 0)
        out << a.val << "\n";
    if (a.img < 0)
        out << a.val << a.img << "i" << "\n";
    else
        out << a.val << "+" << a.img << "i" << "\n";
    return out;
}

Complex Complex::operator+(const Complex &a) {
    Complex temp(val + a.val, img + a.img);
    return temp;
}

Complex Complex::operator-(const Complex &a) {
    Complex temp(val - a.val, img - a.img);
    return temp;
}

Complex Complex::operator*(const Complex &a) {
    Complex temp((val * a.val - img * a.img), (val * a.img + img * a.val));
    return temp;
}

Complex Complex::operator/(const Complex &a) {
    Complex temp((val * a.val + img * a.img) / (a.val * a.val + a.img * a.img),
                 (img * a.val - val * a.img) / (a.val * a.val + a.img * a.img));
    return temp;
}

class Vector : Complex {
private:
    Complex *vec;
    static int N;
public:
    Vector(int N) {
        this->vec = new Complex[N];
    }

    void set_N(int n) {
        N = n;
    }

    void set_vec1(Complex t, int i){
        vec[i] = t;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &A);

    Complex operator+(const Vector &A);

    Vector operator-(const Vector &A);

    Vector operator*(const Vector &A);

    Vector operator/(const Vector &A);

    ~Vector() = default;
};

std::ostream &operator<<(std::ostream &out, const Vector &A) {
    out << "";
    return out;
}

Complex Vector::operator+(const Vector &A) {
    auto *temp = new Complex();
    for (int i = 0; i < A.N; i++){
        temp[i] = A.vec[i]+vec[i];
    }
    return *temp;
}

Vector Vector::operator-(const Vector &A) {
    auto *temp = new Vector(N);
    for (int i = 0; i < A.N; i++){
        temp[i] = A.vec[i]-vec[i];
    }
    return *temp;
}

Vector Vector::operator*(const Vector &A) {
    auto *temp = new Vector(N);

    return *temp;
}

Vector Vector::operator/(const Vector &A) {
    auto *temp = new Vector(N);
    return *temp;
}

void init(Complex *num, int N) {
    int val, img;
    for (int i = 0; i < N; i++) {
        std::cout << "Enter the valid part of " << i + 1 << " number:";
        std::cin >> val;
        num[i].set_val(val);
        std::cout << "Enter the imaginary part of " << i + 1 << " number:";
        std::cin >> img;
        num[i].set_img(img);
    }
}

int main() {
    int cou = 2;
    auto *num = new Complex[cou];
    int choice = 0;
    std::cout << "Please, choose operation:\n"
                 "1.Addition\n"
                 "2.Subtraction\n"
                 "3.Multiplication\n"
                 "4.Division\n"
                 "5.Vector addition\n"
                 "6.Subtraction of vectors\n"
                 "7.Multiplication of a vector by a number\n"
                 "8.Calculation of the scalar product of vectors\n"
                 "9.Vector module\n";
    std::cin >> choice;
    while (choice < 1 || choice > 9) {
        std::cout << "Please, try again!\n";
        std::cin >> choice;
    }
    switch (choice) {
        case 1: {
            init(num, cou);
            std::cout << num[0] + num[1];
        };
            break;
        case 2: {
            init(num, cou);
            std::cout << num[0] - num[1];
        };
            break;
        case 3: {
            init(num, cou);
            std::cout << num[0] * num[1];
        };
            break;
        case 4: {
            init(num, cou);
            std::cout << num[0] / num[1];
        };
            break;
        case 5: {

        };
            break;
        case 6: {

        };
            break;
        case 7: {

        };
            break;
        case 8: {

        };
            break;
        case 9: {

        };
            break;
        default:
            break;
    }
    delete[] num;
    return 0;
}