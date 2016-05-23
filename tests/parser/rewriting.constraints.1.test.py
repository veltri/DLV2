input = """
a(T) | -a(T) :- c(T). %, #succ(T,_).
c(T1) :- a(T). %, #succ(T,T1), #int(T).
c(0) :- true. true.
%c(#maxint)?
"""
output = """
a(T) | -a(T) :- c(T). %, #succ(T,_).
c(T1) :- a(T). %, #succ(T,T1), #int(T).
c(0) :- true. true.
%c(#maxint)?
"""
