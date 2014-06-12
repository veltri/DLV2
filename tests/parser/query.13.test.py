input = """
a | b.

a :- b.
b:- a.

b ?  %a,b ? 
"""
output = """
a | b.

a :- b.
b:- a.

b ?  %a,b ? 
"""
