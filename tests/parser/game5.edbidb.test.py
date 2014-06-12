input = """
% Written by Francesco Scarcello.
%
% We are given eight coins labeled by either x or y. 
% The symbol b stands for "blank" and labels an empty position.
% At each step, we can move two adjacent coins into the (two) empty
% positions, so leaving empty their old positions.
% After five moves, we want an alternating configuration (xyxyxyxybb) 
% (see constraint below)

% Starting configuration (after zero moves)
true.
pos(0,1,b):-true.
pos(0,2,b):-true.
pos(0,3,x):-true.
pos(0,4,x):-true.
pos(0,5,x):-true.
pos(0,6,x):-true.
pos(0,7,y):-true.
pos(0,8,y):-true.
pos(0,9,y):-true.
pos(0,10,y):-true.

% Constraint on the final configuration (after five moves)
ok:- pos(5,1,x),pos(5,2,y),pos(5,3,x),pos(5,4,y),pos(5,5,x),pos(5,6,y),
     pos(5,7,x),pos(5,8,y),pos(5,9,b),pos(5,10,b).

:- not ok.



prec(0,1).
prec(1,2).
prec(2,3).
prec(3,4).
prec(4,5).
prec(5,6).
prec(6,7).
prec(7,8).
prec(8,9).
prec(9,10).
valid_num(1).
valid_num(2).
valid_num(3).
valid_num(4).
valid_num(5).

equal(X,X):-pos(0,X,Y).
diff(X,Y):- equal(X,X), equal(Y,Y), not equal(X,Y).

% Meanings of variables for predicate "move":
% move(#move, new.Pos.S1, new.Pos.S2, S1, S2, old.Pos S1, old.Pos.S2)
move(N,P,Q,S,R,V,W):-valid_num(N), prec(M,N), pos(M,P,b), pos(M,Q,b),
                          pos(M,V,S), pos(M,W,R), prec(P,Q), prec(V,W), 
                          not diff_move(N,V,W).
diff_move(N,V,W):- move(N,_,_,_,_,E,F),
                            diff(V,E), diff(W,F).

modified(N,P,S):-move(N,P,_,S,_,_,_).
modified(N,P,S):-move(N,_,P,_,S,_,_).
modified(N,P,b):-move(N,_,_,_,_,P,_).
modified(N,P,b):-move(N,_,_,_,_,_,P).

pos(N,P,S):- modified(N,P,S).
changed(N,P):- modified(N,P,S).
pos(N,P,S):- valid_num(N), not changed(N,P), 
             pos(M,P,S), prec(M,N).


"""
output = """
% Written by Francesco Scarcello.
%
% We are given eight coins labeled by either x or y. 
% The symbol b stands for "blank" and labels an empty position.
% At each step, we can move two adjacent coins into the (two) empty
% positions, so leaving empty their old positions.
% After five moves, we want an alternating configuration (xyxyxyxybb) 
% (see constraint below)

% Starting configuration (after zero moves)
true.
pos(0,1,b):-true.
pos(0,2,b):-true.
pos(0,3,x):-true.
pos(0,4,x):-true.
pos(0,5,x):-true.
pos(0,6,x):-true.
pos(0,7,y):-true.
pos(0,8,y):-true.
pos(0,9,y):-true.
pos(0,10,y):-true.

% Constraint on the final configuration (after five moves)
ok:- pos(5,1,x),pos(5,2,y),pos(5,3,x),pos(5,4,y),pos(5,5,x),pos(5,6,y),
     pos(5,7,x),pos(5,8,y),pos(5,9,b),pos(5,10,b).

:- not ok.



prec(0,1).
prec(1,2).
prec(2,3).
prec(3,4).
prec(4,5).
prec(5,6).
prec(6,7).
prec(7,8).
prec(8,9).
prec(9,10).
valid_num(1).
valid_num(2).
valid_num(3).
valid_num(4).
valid_num(5).

equal(X,X):-pos(0,X,Y).
diff(X,Y):- equal(X,X), equal(Y,Y), not equal(X,Y).

% Meanings of variables for predicate "move":
% move(#move, new.Pos.S1, new.Pos.S2, S1, S2, old.Pos S1, old.Pos.S2)
move(N,P,Q,S,R,V,W):-valid_num(N), prec(M,N), pos(M,P,b), pos(M,Q,b),
                          pos(M,V,S), pos(M,W,R), prec(P,Q), prec(V,W), 
                          not diff_move(N,V,W).
diff_move(N,V,W):- move(N,_,_,_,_,E,F),
                            diff(V,E), diff(W,F).

modified(N,P,S):-move(N,P,_,S,_,_,_).
modified(N,P,S):-move(N,_,P,_,S,_,_).
modified(N,P,b):-move(N,_,_,_,_,P,_).
modified(N,P,b):-move(N,_,_,_,_,_,P).

pos(N,P,S):- modified(N,P,S).
changed(N,P):- modified(N,P,S).
pos(N,P,S):- valid_num(N), not changed(N,P), 
             pos(M,P,S), prec(M,N).


"""
