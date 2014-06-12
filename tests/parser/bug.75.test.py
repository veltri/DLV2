input = """
edb(0). edb(1).
a(X) | na(X) :- edb(X).
%:- a(X). [X:X]

"""
output = """
edb(0). edb(1).
a(X) | na(X) :- edb(X).
%:- a(X). [X:X]

"""
