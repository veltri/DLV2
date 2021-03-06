input = """

 rule(r1). head(a,r1). nbl(c,r1). 

 rule(r2). head(c,r2). nbl(b,r2).

 rule(r3). head(neg_d,r3). nbl(b,r3).

 rule(r4). head(b,r4). pbl(a,r4). nbl(neg_b,r4).

 opp(d,neg_d). 
 opp(b,neg_b). 

 pr(r1,r2). pr(r2,r3). pr(r3,r4).


"""
output = """

 rule(r1). head(a,r1). nbl(c,r1). 

 rule(r2). head(c,r2). nbl(b,r2).

 rule(r3). head(neg_d,r3). nbl(b,r3).

 rule(r4). head(b,r4). pbl(a,r4). nbl(neg_b,r4).

 opp(d,neg_d). 
 opp(b,neg_b). 

 pr(r1,r2). pr(r2,r3). pr(r3,r4).


"""
