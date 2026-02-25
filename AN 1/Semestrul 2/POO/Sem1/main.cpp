#include <iostream>
#include <vector>
#include <string>

class Student{
private:
    std::string nume;
    std::string prenume;
    int grupa;
    int nr_matricol;
    int nr_restante;
    std::vector<int> note;

public:
    Student() = default;
    Student(const std::string& nume, const std::string& prenume, const int grupa, const int nr_matricol, const int nr_restante, const std::vector<int>& note){
        this->nume = nume;
        this->prenume = prenume;
        this->grupa = grupa;
        this->nr_matricol = nr_matricol;
        this->nr_restante = nr_restante;
        this->note = note;
    }

    void afisare(){
        std::cout << "Nume complet: " + nume + " " + prenume + "\n";
        std::cout << "Grupa: " + std::to_string(grupa) + "\n";
        std::cout << "Nr. matricol: " + std::to_string(nr_matricol) + "\n";
        std::cout << "Nr. restante: " + std::to_string(nr_restante) + "\n";
        std::cout << "Note: ";
        for (const auto& nota : note)
            std::cout << nota << " ";
        std::cout << "\n";
    }

    double media(){
        double m = 0;
        for(const int& x : this->note){
            m += x;
        }
        return m / (int)this->note.size();
    }

    void calculeaza_restante(){
        int nr = 0;
        for(const int& x : this->note){
            nr += (x < 5);
        }
        this->nr_restante = nr;
        std::cout << "Studentul " + this->nume + " " + this->prenume + " are " + 
        std::to_string(this->nr_restante) + " restante.\n";
    }
};

int main(){
    Student s1("Popescu", "Ion", 152, 111, 0, {10, 9, 4});
    s1.afisare();
    std::cout << s1.media() << '\n';
    s1.calculeaza_restante();
}