input = """
%#maxint=27.

numero_depositi(3).

ristorante(5).
ristorante(6).
ristorante(12).
ristorante(19).
ristorante(20).
ristorante(27).

deposito(R) | -deposito(R) :- ristorante(R).

:- numero_depositi(N), not #count{D: deposito(D)}=N.

serve(R,Dist) :- ristorante(R), distanza(R,D,Dist),
		    Dist = #min {Y : deposito(D1), distanza(D1,R,Y) }.

%:- serve(R,Dist). [Dist:]

distanza(X,L,Y):- X>L,  X=L+Y. %#int(X), #int(L), X>L,  X=L+Y.
distanza(X,L,Y):- X<=L, L=X+Y. %#int(X), #int(L), X<=L, L=X+Y.

"""
output = """
%#maxint=27.

numero_depositi(3).

ristorante(5).
ristorante(6).
ristorante(12).
ristorante(19).
ristorante(20).
ristorante(27).

deposito(R) | -deposito(R) :- ristorante(R).

:- numero_depositi(N), not #count{D: deposito(D)}=N.

serve(R,Dist) :- ristorante(R), distanza(R,D,Dist),
		    Dist = #min {Y : deposito(D1), distanza(D1,R,Y) }.

%:- serve(R,Dist). [Dist:]

distanza(X,L,Y):- X>L,  X=L+Y. %#int(X), #int(L), X>L,  X=L+Y.
distanza(X,L,Y):- X<=L, L=X+Y. %#int(X), #int(L), X<=L, L=X+Y.

"""
