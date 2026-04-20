#pragma once

#include <string>

class InstitutiePublica{
protected:
    std::string nume;
    double buget;
    int numarAngajati;
    int numarSefi;
    std::string locatie;
public:
    InstitutiePublica() = default;
    InstitutiePublica(const std::string& nume, double buget, int numarAngajati, int numarSefi, const std::string& locatie) :
    nume(nume),
    buget(buget),
    numarAngajati(numarAngajati),
    numarSefi(numarSefi),
    locatie(locatie) {}

    void printInfo(std::ostream& os) const;
};