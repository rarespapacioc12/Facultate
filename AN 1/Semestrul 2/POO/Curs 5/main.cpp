// #include <iostream>

// class Baza{
// protected: // Devine public pentru clasele derivate
//     int x;
// public:
//     Baza() {
//         x = 5;
//         std::cout << "b\n";
//     }
//     Baza(int x) : x(x) {
//         std::cout << "Param b\n";
//     }
// };

// class Derivata : public Baza{
// private:
//     int y;
// public:    
//     Derivata(){
//         y = 6;
//         std::cout << "d\n";
//     }
//     // Derivata(int y) : y(y){
//     //     std::cout << "Param d\n";
//     // }
//     Derivata(int x, int y) : Baza(x), y(y){
//         std::cout << "param d\n";
//     }
//     void afis(){
//         std::cout << x << " " << y << '\n';
//     }
// };

// int main(){
//     Derivata ob;
//     ob.afis();
//     Baza ob2;
//     //Derivata ob3(10);
//     Derivata ob4(67, 89);
// }

// Diferenta dintre () si {}

// #include <iostream>
// #include <vector>

// class Test{
// private:
//     int x;
// public:
//     Test(int x) : x(x){
//         std::cout << "int\n";
//     }
//     Test(std::initializer_list<int> lista){
//         std::cout << "initializer_list\n";
//     }
// };

// void f(std::initializer_list<int> lista){
//     for(auto& x : lista){
//         std::cout << x << ' ';
//     }
// }

// int main(){
//     // int a1(10);
//     // int a2 = 20;
//     // int a3{30};
//     // std::cout << a1 << ' ' << a2 << ' ' << a3 << '\n';
//     // int a11(10.5);
//     // int a21 = 20.6;
//     // int a31{30.7}; // nu face trunchere
//     // std::cout << a11 << ' ' << a21 << ' ' << a31 << '\n';
//     std::vector<int> v = {1, 2, 3};
//     std::vector<int> v1(6, 8);
//     std::cout << v1.size() << '\n';
//     std::vector<int> v2{6, 8};
//     std::cout << v2.size() << '\n';
//     std::vector<int> v3;
//     std::vector<int> v4(); // apel de functie care imi intoarce un obiect
//     f({5, 78, 90});
//     Test A(34);
//     Test B{78};
// }


// #include <iostream>

// // constr param si de copiere din derivata trebuisa sa faca trimitere catre param si copiere din baza
// // si asta se face prin lista de constructori
// class Baza{
// protected: // Devine public pentru clasele derivate
//     int x;
// public:
//     Baza() {
//         x = 5;
//         std::cout << "b\n";
//     }
//     Baza(int x) : x(x) {
//         std::cout << "Param b\n";
//     }
//     Baza(Baza& ob){
//         x = ob.x;
//         std::cout << "cc din b\n";
//     }
// };

// class Derivata : public Baza{
// private:
//     int y;
// public:    
//     Derivata(){
//         y = 6;
//         std::cout << "d\n";
//     }
//     // Derivata(int y) : y(y){
//     //     std::cout << "Param d\n";
//     // }
//     Derivata(int x, int y) : Baza(x), y(y){
//         std::cout << "param d\n";
//     }
//     // Derivata(Derivata& ob){
//     //     y = ob.y;
//     //     std::cout << "cc din d\n";
//     // }
//     Derivata(Derivata& ob) : Baza(ob){
//         y = ob.y;
//         std::cout << "cc din d\n";
//     }
//     void afis(){
//         std::cout << x << " " << y << '\n';
//     }
// };

// int main(){
//     Derivata ob;
//     ob.afis();
//     Baza ob2;
//     //Derivata ob3(10);
//     Derivata ob4(67, 89);
//     Derivata ob5(ob4);
//     ob5.afis();
// }

// #include <iostream>
// #include <vector>

// class Baza{
// protected:
//     int x;
// public:
//     friend std::istream& operator>>(std::istream& in, Baza& ob){
//         return in >> ob.x;
//     }
// };

// class Derivata : public Baza{
// private:
//     int y;
// public:
//     friend std::ostream& operator<<(std::ostream& out, Derivata& ob){
//         return out << ob.x << ' ' << ob.y << '\n';
//     }
// };

// int main(){
//     Derivata ob;
//     std::cin >> ob; // preluat din clasa parinte
//     std::cout << ob;

//     Baza ob1;
//     std::cin >> ob1;
//     std::cout << ob1; // nu exista decat in clasa copil
// }

// #include <iostream>
// #include <vector>

// class Baza{
//     int x;
// public:
//     void afis(){
//         std::cout << x;
//     }
// };

// struct Derivata : Baza{};
// class Derivata2 : Baza{};

// int main(){
//     Derivata ob;
//     Derivata2 ob2;
//     ob.afis(); // cu private Baza nu merge
//     ob2.afis(); // accesibil daca struct Derivata : Baza{} pt ca "default" pt structura e public
//     Baza ob1;
//     ob1.afis(); // merge
// }

#include <iostream>

class Baza{
protected:
    int x;
public:
    Baza() {
        x = 10;
    }

    Baza operator-(){
        x = -x;
        return *this;
    }
    
    Baza operator-(int y){
        x -= y;
        return *this;
    }
};

class Derivata : Baza{
public:
    Derivata() : Baza(){}
    using Baza::operator-;
    void afis(){
        std::cout << x << '\n';
    }
};

int main(){
    Derivata ob;
    ob.afis();
    -ob;
    ob.afis();
    ob-7;
    ob.afis();
}