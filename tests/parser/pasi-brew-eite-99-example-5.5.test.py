input = """

 rule(r1). head(c,r1). nbl(b,r1). 

 rule(r2). head(b,r2). nbl(a,r2).

 pr(r1,r2).


"""
output = """

 rule(r1). head(c,r1). nbl(b,r1). 

 rule(r2). head(b,r2). nbl(a,r2).

 pr(r1,r2).


"""
