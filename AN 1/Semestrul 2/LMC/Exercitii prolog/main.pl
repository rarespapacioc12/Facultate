% Probleme din modelul de examen

% (P5) [1 punct] Definit¸i un predicat expand intervals/2 care, pentru o list˘a de perechi de
% numere naturale, calculeaz˘a lista R format˘a ˆın felul urm˘ator: Pentru orice i mai mic decˆat
% lungimea lui L, dac˘a (N, M) este perechea de pe pozit¸ia i din L, atunci pe pozit¸ia i din R,
% se va afla lista tuturor numerelor mai mari sau egale ca N ¸si mai mici sau egale cu M.
% Exemplu:
% ?- expand_intervals([(1, 3), (5, 5), (5, 3), (2, 6)], R).
% R = [[1, 2, 3], [5], [], [2, 3, 4, 5, 6]].

expand_interval((N, N), [N]).
expand_interval((M, N), X) :-
    M > N,
    X = [].
expand_interval((M, N), X) :-
    M < N,
    M1 is M + 1,
    expand_interval((M1, N), X1),
    append([M], X1, X).

expand_intervals([], []).
expand_intervals([H | T], R) :-
    expand_intervals(T, R1),
    expand_interval(H, C),
    append([C], R1, R).


% (P6) [1 punct] Consider˘am ˆın continuare reprezentarea formulelor logicii propozit¸ionale
% folosit˘a ˆın laboratorul 5. Scriet¸i un predicat assoc and care, primind ca argument dou˘a formule Phi, Psi, este adev˘arat daca ¸si numai dac˘a Phi ¸si Psi sunt formate doar din conjunct¸ii
% ¸si variabile ¸si, ˆın plus, Psi se poate obt¸ine din Phi prin reasocierea parantezelor din ea (dar
% p˘astrˆand ordinea ˆın care apar variabilele ˆın conjunct¸ii).
% Exemplu:
% ?- assoc_and(si(si(a, b), c), si(a, si(b, c))).
% true
% ?- assoc_and(si(si(a, b), si(c, d)), si(a, si(b, si(c, d)))).
% true
% ?- assoc_and(si(a, b), si(b, a)).
% false
% ?- assoc_and(a, a).
% true
% ?- assoc_and(sau(a, sau(b, c)), sau(sau(a, b), c)).
% false

si(X, Y).

var_list(si(X, Y), L) :-
    var_list(X, L1),
    var_list(Y, L2),
    append(L1, L2, L).
var_list(X, [X]) :-
    si(A, B) \= X.

si_doar(A) :-
    si(X, Y) \= A.

si_doar(si(X, Y)) :-
    si_doar(X),
    si_doar(Y).

assoc_and(A, A).
assoc_and(A, B) :-
    si_doar(A),
    si_doar(B),
    var_list(A, L1),
    var_list(B, L2),
    L1 == L2.


% (P7) [1 punct] Definit, i un predicat dropN/3, astfel ˆıncˆat, pentru orice liste L, R s, i num˘ar
% natural N, dropN(L, R, N) este adev˘arat dac˘a s, i numai dac˘a R este lista care rezult˘a din
% eliminarea ultimelor N elemente ale lui L. Predicatul va fi fals ˆın cazul ˆın care N este mai
% mare decˆat lungimea lui L.
% Exemplu:
% ?- dropN([a, b, c, b], R, 2).
% R = [a, b]
% ?- dropN([a, b, c], R, 5).
% false.

getFirstN(H, [], 0).
getFirstN([H | T], R, X) :-
    X1 is X - 1,
    getFirstN(T, R1, X1),
    append([H], R1, R).
dropN(L, R, N) :-
    length(L, N1),
    N2 is N1 - N,
    getFirstN(L, R, N2).


% in continuare, probleme de pe
% https://www.ic.unicamp.br/~meidanis/courses/mc336/2009s2/prolog/problemas/

% ultimul elem din lista
my_last(X, [X]).
my_last(X, [_ | T]) :-
    my_last(X, T).

% penultimul elem din lista
last_but_one(X, [H | T]) :-
    length([H | T], N),
    N == 2,
    X = H.

last_but_one(X, [H | T]) :-
    length([H | T], N),
    N > 2,
    last_but_one(X, T).

% elementul de la pozitia N (indexare de la 1)
element_at(X, [H | _], N) :-
    N == 1,
    X = H.

element_at(X, [_ | T], N) :-
    N \== 1,
    N1 is N - 1,
    element_at(X, T, N1).

% lungimea listei
my_len([], 0).
my_len([_ | T], N) :-
    my_len(T, N1),
    N is N1 + 1.

% reverse a list
my_rev([], []).
my_rev([H | T], L) :-
    my_rev(T, L1),
    append(L1, [H], L).

% check whether a list is a palyndrome
palindrome(L1) :-
    my_rev(L1, L1).

% flatten a list (ex: [a, [b, [c, d], e]] -> [a, b, c, d, e])

my_flatten([], []).
my_flatten([H | T], X) :-
    my_flatten(T, X1),
    is_list(H),
    my_flatten(H, H1),
    append(H1, X1, X).
my_flatten([H | T], X) :-
    my_flatten(T, X1),
    \+ is_list(H),
    append([H], X1, X).

% eliminate consecutive duplicates of list elements
compress([], []).
compress([H], [H]).
compress([H | T1], X) :-
    compress(T1, X1),
    [H1 | _] = X1,
    H1 == H,
    X = X1.
compress([H | T1], X) :-
    compress(T1, X1),
    [H1 | _] = X1,
    H1 \== H,
    append([H], X1, X).

% p14 - duplicate the elements of a list

dupli([], []).
dupli([H | T], X) :-
    dupli(T, X1),
    append([H], X1, X2),
    append([H], X2, X).

ntimes(_, [], 0).
ntimes(A, L, N) :-
    N1 is N - 1,
    ntimes(A, L1, N1),
    append([A], L1, L).

dupli([], _, []).
dupli([H | T], N, L) :-
    dupli(T, N, L1),
    ntimes(H, L2, N),
    append(L2, L1, L).

% P17 Split a list into two parts; the length of the first part is given.
