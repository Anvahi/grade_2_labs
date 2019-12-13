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

    Complex operator=(const Complex &a);

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

Complex Complex::operator=(const Complex &a) {
    val = a.val;
    img = a.img;
    return (*this);
}

class Vector {
private:
    Complex *vec;
public:
    static int N;
    explicit Vector(int N = 2) {
        this->vec = new Complex[N];
    }

    void set_vec(Complex t, int i){
        this->vec[i] = t;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &A);

    Vector operator+(const Vector &A);

    Vector operator-(const Vector &A);

    ~Vector() = default;
};

std::ostream &operator<<(std::ostream &out, const Vector &A) {
    for (int i = 0; i < Vector::N; i++) {
        out << A.vec[i] << "\n";
    }
    return out;
}

Vector Vector::operator+(const Vector &A) {
    auto temp = new Vector(N);
    for (int i = 0; i < N; i++){
        temp->vec[i] = A.vec[i]+this->vec[i];
    }
    return *temp;
}

Vector Vector::operator-(const Vector &A) {
    auto temp = new Vector(N);
    for (int i = 0; i < N; i++){
        temp->vec[i] = A.vec[i]-vec[i];
    }
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

void initial(Complex &num) {
    int val, img;
    std::cout << "Enter the valid part of number:";
    std::cin >> val;
    num.set_val(val);
    std::cout << "Enter the imaginary part of number:";
    std::cin >> img;
    num.set_img(img);
}

void init_v(Vector *v) {
    Complex temp;
    for (int i = 0; i < Vector::N; i++)  {
        initial(temp);
        v->set_vec(temp, i);
    }
}

void init_n(){
    std::cout << "Enter the number of elements in vectors:";
    std::cin >> Vector::N;
}

int main() {
    int cou = 2;
    auto num = new Complex[cou];
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
            init_n();
            Vector vect(Vector::N);
            init_v(&vect);
            Vector vect2(Vector::N);
            init_v(&vect2);
            std::cout << vect+vect2;
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