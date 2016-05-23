input = """
q("1","2","3").
q("3","te,s,t!","new").
q(1,2,"Work?").

p(f(f(X,Y),Z)) :- q(X,Y,Z).
r(X,Y,Z) :- p(f(f(X,Y),Z)).
"""
output = """
q("1","2","3").
q("3","te,s,t!","new").
q(1,2,"Work?").

p(f(f(X,Y),Z)) :- q(X,Y,Z).
r(X,Y,Z) :- p(f(f(X,Y),Z)).
"""
