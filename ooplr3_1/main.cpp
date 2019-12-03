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
    friend std::ostream& operator << (std::ostream & out, const Complex& a);
    Complex operator + (const Complex& a);
    Complex operator - (const Complex& a);
    Complex operator * (const Complex& a);
    Complex operator / (const Complex& a);
    ~Complex() = default;
};

std::ostream& operator << (std::ostream & out, const Complex& a){
    if (a.img == 0)
        out << a.val << "\n";
    if (a.img < 0)
        out << a.val << a.img << "i" << "\n";
    else
        out << a.val << "+" << a.img << "i" << "\n";
    //out << a.val << "+" << a.img << "i";
    return out;
}

Complex Complex::operator+(const Complex &a) {
    Complex temp(val+a.val, img+a.img);
    return temp;
}

Complex Complex::operator-(const Complex &a) {
    Complex temp(val-a.val, img-a.img);
    return temp;
}

Complex Complex::operator*(const Complex &a) {
    Complex temp((val*a.val-img*a.img), (val*a.img+img*a.val));
    return temp;
}

Complex Complex::operator/(const Complex &a) {
    Complex temp((val*a.val+img*a.img)/(a.val*a.val+a.img*a.img), (img*a.val-val*a.img)/(a.val*a.val+a.img*a.img));
    return temp;
}

void init(Complex *num, int N){
    int val, img;
    for (int i = 0; i < N-1; i++){
        std::cout << "Enter the valid part of " << i+1 << " number:";
        std::cin >> val;
        num[i].set_val(val);
        std::cout << "Enter the imaginary part of " << i+1 << " number:";
        std::cin >> img;
        num[i].set_img(img);
    }
}

void numb_f_vec(int &N){
    std::cout << "Enter the number of numbers in vectors:";
    std::cin >> N;
}

int main() {
    int N = 3;
    auto *num = new Complex[N];
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
            init(num, N);
            std::cout << num[0]+num[1];
        }; break;
        case 2: {
            init(num, N);
            std::cout << num[0]-num[1];
        }; break;
        case 3: {
            init(num, N);
            std::cout << num[0]*num[1];
        }; break;
        case 4: {
            init(num, N);
            std::cout << num[0]/num[1];
        }; break;
        case 5: {

        }; break;
        case 6: {

        }; break;
        case 7: {

        }; break;
        case 8: {

        }; break;
        case 9: {

        }; break;
        default:
            break;
    }
    return 0;
}