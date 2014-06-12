input = """
ok:- #count{V:b(V)}=X,  not p(X).

b(1).
p(2).
"""
output = """
ok:- #count{V:b(V)}=X,  not p(X).

b(1).
p(2).
"""
