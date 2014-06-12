input = """
%#maxint = 15.

ship(1). ship(2). ship(3). ship(4). ship(5).

coords(X,Y) :- X > 0, Y > 0, X <= 5, Y <= 5. %#int(X), #int(Y), X > 0, Y > 0, X <= 5, Y <= 5.

ship_at(S,X,Y) | -ship_at(S,X,Y) :- ship(S), coords(X,Y).

:- ship_at(S1,X,Y), ship_at(S2,X,Y), S1 != S2.
:- ship_at(S,X1,Y1), ship_at(S,X2,Y2), X1 != X2, Y1 != Y2.
:- ship_at(S,X1,Y), ship_at(S,X2,Y), X1 < X2, not ship_at(S,X3,Y). %#succ(X1,X3), not ship_at(S,X3,Y).
:- ship_at(S,X,Y1), ship_at(S,X,Y2), Y1 < Y2, not ship_at(S,X,Y3). %#succ(Y1,Y3), not ship_at(S,X,Y3).

:- ship(S), not #count{X,Y:ship_at(S,X,Y)} = 3.
:- ship(S), not #count{Y,X:ship_at(S,X,Y)} = 3.

%:- ship_at(S,X1,Y), ship_at(S,X2,Y), ship_at(S,X3,Y), ship_at(S,X4,Y), X1 < X2, X2 < X3, X3 < X4.
%:- ship_at(S,X,Y1), ship_at(S,X,Y2), ship_at(S,X,Y3), ship_at(S,X,Y4), Y1 < Y2, Y2 < Y3, Y3 < Y4.

%:- ship_at(S,X1,Y), ship_at(S,X2,Y), #succ(X0,X1), #succ

:- rowsum(R,Su), not #sum{ S : ship_at(S,R,Y) } = Su.
:- colsum(C,Su), not #sum{ S : ship_at(S,X,C) } = Su.

sidelength(5). 
%rowsum(1,3).
rowsum(5,7).
colsum(1,7).
colsum(2,2).
colsum(5,7).
"""
output = """
%#maxint = 15.

ship(1). ship(2). ship(3). ship(4). ship(5).

coords(X,Y) :- X > 0, Y > 0, X <= 5, Y <= 5. %#int(X), #int(Y), X > 0, Y > 0, X <= 5, Y <= 5.

ship_at(S,X,Y) | -ship_at(S,X,Y) :- ship(S), coords(X,Y).

:- ship_at(S1,X,Y), ship_at(S2,X,Y), S1 != S2.
:- ship_at(S,X1,Y1), ship_at(S,X2,Y2), X1 != X2, Y1 != Y2.
:- ship_at(S,X1,Y), ship_at(S,X2,Y), X1 < X2, not ship_at(S,X3,Y). %#succ(X1,X3), not ship_at(S,X3,Y).
:- ship_at(S,X,Y1), ship_at(S,X,Y2), Y1 < Y2, not ship_at(S,X,Y3). %#succ(Y1,Y3), not ship_at(S,X,Y3).

:- ship(S), not #count{X,Y:ship_at(S,X,Y)} = 3.
:- ship(S), not #count{Y,X:ship_at(S,X,Y)} = 3.

%:- ship_at(S,X1,Y), ship_at(S,X2,Y), ship_at(S,X3,Y), ship_at(S,X4,Y), X1 < X2, X2 < X3, X3 < X4.
%:- ship_at(S,X,Y1), ship_at(S,X,Y2), ship_at(S,X,Y3), ship_at(S,X,Y4), Y1 < Y2, Y2 < Y3, Y3 < Y4.

%:- ship_at(S,X1,Y), ship_at(S,X2,Y), #succ(X0,X1), #succ

:- rowsum(R,Su), not #sum{ S : ship_at(S,R,Y) } = Su.
:- colsum(C,Su), not #sum{ S : ship_at(S,X,C) } = Su.

sidelength(5). 
%rowsum(1,3).
rowsum(5,7).
colsum(1,7).
colsum(2,2).
colsum(5,7).
"""
