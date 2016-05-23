input = """
a(X1,X2,X3) :- b(X1,X2), b(X2,X3).

b(Yin,Yang) :- c(Yin), d(Yang).

c(1).

c(2). d(2).

d(3).
"""
output = """
a(X1,X2,X3) :- b(X1,X2), b(X2,X3).

b(Yin,Yang) :- c(Yin), d(Yang).

c(1).

c(2). d(2).

d(3).
"""
