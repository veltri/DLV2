input = """

 rule(r1). head(a,r1). nbl(neg_a,r1). 

 rule(r2). head(neg_a,r2). nbl(a,r2).

 rule(r3). head(neg_a,r3). pbl(a,r3). nbl(c,r3).

 rule(r4). head(c,r4). nbl(neg_c,r4).

 rule(r5). head(neg_a,r5). pbl(a,r5). nbl(b,r5).

 rule(r6). head(b,r6). nbl(neg_b,r6).

 opp(a,neg_a). 
 opp(b,neg_b). 
 opp(c,neg_c). 

 pr(r1,r2). pr(r2,r3). pr(r3,r4). pr(r4,r5). pr(r5,r6).


"""
output = """

 rule(r1). head(a,r1). nbl(neg_a,r1). 

 rule(r2). head(neg_a,r2). nbl(a,r2).

 rule(r3). head(neg_a,r3). pbl(a,r3). nbl(c,r3).

 rule(r4). head(c,r4). nbl(neg_c,r4).

 rule(r5). head(neg_a,r5). pbl(a,r5). nbl(b,r5).

 rule(r6). head(b,r6). nbl(neg_b,r6).

 opp(a,neg_a). 
 opp(b,neg_b). 
 opp(c,neg_c). 

 pr(r1,r2). pr(r2,r3). pr(r3,r4). pr(r4,r5). pr(r5,r6).


"""
