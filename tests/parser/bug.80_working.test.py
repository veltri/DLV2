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

distanza(X,L,Y):- X>L,  Y=X-L. %#int(X), #int(L), X>L,  Y=X-L.
distanza(X,L,Y):- X<=L, Y=L-X. %#int(X), #int(L), X<=L, Y=L-X.

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

distanza(X,L,Y):- X>L,  Y=X-L. %#int(X), #int(L), X>L,  Y=X-L.
distanza(X,L,Y):- X<=L, Y=L-X. %#int(X), #int(L), X<=L, Y=L-X.

"""
