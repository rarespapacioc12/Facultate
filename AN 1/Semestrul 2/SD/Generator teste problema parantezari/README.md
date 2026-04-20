## Explicatii cod
---
### Idee:
Pentru parantezarile gresite, pur si simplu concatenez paranteze random si le inchid cu lungime egala de paranteze random (randomizarea pe un interval asa mare imi spune ca sansele sa fac o parantezare corecta sunt aproape 0). In acest fel, am garantia ca pic si eventualele teste cu counter la paranteze diferite. De asemenea, mai pun o paranteza deschisa la final ca sa ma asigur ca pica orice test.

```C++
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
```

Pentru parantezarile corecte, ma folosesc de o stiva pentru a sti ca inchid corect (in special cand am si rotunde si patrate) si aplic concatenari de parantezari corecte, care raman corecte.

```C++
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
```

Folosindu-ma in continuare de randomizare, la fiecare linie din test generez o parantezare corecta sau gresita. 

Pentru fiecare test, verific constrangerile de dimensiune ca sa intre totusi in timp si daca totul e ok scriu testul.

Pentru a evita munca inutila, aceasta metoda bazata pe biblioteca random ofera rezultate satisfacatoare de teste.