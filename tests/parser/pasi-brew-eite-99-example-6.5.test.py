input = """

 rule(r1). head(a,r1). nbl(b,r1). 

 rule(r2). head(c,r2).

 rule(r3). head(b,r3).

 pr(r1,r2). pr(r2,r3). 


"""
output = """

 rule(r1). head(a,r1). nbl(b,r1). 

 rule(r2). head(c,r2).

 rule(r3). head(b,r3).

 pr(r1,r2). pr(r2,r3). 


"""
