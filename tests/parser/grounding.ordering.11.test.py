input = """
male(john).    republican(john).
male(matt).    republican(matt).
female(joana). republican(joana).
female(luise). democrat(luise).

moreMaleRepublicans :- 
   #count{X:republican(X), female(X)} < N, 
   #count{Y: republican(Y), male(Y)}  = N. 
  
"""
output = """
male(john).    republican(john).
male(matt).    republican(matt).
female(joana). republican(joana).
female(luise). democrat(luise).

moreMaleRepublicans :- 
   #count{X:republican(X), female(X)} < N, 
   #count{Y: republican(Y), male(Y)}  = N. 
  
"""
