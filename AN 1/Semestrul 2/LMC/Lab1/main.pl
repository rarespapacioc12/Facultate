% Care din urm˘atoarele ¸siruri de caractere sunt constante ¸si care sunt
% variabile ˆın Prolog?
% • vINCENT - constanta
% • Footmassage - variabila
% • variable23 - constanta
% • Variable2000 - variabila
% • big_kahuna_burger - constanta
% • ’big kahuna burger’ - constanta
% • big kahuna burger - nici una, nici alta
% • ’Jules’ - constanta
% • _Jules - variabila
% • ’_Jules’ - constanta

% windy :- oslo.
% norway :- oslo.
% cold :- norway.
% winterIsComing :- windy, cold.
% oslo.

% father(peter,meg). -> se numeste FAPT
% father(peter,stewie).
% mother(lois,meg).
% mother(lois,stewie).
% griffin(peter).
% griffin(lois).
% griffin(X) :- father(Y,X), griffin(Y). -> se numeste REGULA

% operatorul :- modeleaza implicatia logica <-
% virgula modeleaza conjunctia ^
% disjunctia v este modelata astfel:
% p(X) :- a(X).
% p(X) :- b(X).
% p(X) :- c(X).
% este echivalent cu p(X) = a(X) v b(X) v c(X)

% culoare(albastru).
% culoare(verde).
% culoare(rosu).
% culoare(galben).

% vecin(X, Y) :-
%     culoare(X),
%     culoare(Y),
%     X \== Y.

% harta(RO, MD, UA, HU, SE, BU) :-
%     vecin(RO, MD),
%     vecin(RO, UA),
%     vecin(RO, HU),
%     vecin(RO, SE),
%     vecin(RO, BU),
%     vecin(MD, UA),
%     vecin(UA, HU),
%     vecin(HU, SE),
%     vecin(SE, BU).

% T = U reuseste daca exista o potrivire (termenii se unifica)
% T \= U reuseste daca nu exista o potrivire
% T == U reuseste daca termenii sunt identici
% T \== U reuseste daca termenii nu sunt identici

% bigger(elephant, horse).
% bigger(horse, donkey).
% bigger(donkey, dog).
% bigger(donkey, monkey).

% is_bigger(X, Y) :-
%     bigger(X, Y).
% is_bigger(X, Y) :-
%     bigger(X, Z),
%     is_bigger(Z, Y).

% animal(dog).
% animal(elephant).
% animal(sheep).

% married(peter, lucy).
% married(paul, mary).
% married(bob, juliet).
% married(harry, geraldine).

% single(Person) :-
%     \+ married(Person, _),
%     \+ married(_, Person).

/*
Exercitiul 1
1. f, loves(john, mary), Mary, _c1, 'Hello'
Atomi: f, 'Hello'
2. a, A, Paul, 'Hello', a_123, _, _abc
Variabile: A, Paul, _, _abc
*/

% single(Person) 

% Exercitiul 2 + 3

female(mary).
female(sandra).
female(juliet).
female(lisa).
male(peter).
male(paul).
male(dony).
male(bob).
male(harry).
parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, dony).
parent(mary, sandra).

father_of(Father, Child) :-
    parent(Father, Child),
    male(Father).

mother_of(Mother, Child) :-
    parent(Mother, Child),
    female(Mother).

grandfather_of(Grandfather, Child) :-
    father_of(Grandfather, Parent),
    parent(Parent, Child).

grandmother_of(Grandmother, Child) :-
    mother_of(Grandmother, Parent),
    parent(Parent, Child).

sister_of(Sister, Person) :-
    female(Sister),
    parent(Parent, Sister),
    parent(Parent, Person).

brother_of(Brother, Person) :-
    male(Brother),
    parent(Parent, Brother),
    parent(Parent, Person).

aunt_of(Aunt, Person) :-
    female(Aunt),
    sister_of(Aunt, Parent),
    parent(Parent, Person).

uncle_of(Uncle, Person) :-
    male(Uncle),
    brother_of(Uncle, Parent),
    parent(Parent, Person).

ancestor_of(X, Y) :-
    parent(X, Y).

ancestor_of(X, Y) :-
    parent(X, Z),
    ancestor_of(Z, Y).

not_parent(X, Y) :-
    male(X),
    male(Y),
    X \== Y,
    \+ parent(X, Y).

not_parent(X, Y) :-
    female(X),
    male(Y),
    \+ parent(X, Y).

not_parent(X, Y) :-
    male(X),
    female(Y),
    \+ parent(X, Y).

not_parent(X, Y) :-
    female(X),
    female(Y),
    X \== Y,
    \+ parent(X, Y).