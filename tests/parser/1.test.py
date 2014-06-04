input = """
\E Y father(Y,X) :- person(X).
person(X) :- father(X,Y). 
\E X,Y p(X,Y,Z) | \E K q(K) :- q(Z),3<>5.
a(X):-p(35,B,3-(4*434+(443/32)-4344)),X!=10.
:~a(Y),d(10). [32@32] 
:-b(c),a(X),fdf("ciao").
X<{a(X):b(X),c(X),not d(X)}<Y.
X<{r(X):s(X),c(X),not d(X)}<Y.
{a(X):b(X),c(X),not d(X);a(X):c(X),not h(X,Y)}<Y:-prova.
prop(X):-X>=#count{10,T,prova:a(T),b(prova);X:h(X,10)}.
q(3)?
"""
output = """
\E Y father(Y,X) :- person(X).
person(X) :- father(X,Y).
\E X,Y p(X,Y,Z) | \E K q(K) :- q(Z), 3!=5.
a(X) :- p(35,B,3-(4*434+(443/32)-4344)), X!=10.
prop(X) :- X>=#count{10,T,prova:a(T),b(prova);X:h(X,10)}.
:- b(c), a(X), fdf("ciao").
:~ a(Y), d(10). [32@32]
X<{a(X):b(X),c(X),not d(X)}<Y.
X<{r(X):s(X),c(X),not d(X)}<Y.
{a(X):b(X),c(X),not d(X);a(X):c(X),not h(X,Y)}<Y :- prova.
q(3)?
"""
