#include <iostream>
#include <fstream>
#include <stack>
#include <random>
#include <string>
#include <stack>

// Lungimi alese academic, practic pot fi oricat dar dimensiunea fisierelor creste considerabil
const int LENGTH = 1e5;
const int SEQUENCE_LENGTH = 1e4;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> good(0, 1); // 0 -> parantezare gresita, 1 -> parantezare corecta
// De asemenea, 0 -> paranteza '(', 1 -> paranteza '['
std::uniform_int_distribution<> length(1, SEQUENCE_LENGTH);

void generate_bad(int number, int test_number){
    std::ofstream fout;
    fout.open("input" + std::to_string(test_number) + ".in", std::fstream::app);
    int remaining_length = LENGTH - 1; // ca sa testez ultimul check de stiva goala, ii mai pun o paranteza deschisa la final
    int counter = 0;
    while(remaining_length > 0){
        int curr_len;
        do{
            curr_len = length(gen);
        }while(curr_len > remaining_length);
        if(counter & 1){
            for(int i = 0; i < curr_len; ++i){
                int type = good(gen);
                if(type == 0){
                    fout << ')';
                }
                else{
                    fout << ']';
                }
            }
        }
        else{
            for(int i = 0; i < curr_len; ++i){
                int type = good(gen);
                if(type == 0){
                    fout << '(';
                }
                else{
                    fout << '[';
                }
            }
        }
        ++counter;
        remaining_length -= curr_len;
    }
    int type = good(gen);
    if(type == 0){
        fout << '(';
    }
    else{
        fout << '[';
    }
    if(number < 20){
        fout << '\n';
    }
}

void generate_good(int number, int test_number){
    std::ofstream fout;
    fout.open("input" + std::to_string(test_number) + ".in", std::fstream::app);
    int remaining_length = LENGTH >> 1; // deci merg pe principiul ca nr_paranteze_dechise = nr_paranteze_inchise
    while(remaining_length > 0){
        int curr_len;
        do{
            curr_len = length(gen);
        }while(curr_len > remaining_length);
        std::stack<char> S;
        for(int i = 0; i < curr_len; ++i){
            int type = good(gen);
            if(type == 0){
                fout << '(';
                S.push(')');
            }
            else{
                fout << '[';
                S.push(']');
            }
        }
        for(; !S.empty(); S.pop()){
            fout << S.top();
        }
        remaining_length -= curr_len;
    }
    if(number < 20)
        fout << '\n';
}

void generate_line(int number, int test_number){
    int type = good(gen);
    if(type == 0){
        generate_bad(number, test_number);
    }
    else{
        generate_good(number, test_number);
    }
}

void generate_test(int test_number){
    std::ofstream clear_file("input" + std::to_string(test_number) + ".in", std::ios::trunc);
    clear_file.close();
    for(int i = 1; i <= 20; ++i){
        generate_line(i, test_number);
    }
}

void generate_tests(){
    for(int i = 0; i < 30; ++i){
        generate_test(i);
    }
}

bool solve(std::string s){
    int n = s.length();
    std::stack<char> S;

    for(int i = 0; i < n; ++i){
        if(s[i] == '(' || s[i] == '['){
            S.push(s[i]);
        }
        else{
            if(s[i] == ')'){
                if(S.empty() || S.top() == '['){
                    return false;
                }
                else{
                    S.pop();
                }
            }
            else{
                if(S.empty() || S.top() == '('){
                    return false;
                }
                else{
                    S.pop();
                }
            }
        }
    }
    if(!S.empty()){
        return false;
    }
    return true;
}

void solve_test(int nr){
    std::ifstream fin("input" + std::to_string(nr) + ".in");
    std::ofstream fout("output" + std::to_string(nr) + ".out");
    std::string s;
    for(int i = 0; i < 20; ++i){
        fin >> s;
        fout << (solve(s) ? "True\n" : "False\n");
    }
}

void solve_tests(){
    for(int i = 0; i < 30; ++i){
        solve_test(i);
    }
}

int main(){
    generate_tests();
    solve_tests();
}