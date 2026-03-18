apare(X, [X | _]).
apare(X, [_ | T]) :-
    apare(X, T).

listaNelem(_, 0, []).

listaNelem(L, N, [H1 | T1]) :-
    N > 0,
    length([H1 | T1], N),
    apare(H1, L),
    N1 is N - 1,
    listaNelem(L, N1, T1).

listeNelem(L, N, LL) :-
    bagof(M, listaNelem(L, N, M), LL).

word(abalone, a, b, a, l, o, n, e).
word(abandon, a, b, a, n, d, o, n).
word(anagram, a, n, a, g, r, a, m).
word(connect, c, o, n, n, e, c, t).
word(elegant, e, l, e, g, a, n, t).
word(enhance, e, n, h, a, n, c, e).

crosswd(V1, V2, V3, H1, H2, H3) :-
    word(V1, _, A, _, B, _, C, _),
    word(V2, _, D, _, E, _, F, _),
    word(V3, _, G, _, H, _, I, _),
    word(H1, _, A, _, D, _, G, _),
    word(H2, _, B, _, E, _, H, _),
    word(H3, _, C, _, F, _, I, _).

connected(1,2).
connected(3,4).
connected(5,6).
connected(7,8).
connected(9,10).
connected(12,13).
connected(13,14).
connected(15,16).
connected(17,18).
connected(19,20).
connected(4,1).
connected(6,3).
connected(4,7).
connected(6,11).
connected(14,9).
connected(11,15).
connected(16,12).
connected(14,17).
connected(16,19).

pathc(X, Y) :-
    connected(X, Y).
pathc(X, Y) :-
    connected(X, Z),
    connected(Z, Y).

path(X, Y, L) :-
    connected(X, Y),
    append([], [X, Y], L).
path(X, Y, L) :-
    \+ connected(X, Y),
    pathc(X, Y),
    path(X, Z, L1),
    path(Z, Y, L2),
    append(L1, L2, L3),
    append(L3, [Y], L).

word_letters(Y, X) :-
    atom_chars(Y, X).

times([], X, 0).
times([X | T], X, N) :-
    times(T, X, N1),
    N is N1 + 1.
times([H | T], X, N) :-
    H \== X,
    times(T, X, N).

cover([], _).
cover([H | T], L) :-
    times([H | T], H, N),
    times(L, H, N),
    cover(T, L).

solution(L, Word, Len) :-
    word(Word),
    word_letters(Word, List),
    length(List, Len),
    cover(List, L).

partial_sol(List, Word, L) :-
    solution(List, Word, L).

partial_sol(List, Word, L) :-
    \+ solution(List, Word, L),
    L1 is L - 1,
    partial_sol(List, Word, L1).

topsolution(List, Word) :-
    length(List, Len),
    partial_sol(List, Word, Len).