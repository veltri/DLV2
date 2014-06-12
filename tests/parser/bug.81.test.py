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

distanza(X,L,Y):- X>L,  X=L+Y. %#int(X), #int(L), X>L,  X=L+Y.
distanza(X,L,Y):- X<=L, L=X+Y. %#int(X), #int(L), X<=L, L=X+Y.

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

distanza(X,L,Y):- X>L,  X=L+Y. %#int(X), #int(L), X>L,  X=L+Y.
distanza(X,L,Y):- X<=L, L=X+Y. %#int(X), #int(L), X<=L, L=X+Y.

"""
