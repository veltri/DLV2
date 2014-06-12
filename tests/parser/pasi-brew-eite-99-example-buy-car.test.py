input = """

% Facts which are not disputable are declared as heads of 'top'

rule(top).

rule(r11). 
rule(r12). 
rule(r13). 

rule(r21).
rule(r22).
rule(r23).
rule(r24).
rule(r25).
rule(r26).
rule(r27).
rule(r28).
rule(r29).

rule(r31).
rule(r32).
rule(r33).
rule(r34).
rule(r35).
rule(r36).
rule(r37).
rule(r38).
rule(r39).

rule(r41).
rule(r42).
rule(r43).
rule(r44).
rule(r45).
rule(r46).
rule(r47).
rule(r48).
rule(r49).

head(expensive_C,top). 
head(safe_C,top).
head(safe_V,top).
head(nice_P,top).
head(fast_P,top). 


head(neg_buy_C,r11). nbl(buy_C,r11). pbl(expensive_C,r11).  
head(neg_buy_V,r12). nbl(buy_V,r12). pbl(expensive_V,r12).  
head(neg_buy_P,r13). nbl(buy_P,r13). pbl(expensive_P,r13).  

head(buy_C,r21). nbl(neg_buy_C,r21). pbl(safe_C,r21).  
head(buy_V,r22). nbl(neg_buy_V,r22). pbl(safe_V,r22).  
head(buy_P,r23). nbl(neg_buy_P,r23). pbl(safe_P,r23).  

head(neg_buy_C,r24). pbl(buy_V,r24). pbl(safe_V,r24).  
head(neg_buy_C,r27). pbl(buy_P,r27). pbl(safe_P,r27).  
head(neg_buy_V,r25). pbl(buy_P,r25). pbl(safe_P,r25).  
head(neg_buy_V,r28). pbl(buy_C,r28). pbl(safe_C,r28).  
head(neg_buy_P,r26). pbl(buy_C,r26). pbl(safe_C,r26).  
head(neg_buy_P,r29). pbl(buy_V,r29). pbl(safe_V,r29).  


head(buy_C,r31). nbl(neg_buy_C,r31). pbl(nice_C,r31).  
head(buy_V,r32). nbl(neg_buy_V,r32). pbl(nice_V,r32).  
head(buy_P,r33). nbl(neg_buy_P,r33). pbl(nice_P,r33).  

head(neg_buy_C,r34). pbl(buy_V,r34). pbl(nice_V,r34).  
head(neg_buy_C,r37). pbl(buy_P,r37). pbl(nice_P,r37).  
head(neg_buy_V,r35). pbl(buy_P,r35). pbl(nice_P,r35).  
head(neg_buy_V,r38). pbl(buy_C,r38). pbl(nice_C,r38).  
head(neg_buy_P,r36). pbl(buy_C,r36). pbl(nice_C,r36).  
head(neg_buy_P,r39). pbl(buy_V,r39). pbl(nice_V,r39).  

head(buy_C,r41). nbl(neg_buy_C,r41). pbl(fast_C,r41).  
head(buy_V,r42). nbl(neg_buy_V,r42). pbl(fast_V,r42).  
head(buy_P,r43). nbl(neg_buy_P,r43). pbl(fast_P,r43).  

head(neg_buy_C,r44). pbl(buy_V,r44). pbl(fast_V,r44).  
head(neg_buy_C,r47). pbl(buy_P,r47). pbl(fast_P,r47).  
head(neg_buy_P,r46). pbl(buy_C,r46). pbl(fast_C,r46).  
head(neg_buy_P,r49). pbl(buy_V,r49). pbl(fast_V,r49).  
head(neg_buy_V,r45). pbl(buy_P,r45). pbl(fast_P,r45).  
head(neg_buy_V,r48). pbl(buy_C,r48). pbl(fast_C,r48).  

opp(buy_C,neg_buy_C). 
opp(buy_V,neg_buy_V). 
opp(buy_P,neg_buy_P). 


% define preferences 

level(0,top).

level(1,r11). 
level(1,r12). 
level(1,r13). 

level(2,r21).
level(2,r22).
level(2,r23).
level(2,r24).
level(2,r25).
level(2,r26).
level(2,r27).
level(2,r28).
level(2,r29).

level(3,r31).
level(3,r32).
level(3,r33).
level(3,r34).
level(3,r35).
level(3,r36).
level(3,r37).
level(3,r38).
level(3,r39).

level(4,r41).
level(4,r42).
level(4,r43).
level(4,r44).
level(4,r45).
level(4,r46).
level(4,r47).
level(4,r48).
level(4,r49).

kl(0,1). kl(1,2). kl(2,3). kl(3,4).

pr(X,Y) :- kl(L1,L2), level(L1,X),level(L2,Y).
"""
output = """

% Facts which are not disputable are declared as heads of 'top'

rule(top).

rule(r11). 
rule(r12). 
rule(r13). 

rule(r21).
rule(r22).
rule(r23).
rule(r24).
rule(r25).
rule(r26).
rule(r27).
rule(r28).
rule(r29).

rule(r31).
rule(r32).
rule(r33).
rule(r34).
rule(r35).
rule(r36).
rule(r37).
rule(r38).
rule(r39).

rule(r41).
rule(r42).
rule(r43).
rule(r44).
rule(r45).
rule(r46).
rule(r47).
rule(r48).
rule(r49).

head(expensive_C,top). 
head(safe_C,top).
head(safe_V,top).
head(nice_P,top).
head(fast_P,top). 


head(neg_buy_C,r11). nbl(buy_C,r11). pbl(expensive_C,r11).  
head(neg_buy_V,r12). nbl(buy_V,r12). pbl(expensive_V,r12).  
head(neg_buy_P,r13). nbl(buy_P,r13). pbl(expensive_P,r13).  

head(buy_C,r21). nbl(neg_buy_C,r21). pbl(safe_C,r21).  
head(buy_V,r22). nbl(neg_buy_V,r22). pbl(safe_V,r22).  
head(buy_P,r23). nbl(neg_buy_P,r23). pbl(safe_P,r23).  

head(neg_buy_C,r24). pbl(buy_V,r24). pbl(safe_V,r24).  
head(neg_buy_C,r27). pbl(buy_P,r27). pbl(safe_P,r27).  
head(neg_buy_V,r25). pbl(buy_P,r25). pbl(safe_P,r25).  
head(neg_buy_V,r28). pbl(buy_C,r28). pbl(safe_C,r28).  
head(neg_buy_P,r26). pbl(buy_C,r26). pbl(safe_C,r26).  
head(neg_buy_P,r29). pbl(buy_V,r29). pbl(safe_V,r29).  


head(buy_C,r31). nbl(neg_buy_C,r31). pbl(nice_C,r31).  
head(buy_V,r32). nbl(neg_buy_V,r32). pbl(nice_V,r32).  
head(buy_P,r33). nbl(neg_buy_P,r33). pbl(nice_P,r33).  

head(neg_buy_C,r34). pbl(buy_V,r34). pbl(nice_V,r34).  
head(neg_buy_C,r37). pbl(buy_P,r37). pbl(nice_P,r37).  
head(neg_buy_V,r35). pbl(buy_P,r35). pbl(nice_P,r35).  
head(neg_buy_V,r38). pbl(buy_C,r38). pbl(nice_C,r38).  
head(neg_buy_P,r36). pbl(buy_C,r36). pbl(nice_C,r36).  
head(neg_buy_P,r39). pbl(buy_V,r39). pbl(nice_V,r39).  

head(buy_C,r41). nbl(neg_buy_C,r41). pbl(fast_C,r41).  
head(buy_V,r42). nbl(neg_buy_V,r42). pbl(fast_V,r42).  
head(buy_P,r43). nbl(neg_buy_P,r43). pbl(fast_P,r43).  

head(neg_buy_C,r44). pbl(buy_V,r44). pbl(fast_V,r44).  
head(neg_buy_C,r47). pbl(buy_P,r47). pbl(fast_P,r47).  
head(neg_buy_P,r46). pbl(buy_C,r46). pbl(fast_C,r46).  
head(neg_buy_P,r49). pbl(buy_V,r49). pbl(fast_V,r49).  
head(neg_buy_V,r45). pbl(buy_P,r45). pbl(fast_P,r45).  
head(neg_buy_V,r48). pbl(buy_C,r48). pbl(fast_C,r48).  

opp(buy_C,neg_buy_C). 
opp(buy_V,neg_buy_V). 
opp(buy_P,neg_buy_P). 


% define preferences 

level(0,top).

level(1,r11). 
level(1,r12). 
level(1,r13). 

level(2,r21).
level(2,r22).
level(2,r23).
level(2,r24).
level(2,r25).
level(2,r26).
level(2,r27).
level(2,r28).
level(2,r29).

level(3,r31).
level(3,r32).
level(3,r33).
level(3,r34).
level(3,r35).
level(3,r36).
level(3,r37).
level(3,r38).
level(3,r39).

level(4,r41).
level(4,r42).
level(4,r43).
level(4,r44).
level(4,r45).
level(4,r46).
level(4,r47).
level(4,r48).
level(4,r49).

kl(0,1). kl(1,2). kl(2,3). kl(3,4).

pr(X,Y) :- kl(L1,L2), level(L1,X),level(L2,Y).
"""
