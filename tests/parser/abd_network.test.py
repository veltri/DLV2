input = """
reaches(X,X) :- node(X), not offline(X).
reaches(X,Z) :- reaches(X,Y), connected(Y,Z), not offline(Z).

connected(a,b).
connected(b,c).
connected(c,e).
connected(b,d).
connected(d,e).
connected(a,f).
connected(f,e).

node(a).
node(b).
node(c).
node(d).
node(e).
node(f).


"""
output = """
reaches(X,X) :- node(X), not offline(X).
reaches(X,Z) :- reaches(X,Y), connected(Y,Z), not offline(Z).

connected(a,b).
connected(b,c).
connected(c,e).
connected(b,d).
connected(d,e).
connected(a,f).
connected(f,e).

node(a).
node(b).
node(c).
node(d).
node(e).
node(f).


"""
