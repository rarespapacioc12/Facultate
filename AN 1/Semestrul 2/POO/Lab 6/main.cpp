#include <iostream>
#include <vector>

/*
InstitutiePublica {nume, buget, numarAngajati, numarSefi, locatie }
- ANAF { numarPersoaneJuridice, areBirocratie }
- Primarie { numePrimar, numarViceprimari }
- SRI { numarTelefoaneAscultate }
*/

class InstitutiePublica{
protected:
    std::string nume;
    double buget;
    int numarAngajati;
    int numarSefi;
    std::string locatie;
public:
    InstitutiePublica(const std::string& nume, double buget, int numarAngajati, int numarSefi, const std::string& locatie) :
    nume(nume),
    buget(buget),
    numarAngajati(numarAngajati),
    numarSefi(numarSefi),
    locatie(locatie) {}

    friend std::ostream &operator<<(std::ostream& os, const InstitutiePublica &obj){
        obj.printInfo(os);
        return os;  
    }

    virtual void printInfo(std::ostream& os) const{
        std::cout << "Nume: " << nume << '\n';
        std::cout << "Buget: " << buget << '\n'; 
        std::cout << "Numar ngajati: " << numarAngajati << '\n'; 
        std::cout << "Numar sefi: " << numarSefi << '\n'; 
        std::cout << "Locatie: " << locatie << '\n';  
    }

    virtual void f() = 0;
};

class ANAF : public InstitutiePublica{
private:
    int numarPersoaneJuridice;
    int areBirocratie;
public:
    ANAF(const std::string& nume, double buget, int numarAngajati, int numarSefi, const std::string& locatie, int numarPersoaneJuridice, int areBirocratie) :
    InstitutiePublica(nume, buget, numarAngajati, numarSefi, locatie),
    numarPersoaneJuridice(numarPersoaneJuridice),
    areBirocratie(areBirocratie) {}

    void printInfo(std::ostream& os) const override{ // override imi da debug daca fac typos
        InstitutiePublica::printInfo(os); 
        std::cout << "Numar persoane juridice: " << numarPersoaneJuridice << '\n';
        std::cout << "Are birocratie: " << areBirocratie << '\n';
    }

    void f() override{
        std::cout << "Scriu functia virtuala pura\n";
    }
};

class Primarie : public InstitutiePublica{
private:
    std::string numePrimar;
    int numarViceprimari;
public:
    Primarie(const std::string& nume, double buget, int numarAngajati, int numarSefi, const std::string& locatie, const std::string& numePrimar, int numarViceprimari) :
    InstitutiePublica(nume, buget, numarAngajati, numarSefi, locatie),
    numePrimar(numePrimar),
    numarViceprimari(numarViceprimari) {}

    void printInfo(std::ostream& os) const override{ // override imi da debug daca fac typos
        InstitutiePublica::printInfo(os); 
        std::cout << "Nume primar: " << numePrimar << '\n';
        std::cout << "Numar viceprimari: " << numarViceprimari << '\n';
    }
};

class SRI : public InstitutiePublica{
private:
    int numarTelefoaneAscultate;
public:
    SRI(const std::string& nume, double buget, int numarAngajati, int numarSefi, const std::string& locatie, int numarTelefoaneAscultate) :
    InstitutiePublica(nume, buget, numarAngajati, numarSefi, locatie),
    numarTelefoaneAscultate(numarTelefoaneAscultate) {}

    void printInfo(std::ostream& os) const override{ // override imi da debug daca fac typos
        InstitutiePublica::printInfo(os); 
        std::cout << "Numar telefoane ascultate: " << numarTelefoaneAscultate << '\n';
    }
};

int main(){
    std::vector<InstitutiePublica*> institutiiPublice;
    // institutiiPublice.push_back(new InstitutiePublica("test", 123, 67, 23, "uliu maniu"));
    institutiiPublice.push_back(new ANAF("anal", 69, 67, 12, "magheru", -1, 7));

    for(auto& institutie : institutiiPublice){
        std::cout << *institutie;
        std::cout << "----------------------------------\n";
    }
}