input = """
% run with option -- depgraph
% component of b must be HCF

a(1) | -a(1).
b(X) | b(X) :-  a(X).

"""
output = """
% run with option -- depgraph
% component of b must be HCF

a(1) | -a(1).
b(X) | b(X) :-  a(X).

"""
