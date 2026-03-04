distance((X1, Y1), (X2, Y2), D) :-
    D is sqrt((X2 - X1)**2 + (Y2 - Y1) ** 2).

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

line(0, Char).

line(X, Char) :-
    X > 0,
    write(Char),
    NewX is X - 1,
    line(NewX, Char).

rectangle(0, Y, Char).

rectangle(X, Y, Char) :-
    X > 0,
    line(Y, Char),
    nl,
    X1 is X - 1,
    rectangle(X1, Y, Char).

square(0, Char).
square(X, Char) :-
    rectangle(X, X, Char).

element_of(X, [X | _]).
element_of(X, [_ | Tail]) :- element_of(X, Tail).

concat_lists([], List, List).
concat_lists([Elem | List1], List2, [Elem | List3]) :-
    concat_lists(List1, List2, List3).

is_a(X):-
    X == a.
all_a([X]) :-
    is_a(X).

all_a([X | Tail]) :-
    is_a(X),
    all_a(Tail).

is_b(X):-
    X == b.
all_b([X]) :-
    is_b(X).

all_b([X | Tail]) :-
    is_b(X),
    all_b(Tail).

create_b_list(0, List).

create_b_list(Len, List):-
    Len > 0,
    Len1 is Len - 1,
    List1 is [b | List],
    create_b_list(Len1, List1).

trans_a_b(X, Y) :-
    all_a(X),
    all_b(Y),
    length(X, L1),
    length(Y, L2),
    L1 == L2.

trans_a_b(X, Y) :-
    all_a(X),
    length(X, L1),
    length(Y, L2),
    L2 == 0,
    create_b_list(L1, Y).