intoarce([], []).

intoarce([H1 | T1], L) :-
    intoarce(T1, NewL), % Intoarce restul listei
    append(NewL, [H1], L). % L = NewL + [H1]

palindrome([]).

% L e palindrom <=> L = reverse(L)
palindrome(L) :-
    intoarce(L, X),
    X == L.

contains([X | _], X). % X == Head deci X e in lista
contains([_ | Tail], X) :- % X nu e Head deci caut in restul listei
    contains(Tail, X).

remove_duplicates([], []). % Lista goala e lista initiala fara duplicate

remove_duplicates([H1 | T1], L) :-
    remove_duplicates(T1, L1), % L1 = T1 fara duplicate
    \+ contains(L1, H1), % Daca H1 nu e in L1
    L = [H1 | L1]. % Atunci L = [H1 | L1]

remove_duplicates([H1 | T1], L) :-
    remove_duplicates(T1, L1), % L1 = T1 fara duplicate
    contains(L1, H1), % Daca H1 e in L1
    L = L1. % Atunci L = L1

atimes(N, [], 0). % Orice numar apare de 0 ori in lista vida

atimes(N, [N | T], X) :-
    atimes(N, T, X1), % X1 = de cate ori apare N in T
    X is X1 + 1. % X = X + 1 ptc N apare ca Head

atimes(N, [H | T], X) :-
    N \== H, % N e diferit de Head
    atimes(N, T, X). % Deci X = nr de aparitii ale lui N in tail

insert(H, [], [H]). % Daca am un singur element pozitia lui e singurul element din lista

insert(H, [H1 | T1], L) :-
    H > H1, % Daca el curent > H1
    insert(H, T1, NewL), % Il pun in NewL pe pozitia potrivita
    L = [H1 | NewL]. % L va deveni [H1 | NewL] (aici NewL e corect)

insert(H, [H1 | T1], L) :-
    H =< H1, % Daca el curent e mai mic decat H1
    L = [H | [H1 | T1]]. % Atunci lista e [H, H1, T1].

insertsort([], []).
insertsort([H|T],L) :- insertsort(T,L1), insert(H,L1,L). % L1 e sortat, vreau sa pun L = L1 cu H

split(H, [], [], []). % Splitul e corect pt liste vide

split(H, [H1 | T1], A, B) :-
    H1 < H,
    split(H, T1, NewA, B), % Daca H1 e mai mic decat H, merge in stanga
    A = [H1 | NewA]. % Il pun pe H1 la inceputul listei NewA

split(H, [H1 | T1], A, B) :-
    H1 >= H,
    split(H, T1, A, NewB), % Daca H1 mai mare sau egal decat H, merge in dreapta
    B = [H1 | NewB]. % Il pun pe H1 la inceputul listei NewB

quicksort([], []).
quicksort([H | T], L) :- % sorteaza [H | T] in L
    split(H, T, A, B), % H = pivot, T = lista_mare, A = lista_stanga, B = lista_dreapta
    quicksort(A, M), % sorteaza stanga
    quicksort(B, N), % sorteaza dreapta
    append(M, [H | N], L). % fa L = [M | [H | N]]
