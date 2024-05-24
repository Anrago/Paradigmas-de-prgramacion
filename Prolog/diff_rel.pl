different(X, X) :- !, fail.
different(X, Y).

different(X, Y) :- X = Y, !, fail ; true.