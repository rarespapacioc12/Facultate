// #include <iostream>

// class Baza{
// public:
//     void f() { std::cout << "f din baza\n"; }
// };

// class Derivata : public Baza{
// public:
//     void f() { std::cout << "f din derivata\n"; }
//     void g() { std::cout << "g din derivata\n"; }
// };

// int main(){
//     Baza ob1;
//     ob1.f();
//     // (static_cast<Derivata>(ob1)).g(); -> nu merge
//     Baza* ob2 = new Baza();
//     //ob2->g(); // nu merge
//     ((Derivata*)(ob2))->g();
//     (static_cast<Derivata*>(ob2))->g();
//     Derivata* ob3 = new Derivata();
//     if(static_cast<Derivata*>(ob3) == 0) {
//         std::cout << "nu merge conversia\n";
//     }
// }

// #include <iostream>
// #include <typeinfo>
// #include <vector>

// class Baza{
// public:
//     virtual void f(){}
// };

// class Derivata : public Baza {

// };

// class Derivata1 : public Derivata {};
// class Derivata2 : public Derivata {};

// int main(){
//     // Baza* p = new Derivata;

//     // if(typeid(*p) == typeid(Baza)){
//     //     std::cout << "baza\n";
//     // }
//     // else{
//     //     std::cout << "derivata\n";
//     // }

//     // if(dynamic_cast<Derivata*>(p)){
//     //     std::cout << "derivata\n";
//     // }
//     // else{
//     //     std::cout << "altceva\n";
//     // }

//     std::vector<Baza*> v;
//     v.push_back(new Derivata());
//     v.push_back(new Derivata1());
//     v.push_back(new Derivata2());

//     int nr1 = 0;
//     for(auto& x : v){
//         if(typeid(*x) == typeid(Derivata)){
//             ++nr1;
//         }
//     }

//     std::cout << nr1 << '\n'; // 1 - tipul de date si atat

//     int nr2 = 0;
//     for(auto& x : v){
//         if(dynamic_cast<Derivata*>(x)){
//             ++nr2;
//         }
//     }

//     std::cout << nr2 << '\n'; // 3 - tipul de date + derivate
// }