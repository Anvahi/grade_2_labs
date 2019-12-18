#include <iostream>
#include <string>

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

    void set_val(double a) {
        val = a;
    }

    void set_img(double b) {
        img = b;
    }

    double get_val() {
        return val;
    }

    double get_img() {
        return img;
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
    return *this;
}

class Vector {
private:
    Complex *vec;
public:
    static int N;
    Vector() {
        this->vec = new Complex[N];
    }

    void set_vec(Complex t, int i){
        this->vec[i] = t;
    }

    void abs(Complex &mod){
        Complex sum;
        for (int i = 0; i < Vector::N; i++){
            sum = this->vec[i]*this->vec[i];
        }
        std::cout << "Vector module is sqrt(" << sum << ")\n";
    }

    friend std::istream &operator>>(std::istream &in, Vector &A);

    friend std::ostream &operator<<(std::ostream &out, const Vector &A);

    Vector operator+(const Vector &A);

    Vector operator-(const Vector &A);

    Vector operator*(double a);

    Vector operator*(const Vector &A);

    ~Vector() = default;
};

std::istream &operator>>(std::istream &in, Vector &A) {
    int val, img;
    for (int i = 0; i < Vector::N; i++){
        std::cout << "Enter the real part of the number:";
        in >> val;
        A.vec[i].set_val(val);
        std::cout << "Enter the imaginary part of the number:";
        in >> img;
        A.vec[i].set_img(img);
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Vector &A) {
    for (int i = 0; i < Vector::N; i++) {
        out << A.vec[i];
    }
    return out;
}

Vector Vector::operator+(const Vector &A) {
    auto temp = new Vector();
    for (int i = 0; i < Vector::N; i++){
        temp->vec[i] = A.vec[i]+this->vec[i];
    }
    return *temp;
}

Vector Vector::operator-(const Vector &A) {
    auto temp = new Vector();
    for (int i = 0; i < Vector::N; i++){
        temp->vec[i] = this->vec[i]-A.vec[i];
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

int init_n(){
    int n;
    std::cout << "Enter the number of elements in vectors:";
    std::cin >> n;
    while (n < 2){
        std::cout << "Please, try again!";
        std::cin >> n;
    }
    return n;
}

int Vector::N = init_n();

Vector Vector::operator*(double a) {
    for (int i = 0; i < Vector::N; i++) {
        this->vec[i].set_val(vec[i].get_val()*a);
        this->vec[i].set_img(vec[i].get_img()*a);
    }
    return Vector();
}

Vector Vector::operator*(const Vector &A) {
    for (int i = 0; i < Vector::N; i++){
        this->vec[i] = this->vec[i]*A.vec[i];
    }
    return Vector();
}

int main() {
    while (true) {
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
                auto vect = new Vector();
                std::cin >> *vect;
                auto vect2 = new Vector();
                std::cin >> *vect2;
                std::cout << vect->operator+(*vect2);
            };
                break;
            case 6: {
                auto vect = new Vector();
                std::cin >> *vect;
                auto vect2 = new Vector();
                std::cin >> *vect2;
                std::cout << vect->operator-(*vect2);
            };
                break;
            case 7: {
                auto vect = new Vector();
                std::cin >> *vect;
                std::cout << "Enter the number for mult:";
                double k;
                std::cin >> k;
                std::cout << vect->operator*(k);
            };
                break;
            case 8: {
                auto vect = new Vector();
                std::cin >> *vect;
                auto vect2 = new Vector();
                std::cin >> *vect2;
                std::cout << vect->operator*(*vect2);
            };
                break;
            case 9: {
                auto vect = new Vector();
                std::cin >> *vect;
            };
                break;
            default:
                break;
        }
        delete[] num;
        std::string again;
        std::cout << "Do you want to continue?(yes/no)\n";
        std::cin >> again;
        while (again != "yes" && again != "no"){
            std::cout << "Please, try again!\n";
            std::cin >> again;
        }
        if (again == "yes")
            continue;
        else if (again == "no")
            break;
    }
    return 0;
}