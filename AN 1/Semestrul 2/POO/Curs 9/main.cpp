// #include <iostream>
// #include <string>
// #include <vector>

// // Varianta cu functii virtuale si atat

// class Jucarie{
// protected:
//     int an;
//     std::string tara;
// public:
//     virtual void citire(){
//         std::cout << "an ";
//         std::cin >> an;
//         std::cout << "\ntara ";
//         std::cin >> tara;
//     }

//     virtual void afis(){
//         std::cout << an << ' ' << tara << '\n';
//     }
// };

// class Masinuta : public Jucarie{
// private:
//     std::string culoare;
// public:
//     void citire(){
//         Jucarie::citire();
//         std::cout << "\nculoare ";
//         std::cin >> culoare;
//     }
// };

// class Round : public Jucarie{ // de exemplu pentru titirez
// private:
//     int viteza;
// public:
//     void citire(){
//         Jucarie::citire();
//         std::cout << "\nviteza ";
//         std::cin >> viteza;
//     }
// };

// class Plus : public Jucarie{ // jucarii de plus
// private:
//     bool baterie;
// public:
//     void citire(){
//         Jucarie::citire();
//         std::cout << "\nbaterie ";
//         std::cin >> baterie;
//     }
// };

// int main(){
//     Jucarie* v[10];
// }


// #include <iostream>
// #include <string>
// #include <vector>

// // Varianta cu functii prieten

// class Jucarie{
// protected:
//     int an;
//     std::string tara;
// public:
//     friend std::istream& operator>>(std::istream& in, Jucarie& ob){
//         std::cout << "an ";
//         in >> ob.an;
//         std::cout << "tara ";
//         in >> ob.tara;
//         return in;
//     }

//     virtual void afis(){
//         std::cout << an << ' ' << tara << '\n';
//     }
// };

// class Masinuta : public Jucarie{
// private:
//     std::string culoare;
// public:
//     friend std::istream& operator>>(std::istream& in, Masinuta& ob){
//         in >> static_cast<Jucarie&>(ob);
//         std::cout << "culoare ";
//         in >> ob.culoare;
//         return in;
//     }
// };

// class Round : public Jucarie{ // de exemplu pentru titirez
// private:
//     int viteza;
// public:
//     // void citire(){
//     //     Jucarie::citire();
//     //     std::cout << "\nviteza ";
//     //     std::cin >> viteza;
//     // }
// };

// class Plus : public Jucarie{ // jucarii de plus
// private:
//     bool baterie;
// public:
//     // void citire(){
//     //     Jucarie::citire();
//     //     std::cout << "\nbaterie ";
//     //     std::cin >> baterie;
//     // }
// };

// class Meniu{
//     // ce tine de singleton; constr, =, destr privati + data membra static* privata + fct publica static*
//     static Meniu* instance;
// public:
//     void rezolvare_punct_a();
//     static Meniu* get_instance(){
//         if(instance == nullptr) return new Meniu();
//     }
// };

// Meniu* Meniu::instance = nullptr;

// void Meniu::rezolvare_punct_a(){
//     // citire, stocare, afisare
// }

// int main(){
//     // Meniu m;
//     // m.rezolvare_punct_a();
//     Meniu* m = Meniu::get_instance();
//     m->rezolvare_punct_a();
//     Jucarie* v[10];
//     Jucarie* p = new Masinuta();
//     std::cin >> *dynamic_cast<Masinuta*>(p);
// }

// #include <iostream>
// #include <string>
// #include <vector>

// // Varianta cu functii prieten

// class Jucarie{
// protected:
//     int an;
//     std::string tara;
// public:
//     virtual void citire(){
//         std::cout << "an ";
//         std::cin >> an;
//         std::cout << "tara ";
//         std::cin >> tara;
//     }
//     virtual void afis() const{
//         std::cout << an << ' ' << tara << ' ';
//     }
//     friend std::istream& operator>>(std::istream& in, Jucarie& ob){
//         ob.citire();
//         return in;
//     }

//     friend std::ostream& operator<<(std::ostream& out, Jucarie& ob){
//         ob.afis();
//         return out;
//     }
// };

// class Masinuta : public Jucarie{
// private:
//     std::string culoare;
// public:
//     friend std::istream& operator>>(std::istream& in, Masinuta& ob){
//         in >> static_cast<Jucarie&>(ob);
//         std::cout << "culoare ";
//         in >> ob.culoare;
//         return in;
//     }
// };

// class Round : public Jucarie{ // de exemplu pentru titirez
// private:
//     int viteza;
// public:
//     // void citire(){
//     //     Jucarie::citire();
//     //     std::cout << "\nviteza ";
//     //     std::cin >> viteza;
//     // }
// };

// class Plus : public Jucarie{ // jucarii de plus
// private:
//     bool baterie;
// public:
//     // void citire(){
//     //     Jucarie::citire();
//     //     std::cout << "\nbaterie ";
//     //     std::cin >> baterie;
//     // }
// };

// int main(){
//     Jucarie* p = new Masinuta();
//     std::cin >> *p;
//     std::cout << *p;
// }

#include <iostream>
#include <string>
#include <vector>

// Varianta cu functii prieten

class Jucarie{
protected:
    int an;
    std::string tara;
public:
    virtual void citire(){
        std::cout << "an ";
        std::cin >> an;
        std::cout << "tara ";
        std::cin >> tara;
    }
    virtual void afis() const{
        std::cout << an << ' ' << tara << ' ';
    }
    friend std::istream& operator>>(std::istream& in, Jucarie& ob){
        ob.citire();
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, Jucarie& ob){
        ob.afis();
        return out;
    }
};

class Masinuta : public Jucarie{
private:
    std::string culoare;
public:
    friend std::istream& operator>>(std::istream& in, Masinuta& ob){
        in >> static_cast<Jucarie&>(ob);
        std::cout << "culoare ";
        in >> ob.culoare;
        return in;
    }
};

class Round : public Jucarie{ // de exemplu pentru titirez
private:
    int viteza;
public:
    void citire(){
        Jucarie::citire();
        std::cout << "\nviteza ";
        std::cin >> viteza;
    }
};

class Plus : public Jucarie{ // jucarii de plus
private:
    bool baterie;
public:
    void citire(){
        Jucarie::citire();
        std::cout << "\nbaterie ";
        std::cin >> baterie;
    }
};

template<class T>
void Gestiune(T v[10], int n){
    for(int i = 0; i < n; ++i){
        v[i].citire();
    }
}


int main(){
    
}