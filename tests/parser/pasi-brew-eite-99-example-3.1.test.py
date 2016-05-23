input = """

 rule(r1). head(b,r1). pbl(a,r1). nbl(neg_b,r1). 

 rule(r2). head(neg_b,r2). nbl(b,r2).

 rule(r3). head(a,r3). nbl(neg_a,r3).

 opp(a,neg_a). 
 opp(b,neg_b). 

 pr(r1,r2). pr(r2,r3). 


"""
output = """

 rule(r1). head(b,r1). pbl(a,r1). nbl(neg_b,r1). 

 rule(r2). head(neg_b,r2). nbl(b,r2).

 rule(r3). head(a,r3). nbl(neg_a,r3).

 opp(a,neg_a). 
 opp(b,neg_b). 

 pr(r1,r2). pr(r2,r3). 


"""
