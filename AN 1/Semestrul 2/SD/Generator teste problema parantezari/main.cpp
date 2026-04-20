#include <iostream>
#include <fstream>
#include <stack>
#include <random>
#include <string>

// Restrictii pentru generare
const int MAX_LINE_LENGTH = 2.5e4;
const int MAX_TEST_LENGTH = 5e5;
const int SEQUENCE_LENGTH = 1e3;
const int LINES_PER_TEST = 20;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> good(0, 1);
std::uniform_int_distribution<> length(1, SEQUENCE_LENGTH);

int generate_bad(int number, int test_number, int& test_total_length){
    std::ofstream fout;
    fout.open("input" + std::to_string(test_number) + ".in", std::fstream::app);
    int remaining_length = MAX_LINE_LENGTH - 1;
    int counter = 0;
    int total_written = 0;
    while(remaining_length > 0){
        int curr_len;
        do{
            curr_len = length(gen);
        }while(curr_len > remaining_length);
        if(counter & 1){
            for(int i = 0; i < curr_len; ++i){
                int type;
                if(test_number < 5){
                    type = 0;
                }
                else{
                    type = good(gen);
                }
                if(type == 0){
                    fout << ')';
                }
                else{
                    fout << ']';
                }
                total_written++;
            }
        }
        else{
            for(int i = 0; i < curr_len; ++i){
                int type;
                if(test_number < 5){
                    type = 0;
                }
                else{
                    type = good(gen);
                }
                if(type == 0){
                    fout << '(';
                }
                else{
                    fout << '[';
                }
                total_written++;
            }
        }
        ++counter;
        remaining_length -= curr_len;
    }
    int type;
    if(test_number < 5){
        type = 0;
    }
    else{
        type = good(gen);
    }
    if(type == 0){
        fout << '(';
    }
    else{
        fout << '[';
    }
    total_written++;
    if(number < LINES_PER_TEST){
        fout << '\n';
        total_written++;
    }
    test_total_length += total_written;
    return total_written;
}

int generate_good(int number, int test_number, int& test_total_length){
    std::ofstream fout;
    fout.open("input" + std::to_string(test_number) + ".in", std::fstream::app);
    int remaining_length = MAX_LINE_LENGTH >> 1;
    int total_written = 0;
    while(remaining_length > 0){
        int curr_len;
        do{
            curr_len = length(gen);
        }while(curr_len > remaining_length);
        std::stack<char> S;
        for(int i = 0; i < curr_len; ++i){
            int type;
            if(test_number < 5){
                type = 0;
            }
            else{
                type = good(gen);
            }
            if(type == 0){
                fout << '(';
                S.push(')');
            }
            else{
                fout << '[';
                S.push(']');
            }
            total_written++;
        }
        for(; !S.empty(); S.pop()){
            fout << S.top();
            total_written++;
        }
        remaining_length -= curr_len;
    }
    if(number < LINES_PER_TEST){
        fout << '\n';
        total_written++;
    }
    test_total_length += total_written;
    return total_written;
}

int generate_line(int number, int test_number, int& test_total_length){
    int type = good(gen);
    if(type == 0){
        return generate_bad(number, test_number, test_total_length);
    }
    else{
        return generate_good(number, test_number, test_total_length);
    }
}

void generate_test(int test_number){
    std::ofstream clear_file("input" + std::to_string(test_number) + ".in", std::ios::trunc);
    clear_file.close();
    int total_length = 0;
    int num_lines = 0;
    for(int i = 1; i <= LINES_PER_TEST && total_length < MAX_TEST_LENGTH; ++i){
        generate_line(i, test_number, total_length);
        num_lines++;
    }
    
    std::ifstream fin("input" + std::to_string(test_number) + ".in");
    std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();
    
    std::ofstream fout("input" + std::to_string(test_number) + ".in", std::ios::trunc);
    fout << num_lines << '\n' << content;
    fout.close();
}

void generate_tests(){
    for(int i = 0; i < 20; ++i){
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
    while(fin >> s){
        fout << (solve(s) ? "True\n" : "False\n");
    }
}

void solve_tests(){
    for(int i = 0; i < 20; ++i){
        solve_test(i);
    }
}

int main(){
    generate_tests();
    //solve_tests();
}