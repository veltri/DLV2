input = """
p(a,b,b).
f(q,q,q,q).
q(Anno,V) :- p(Id,"VIBO VALENZIA",_), f(Id,_,Anno,V).

"""
output = """
p(a,b,b).
f(q,q,q,q).
q(Anno,V) :- p(Id,"VIBO VALENZIA",_), f(Id,_,Anno,V).

"""
