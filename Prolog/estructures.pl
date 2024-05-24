is_digesting(X, Y) :- just_ate(X, Y).
is_digesting(X, Y) :- just_ate(X, Z), is_digesting(Z, Y).

predecessor(X, Z) :- parent(X, Z).

predecessor(X, Z) :- parent(X, Y),predecessor(Y, Z).

p1 − point(1, 1)

p2 − point(2,3)

S − seg( Pl, P2): seg( point(1,1), point(2,3))

T − triangle( point(4,Z), point(6,4), point(7,1) )