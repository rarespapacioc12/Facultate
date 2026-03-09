% Se aplica formula
distance((X1, Y1), (X2, Y2), D) :-
    D is sqrt((X2 - X1)**2 + (Y2 - Y1) ** 2).


% Asa faci memoizare aparent
:- table fibo/2.

fibo(0, 1).
fibo(1, 1).

fibo(Y, X) :-
    Y > 1,
    P1 is Y - 1,
    P2 is Y - 2,
    fibo(P1, A),
    fibo(P2, B),
    X is A + B.

% Definesc linia vida ca adevar
line(0, Char).

% Scriu linia caracter cu caracter
line(X, Char) :-
    X > 0,
    X1 is X - 1,
    write(Char),
    line(X1, Char).

% Definesc dreptunghiul sub forma de linie ca adevar
rectangle(0, Y, Char). 

% Construiesc dreptunghiul linie cu linie
rectangle(X, Y, Char) :-
    X > 0,
    line(Y, Char),
    nl,
    X1 is X - 1,
    rectangle(X1, Y, Char).

square(X, Char) :- rectangle(X, X, Char).

% X e in lista daca e capul ei (primul el)
element_of(X, [X | _]).
% SAU X e in lista daca nu e capul ei, dar se afla in coada listei (restul elementelor, fara primul)
element_of(X, [_ | Tail]) :- element_of(X, Tail).

% Daca L1 = vid, atunci concatenarea lor e chiar L2
concat_lists([], List, List). % concateneaza L1 cu L2 in L3

% SAU L1 nu e vid, deci pun elementele din ele unul cate unul in L3 la inceput
concat_lists([Elem | List1], List2, [Elem | List3]) :-
    concat_lists(List1, List2, List3).

% Multimea vida respecta conditia
all_a([]).

% Verific daca Head e a si continui verificarea pentru restul listei.
% A se vedea ca daca Head e variabila, i se atribuie valoarea a pentru a rezolva ecuatia practic
all_a([Head | Tail]) :-
    Head = a,
    all_a(Tail).

% Analog all_a
all_b([]).

all_b([Head | Tail]) :-
    Head = b,
    all_b(Tail).

% Calculez L1 = length(X), L2 = length(Y), verific daca sunt egale si dupa verific daca X contine doar a si Y contine doar b
% De remarcat ca daca X sau Y sunt nule, modul in care sunt scrise all_a si all_b le face liste de lungimea potrivita de a, respectiv b
trans_a_b(X, Y) :-
    length(X, L1),
    length(Y, L2),
    L1 == L2,
    all_a(X),
    all_b(Y).

% Cand am ajuns la lista vida la parametrii 2 si 3, inseamna ca am terminat procesul
scalarMult(X, [], []).

% Consider L1 = lista initiala si L2 = lista finala
scalarMult(X, [Head | Tail], [NewHead | NewTail]) :-
    NewHead is X * Head, % practic fac L2[i] = L1[i] * X
    scalarMult(X, Tail, NewTail). % Continui asta pt pozitiile i + 1, ...

% Pentru lista vida, produsul scalar e 0
dot([], [], 0).

% Plec de la premiza ca lungimile celor 2 liste sunt egale
dot([H1 | T1], [H2 | T2], Result) :-
    dot(T1, T2, NewRes), % Calculez produsul scalar dintre Tail1 si Tail2
    Result is NewRes + H1 * H2. % Practic fac Result = produs_scalar(L1[i + 1:], L2[i + 1:]) + L1[i] * L2[i] (am folosit notatii python)

% Daca X > Y, maximul (stocat in VAL) este X.
maxim(X, Y, VAL) :-
    X > Y,
    VAL is X.

% Altfel, maximul e Y.
maxim(X, Y, VAL) :-
    Y >= X,
    VAL is Y.

% Maximul listei vide de nr naturale e 0
max([], 0).

max([Head | Tail], Result) :-
    max(Tail, NewRes), % NewRes = maximul pe sublista Tail = L[i + 1:]
    maxim(Head, NewRes, Result). % Result = max(Head, newRes)