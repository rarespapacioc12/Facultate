// #include <iostream>

// struct FructStruct {
//     std::string nume;
//     double gramaj;

//     FructStruct(const std::string& nume, double gramaj){
//         this->nume = nume;
//         this->gramaj = gramaj;
//     }

//     void printInfo(){
//         std::cout << this->nume << " " << this->gramaj << "\n";
//     }
// };

// int main(){
//     FructStruct fructStruct("mar", 105);

//     fructStruct.printInfo();
// }


#include <iostream>

union DummyUnion{
    int a; // 32 biti
    char c; // 8 biti
}; // 32 biti

struct DummyStruct{
    int a; // 32 biti
    char c; // 8 biti
}; // 40 biti

class FructClass {
private:
    std::string nume;
    double gramaj;

public:
    FructClass() {
        std::cout << "Constructor default.\n";
    };

    FructClass(const std::string& nume) {
        this->nume = nume;
        this->gramaj = 50;

        std::cout << "Constructor parametrizabil - 1.\n";
    }

    FructClass(const std::string& nume, double gramaj){
        this->nume = nume;
        this->gramaj = gramaj;

        std::cout << "Constructor parametrizabil - 2.\n";
    }

    FructClass(const FructClass& fruit){
        this->nume = fruit.nume;
        this->gramaj = fruit.gramaj;

        std::cout << "Constructor de copiere.\n";
    }

    FructClass& operator=(const FructClass& other){
        this->nume = other.nume;
        this->gramaj = other.gramaj;

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const FructClass& other){
        out << "Exista " << other.gramaj << " grame din fructul " << other.nume << '\n';
        return out;
    }

    void print_info(){
        std::cout << this->nume << " " << this->gramaj << "\n";
    }

    ~FructClass() {
        std::cout << "Fructul " << nume << " a fost mancat!\n";
    };
};

int main(){
    FructClass fructClass("mar", 105);
    FructClass fructClass1, fructClass2(fructClass);
    FructClass fructClass3;

    fructClass3 = fructClass;
    fructClass3.operator=(fructClass);

    std::cout << fructClass2 << fructClass3;
}