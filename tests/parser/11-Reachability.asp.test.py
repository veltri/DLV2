input = """
reaches(X,Y) :- edge(X,Y).
reaches(X,Y) :- edge(X,Z), reaches(Z,Y).
"""
output = """
reaches(X,Y) :- edge(X,Y).
reaches(X,Y) :- edge(X,Z), reaches(Z,Y).
"""
