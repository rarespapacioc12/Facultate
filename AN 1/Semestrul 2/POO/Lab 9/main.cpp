#include <iostream>
#include <string>
#include <vector>
#include <memory>

class ApplicationException : public std::exception {
private:
    std::string message;
public:
    ApplicationException(std::string m) : message(m) {}
    const char* what() const throw() {
        return message.c_str();
    }
};

class SuficienteJucarii : public ApplicationException {
public:
    SuficienteJucarii() : ApplicationException("Un copil nu poate avea mai multe jucarii decat fapte bune!\n") {}
};

class Jucarie {
protected:
    std::string denumire;
    int dimensiune;
    std::string tip;
public:
    Jucarie() = default;
    Jucarie(const std::string& denumire, int dimensiune, const std::string& tip) :
    denumire(denumire), dimensiune(dimensiune), tip(tip) {}

    Jucarie() {
        std::cin >> denumire >> dimensiune >> tip;
    }

    friend std::ostream& operator<<(std::ostream& os, const Jucarie& jucarie) {
        std::cout << jucarie.denumire << '\n';
        std::cout << jucarie.dimensiune << '\n';
        std::cout << jucarie.tip << '\n';
    }

    virtual ~Jucarie() = default;
};

class JucarieClasica : public Jucarie {
private:
    std::string material;
    std::string culoare;
public:
    JucarieClasica() = default;
    JucarieClasica(const std::string& denumire, int dimensiune,
    const std::string& tip, const std::string& material,
    const std::string& culoare) :
    Jucarie(denumire, dimensiune, tip),
    material(material), culoare(culoare) {}
};

class JucarieEducativa : virtual public Jucarie {
private:
    std::string abilitate_dezvoltata;
public:
    JucarieEducativa() = default;
    JucarieEducativa(const std::string& denumire, int dimensiune,
    const std::string& tip, const std::string& abilitate_dezolvtata) :
    Jucarie(denumire, dimensiune, tip), abilitate_dezvoltata(abilitate_dezolvtata) {}
};

class JucarieElectronica : virtual public Jucarie {
private:
    int baterii;
public:
    JucarieElectronica() = default;
    JucarieElectronica(const std::string& denumire, int dimensiune,
    const std::string& tip, int baterii) :
    Jucarie(denumire, dimensiune, tip),
    baterii(baterii) {}
};

class JucarieModerna : public JucarieEducativa, public JucarieElectronica {
private:
    std::string brand;
    std::string model;
public:
    JucarieModerna(const std::string& denumire, int dimensiune,
    const std::string& tip, const std::string& brand, const std::string& model) :
    JucarieElectronica(denumire, dimensiune, tip, 1),
    brand(brand),
    model(model) {}
};

class Copil {
protected:
    int id;
    static int id_gen;
    std::string nume;
    std::string prenume;
    std::string adresa;
    int varsta;
    int fapte_bune;
    std::vector<std::shared_ptr<Jucarie>> jucarii;
public:
    Copil(const std::string& nume, const std::string& prenume,
    const std::string& adresa, int varsta, int fapte_bune,
    const std::vector<std::shared_ptr<Jucarie>>& jucarii) :
    id(++id_gen), nume(nume), prenume(prenume),
    adresa(adresa), varsta(varsta), fapte_bune(fapte_bune),
    jucarii(jucarii) {}

    Copil(){
        std::cin >> nume >> prenume >> adresa >> varsta >> fapte_bune;
    }

    void citeste_jucarie(){
        if(jucarii.size() + 1 <= fapte_bune){
            std::shared_ptr<Jucarie> j = nullptr;
            std::cout << "Ce tip de jucarie va primi copilul? (c/d/e/n)\n";
            char c;
            std::cin >> c;

            switch(c) {
                case 'c':
                    j = std::make_shared<JucarieClasica>();
                    break;
                case 'd':
                    j = std::make_shared<JucarieEducativa>();
                    break;
                case 'e':
                    j = std::make_shared<JucarieElectronica>();
                    break;
                case 'm':
                    j = std::make_shared<JucarieModerna>();
                    break;
                default:
                    throw new ApplicationException("Tip invalid de jucarie!\n");
            }
        }
        else{
            throw new SuficienteJucarii();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Copil& copil) {
        os << copil.nume << '\n';
        os << copil.prenume << '\n';
        os << copil.adresa << '\n';
        os << copil.varsta << '\n';
        os << copil.fapte_bune << '\n';
    }
};

class CopilCuminte : public Copil {
private:
    int nr_dulciuri;
public:
    CopilCuminte(const std::string& nume, const std::string& prenume,
    const std::string& adresa, int varsta, int fapte_bune,
    const std::vector<std::shared_ptr<Jucarie>>& jucarii, int nr_dulciuri) :
    Copil(nume, prenume, adresa, varsta, fapte_bune, jucarii), nr_dulciuri(nr_dulciuri) {}
};

class CopilNeastamparat : public Copil {
private:
    int nr_carbuni;
public:
    CopilNeastamparat(const std::string& nume, const std::string& prenume,
    const std::string& adresa, int varsta, int fapte_bune,
    const std::vector<std::shared_ptr<Jucarie>>& jucarii, int nr_carbuni) :
    Copil(nume, prenume, adresa, varsta, fapte_bune, jucarii), nr_carbuni(nr_carbuni) {}
};