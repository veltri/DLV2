input = """
%#maxint=200.

articolo(sardella,cibo,3).
articolo(liquoreliqueriziapeperoncino,bibita,2).
articolo(amaro,bibita,7).

assaggia(N,T,P) | -assaggia(N,T,P) :- articolo(N,T,P).

:- #count{N : assaggia(N,_,_)} > 4.
 
:- Y>X, #count{C : assaggia(C,cibo,_)} = X, #count{B : assaggia(B,bibita,_)} = Y. %, #int(X), #int(Y).

%:- -assaggia(N,T,P). [P:]
"""
output = """
%#maxint=200.

articolo(sardella,cibo,3).
articolo(liquoreliqueriziapeperoncino,bibita,2).
articolo(amaro,bibita,7).

assaggia(N,T,P) | -assaggia(N,T,P) :- articolo(N,T,P).

:- #count{N : assaggia(N,_,_)} > 4.
 
:- Y>X, #count{C : assaggia(C,cibo,_)} = X, #count{B : assaggia(B,bibita,_)} = Y. %, #int(X), #int(Y).

%:- -assaggia(N,T,P). [P:]
"""
