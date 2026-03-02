/*#include <iostream>
#include <vector>

int main(){
    std::vector<int> v;
    v.push_back(123);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 1 1

    v.push_back(-123);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 2 2

    v.push_back(23);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 3 4

    v.push_back(3);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 4 4

    v.push_back(453);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 5 8

    v.push_back(99);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 6 8

    return 0;
}*/

/*#include <iostream>
#include <vector>

//Orice clasa are constructor de initializare
// class Test{
//     int *a;
//     public:
//     Test(int a = 15) {this->a = new int[14];}//: a(a) {} //constructor de initializare
//     Test(Test& ob){
//         a = new int[14];
//         for(int i = 0; i < 14; i++)
//             a[i] = ob.a[i];
//     }
//     Test(Test&& ob){
//         a = ob.a;
//         ob.a = NULL;
//     }
//     ~Test() { delete[] a; }
// };

class Test{
    int a;
    public:
    // Test(int a = 19)  { this->a = a;}
    Test(int a = 19) : a(a) {}
};

int main(){
    Test A(15);
    Test B(A);
    std::vector<Test> v;
    v.push_back(Test());
    std::cout << v.size() << " " << v.capacity() << '\n'; // 1 1

    v.push_back(Test(88));
    std::cout << v.size() << " " << v.capacity() << '\n'; // 2 2

    v.push_back(23);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 3 4

    v.push_back(3);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 4 4

    v.push_back(453);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 5 8

    v.push_back(99);
    std::cout << v.size() << " " << v.capacity() << '\n'; // 6 8

    return 0;
}*/

/*#include <iostream>
#include <vector>
#include <string>

struct masina{
    int an;
    std::string culoare;

    void afis(){
        std::cout << an << " " << culoare << '\n';
    }
};

int main(){
    masina A;
    A.an = 2025;
    A.culoare = "verde";
    A.afis();
}*/

/*#include <iostream>
#include <vector>
#include <string>

class masina{
private:
    int an;
    std::string culoare;

public:
    void afis(){
        std::cout << an << " " << culoare << '\n';
    }

    int get_an(){ return an; }
    std::string get_culoare(){ return culoare; }

    void set_an(int x){ an = x; }
    void set_culoare(std::string x){ culoare = x; }
};

int main(){
    masina A;
    // A.an = 2025; ---> eroare
    // A.culoare = "verde"; ---> eroare
    A.set_an(2025);
    A.set_culoare("verde");
    std::cout << A.get_an() << '\n';
    A.afis();
}*/

#include <iostream>
#include <vector>
#include <string>

class proprietar{
    std::string nume;
public:
    proprietar(std::string nume) : nume(nume){}
};

class masina{
protected:
    proprietar& P; // agregare/compunere
    int an;
    std::string culoare;

public:
    masina(proprietar& prop): P(prop){}

    void afis(){
        std::cout << an << " " << culoare << '\n';
    }

    int get_an(){ return an; }
    std::string get_culoare(){ return culoare; }

    void set_an(int x){ an = x; }
    void set_culoare(std::string x){ culoare = x; }
};

// mostenire/inheritance
class masina_sport : public masina { // private masina
private:
    proprietar* dummy_prop;
public:
    masina_sport(proprietar& prop) : masina(prop) { 
        an = 1999; 
        culoare = "gri"; 
    }
    void set_an(int x){
        // std::cout << "din derivata ";
        // an = x; SAU
        masina::set_an(x);
    }
    void afis(){
        std::cout << "afis din derivata " << an << '\n'; 
    }
};

int main(){
    proprietar prop("none");
    masina A(prop);
    A.set_an(2024);
    masina_sport B(prop);
    B.set_an(2000);
    B.masina::set_an(2010);
    B.set_culoare("rosie");
    B.afis();
}