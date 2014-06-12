input = """
c(1) | c(2) | c(3).
d(1) | d(2) | d(3). 
e(1) | e(2) | e(3).
a(X) :- c(X).

b(Y) :- d(Y).
okay :- 0<#count{V :a(V)} <3. 
okay1 :- 0<#count{V :a(V)} <2.
okay2 :-0<#count{V :b(V)} <3.
okay3 :-0<#count{V :e(V)} <3.
"""
output = """
c(1) | c(2) | c(3).
d(1) | d(2) | d(3). 
e(1) | e(2) | e(3).
a(X) :- c(X).

b(Y) :- d(Y).
okay :- 0<#count{V :a(V)} <3. 
okay1 :- 0<#count{V :a(V)} <2.
okay2 :-0<#count{V :b(V)} <3.
okay3 :-0<#count{V :e(V)} <3.
"""
