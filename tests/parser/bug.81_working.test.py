input = """
%#maxint=2.

numero_depositi(1).

ristorante(1).
ristorante(2).

deposito(R) | -deposito(R) :- ristorante(R).

:- numero_depositi(N), not #count{D: deposito(D)}=N.

serve(D,R,Dist) :- ristorante(R), deposito(D),
                    distanza(R,D,Dist),
		    Dist = #min {Y : deposito(D1), distanza(D1,R,Y) }.

%:- serve(D,R,Dist). [Dist:]

distanza(X,L,Y):- X>L,  Y=X-L. %#int(X), #int(L), X>L,  Y=X-L.
distanza(X,L,Y):- X<=L, Y=L-X. %#int(X), #int(L), X<=L, Y=L-X.

"""
output = """
%#maxint=2.

numero_depositi(1).

ristorante(1).
ristorante(2).

deposito(R) | -deposito(R) :- ristorante(R).

:- numero_depositi(N), not #count{D: deposito(D)}=N.

serve(D,R,Dist) :- ristorante(R), deposito(D),
                    distanza(R,D,Dist),
		    Dist = #min {Y : deposito(D1), distanza(D1,R,Y) }.

%:- serve(D,R,Dist). [Dist:]

distanza(X,L,Y):- X>L,  Y=X-L. %#int(X), #int(L), X>L,  Y=X-L.
distanza(X,L,Y):- X<=L, Y=L-X. %#int(X), #int(L), X<=L, Y=L-X.

"""
