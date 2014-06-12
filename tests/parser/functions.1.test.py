input = """
q(1,f(2,3)).
q(f("1","2"),"3").
q("3",f(p,q)).
q(f(1,2),"ppp").

p(f(f(X,Y),Z)) :- q(f(X,Y),Z).
p(s(X)) :- q(X, f(Y,Z)).
"""
output = """
q(1,f(2,3)).
q(f("1","2"),"3").
q("3",f(p,q)).
q(f(1,2),"ppp").

p(f(f(X,Y),Z)) :- q(f(X,Y),Z).
p(s(X)) :- q(X, f(Y,Z)).
"""
