#include <iostream>
#include "InstitutiePublica.hpp"

int main(){
    InstitutiePublica *institutiePublica = new InstitutiePublica("test", 123, 67, -3, "uliu maniu");
    institutiePublica->printInfo(std::cout);
}