// #include <iostream>

// class FormaGeometrica{
// public:
//     FormaGeometrica(){
//         std::cout << "Am creat o forma geometrica!\n";
//     }

//     virtual ~FormaGeometrica(){
//         std::cout << "Am distrus o forma geometrica\n";
//     }

//     virtual void printData(){
//         std::cout << "Aceasta este o forma geometrica!\n";
//     }
// };

// class Cerc : public FormaGeometrica{
// public:
//     Cerc(){
//         std::cout << "Am creat un cerc!\n";
//     }

//     ~Cerc(){
//         std::cout << "Am distrus un cerc!\n";
//     }

//     void printData(){
//         std::cout << "Acesta este un cerc!\n";
//     }
// };

// int main(){
//     // Destructor virtual
//     // FormaGeometrica* cerc = new Cerc();
//     // cerc->printData();
//     // delete cerc;

//     // Constructor virtual - clone()
//     Cerc* cerc = new Cerc();
//     cerc->printData();
//     FormaGeometrica* formaGeometrica = cerc;
//     formaGeometrica->printData();
// }

// #include <iostream>
// #include <memory>

// class DummyClass{
//     int n;

// public:
//     DummyClass(int n) : n(n){
//         std::cout << "[CONSTRUCTOR] - n: " << n << '\n';
//     }

//     ~DummyClass(){
//         std::cout << "[DESTRUCTOR] - n: " << n << '\n';
//     }
// };

// int main(){
//     // std::unique_ptr<DummyClass> ptr = std::make_unique<DummyClass>(3);
//     // std::cout << "BEFORE\n";
//     // {
//     //     std::unique_ptr<DummyClass> ptr1 = ptr;
//     //     {

//     //     }
//     // }

//     std::shared_ptr<DummyClass> ptr = std::make_shared<DummyClass>(3);
//     std::cout << "[CNT]: " << ptr.use_count() << '\n';
//     std::cout << "BEFORE\n";
//     {
//         std::shared_ptr<DummyClass> ptr1 = ptr;
//         std::cout << "[CNT]: " << ptr.use_count() << '\n';
//         std::cout << "BEFORE2\n";
//         {
//             std::shared_ptr<DummyClass> ptr2 = ptr1;
//             std::cout << "[CNT]: " << ptr.use_count() << '\n';
//         }
//         std::cout << "AFTER2\n";
//         std::cout << "[CNT]: " << ptr.use_count() << '\n';
//     }
//     std::cout << "AFTER\n";
//     std::cout << "[CNT]: " << ptr.use_count() << '\n';
// }

// #include <iostream>

// class DummyClass{
//     static int id;
//     int i;

// public:
//     DummyClass(int i, int n){
//         this->i = i;
//         id = n;
//     }

//     ~DummyClass() = default;

//     void printInfo() {
//         std::cout << "ID[" << i << "] = " << id << '\n';
//     }

//     static void sprintInfo() {
//         std::cout << "ID = " << id << '\n';
//     }
// };

// int DummyClass::id = 0;

// int main(){
//     DummyClass dummyObj1(1, 5);
//     dummyObj1.printInfo();

//     DummyClass dummyObj2(2, 10);
//     dummyObj2.printInfo();
//     dummyObj1.printInfo();

//     dummyObj2.sprintInfo();
//     DummyClass::sprintInfo();
// }

#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>

class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Aceasta este o exceptie custom!\n";
    }
};

class MyCustomException : public std::exception {
    std::string message;

public:
    MyCustomException(const std::string& message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


class Impartire {
    int a, b;

public:
    Impartire(int a, int b) : a(a), b(b) {
        if(b == 0){
            // throw std::invalid_argument("Impartirea la zero este ilegala!\n");
            // throw MyException();
            throw MyCustomException("Exceptia mea custom!\n");
        }
    }

    int rezultat(){
        return a / b;
    }
};

int main(){
    try{
        Impartire impartire(1, 0);
        std::cout << impartire.rezultat();
    } catch(std::invalid_argument& e){
        std::cout << e.what() << '\n';
    } catch(MyException& e){
        std::cout << e.what() << '\n';
    } catch(...){
        std::cout << "Another exception\n";
    }

    try{
        try{
            int a = 3;
            throw a;
        } catch(int a) {
            std::cout << a << '\n';
            throw 'c';
        }
    } catch(char c){
        std::cout << c << '\n';
    }
}