#include "InstitutiePublica.hpp"
#include <iostream>

void InstitutiePublica::printInfo(std::ostream& os) const{
    std::cout << "Nume: " << nume << '\n';
    std::cout << "Buget: " << buget << '\n'; 
    std::cout << "Numar ngajati: " << numarAngajati << '\n'; 
    std::cout << "Numar sefi: " << numarSefi << '\n'; 
    std::cout << "Locatie: " << locatie << '\n';  
}

std::ostream &operator<<(std::ostream& os, const InstitutiePublica &obj){
    obj.printInfo(os);
    return os;  
}