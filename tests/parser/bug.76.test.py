input = """
%% start file count.dl %%
%#maxint = 5.
n(1).
n(2).
n(3).
a(X) :- X > 0, X < #count{Z : n(Z) }. %#int(X), X > 0, X < #count{Z : n(Z) }.
b(X) :- X < #count{Z : n(Z) }. %#int(X), X < #count{Z : n(Z) }.
c(X1) :- X1 < #count{Z : n(Z) }, X=1+X1. %#int(X), X1 < #count{Z : n(Z) }, +(X, 1, X1).
%% end   %%

"""
output = """
%% start file count.dl %%
%#maxint = 5.
n(1).
n(2).
n(3).
a(X) :- X > 0, X < #count{Z : n(Z) }. %#int(X), X > 0, X < #count{Z : n(Z) }.
b(X) :- X < #count{Z : n(Z) }. %#int(X), X < #count{Z : n(Z) }.
c(X1) :- X1 < #count{Z : n(Z) }, X=1+X1. %#int(X), X1 < #count{Z : n(Z) }, +(X, 1, X1).
%% end   %%

"""
