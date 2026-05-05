non(X) :-
    \+ X.

si(X, Y) :-
    X,
    Y.

sau(X, Y) :-
    X.

sau(X, Y) :- 
    Y.

imp(X, Y) :-
    sau(non(X), Y).

vars(X, [X]) :-
    atom(X).
vars(non(X), S) :-
    vars(X, S).
vars(sau(X, Y), S) :-
    vars(X, S1),
    vars(Y, S2),
    union(S1, S2, S).
vars(si(X, Y), S) :-
    vars(X, S1),
    vars(Y, S2),
    union(S1, S2, S).
vars(imp(X, Y), S) :-
    vars(X, S1),
    vars(Y, S2),
    union(S1, S2, S).

val(X, [(X, E) | T], A) :-
    A is E.

val(X, [_ | T], A) :-
    val(X, T, A).

bnon(0, 1).
bnon(1, 0).

bsi(1, 1, 1).
bsi(0, 1, 0).
bsi(1, 0, 0).
bsi(0, 0, 0).

bsau(1, 1, 1).
bsau(0, 1, 1).
bsau(1, 0, 1).
bsau(0, 0, 0).

bimp(A, B, C) :-
    bnon(A, C1),
    bsau(C1, B, C).

eval(Phi, [_ | T], A) :-
    atom(Phi),
    eval(Phi, T, A).

eval(Phi, [(Phi, E) | _], A) :-
    atom(Phi),
    A is E. 

eval(si(Phi, Psi), E, A) :-
    eval(Phi, E, A1),
    eval(Psi, E, A2),
    bsi(A1, A2, A).

eval(sau(Phi, Psi), E, A) :-
    eval(Phi, E, A1),
    eval(Psi, E, A2),
    bsau(A1, A2, A).

eval(imp(Phi, Psi), E, A) :-
    eval(Phi, E, A1),
    eval(Psi, E, A2),
    bimp(A1, A2, A).

eval(non(Phi), E, A) :-
    eval(Phi, E, A1),
    bnon(A1, A).

evals(Form, [], []).
evals(Form, [E | T1], [A | T2]) :-
    eval(Form, E, A),
    evals(Form, T1, T2).

evs_helper([], E, [E]).

evs_helper([H | T], E, Evals) :-
    evs_helper(T, [(H, 0) | E], Evals0),
    evs_helper(T, [(H, 1) | E], Evals1),
    append(Evals0, Evals1, Evals).

evs(Var, Evals) :-
    evs_helper(Var, [], Evals).

all_evals(Form, As) :-
    vars(Form, Var),
    evs(Var, Evals),
    evals(Form, Evals, As).

all_ones([]).
all_ones([1 | T]) :-
    all_ones(T).
taut(Form) :-
    all_evals(Form, As),
    all_ones(As).