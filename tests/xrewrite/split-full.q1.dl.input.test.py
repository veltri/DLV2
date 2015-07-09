input = """
% Split full TGDs x10 %

p2(X) :- p1(X).
p3(X) :- p2(X).
p4(X) :- p3(X).
p5(X) :- p4(X).
p6(X) :- p5(X).
p7(X) :- p6(X).
p8(X) :- p7(X).
p9(X) :- p8(X).
p10(X) :- p9(X).
p11(X) :- p10(X).
p12(X) :- p11(X).
p13(X) :- p12(X).
p14(X) :- p13(X).
p15(X) :- p14(X).
p16(X) :- p15(X).
p17(X) :- p16(X).
p18(X) :- p17(X).
p19(X) :- p18(X).
p20(X) :- p19(X).

s2(X) :- s1(X).
s3(X) :- s2(X).
s4(X) :- s3(X).
s5(X) :- s4(X).
s6(X) :- s5(X).
s7(X) :- s6(X).
s8(X) :- s7(X).
s9(X) :- s8(X).
s10(X) :- s9(X).
s11(X) :- s10(X).
s12(X) :- s11(X).
s13(X) :- s12(X).
s14(X) :- s13(X).
s15(X) :- s14(X).
s16(X) :- s15(X).
s17(X) :- s16(X).
s18(X) :- s17(X).
s19(X) :- s18(X).
s20(X) :- s19(X).

r2(X,Y,Z) :- r1(X,Y,Z).
r3(X,Y,Z) :- r2(X,Y,Z).
r4(X,Y,Z) :- r3(X,Y,Z).
r5(X,Y,Z) :- r4(X,Y,Z).
r6(X,Y,Z) :- r5(X,Y,Z).
r7(X,Y,Z) :- r6(X,Y,Z).
r8(X,Y,Z) :- r7(X,Y,Z).
r9(X,Y,Z) :- r8(X,Y,Z).
r10(X,Y,Z) :- r9(X,Y,Z).
r11(X,Y,Z) :- r10(X,Y,Z).
r12(X,Y,Z) :- r11(X,Y,Z).
r13(X,Y,Z) :- r12(X,Y,Z).
r14(X,Y,Z) :- r13(X,Y,Z).
r15(X,Y,Z) :- r14(X,Y,Z).
r16(X,Y,Z) :- r15(X,Y,Z).
r17(X,Y,Z) :- r16(X,Y,Z).
r18(X,Y,Z) :- r17(X,Y,Z).
r19(X,Y,Z) :- r18(X,Y,Z).
r20(X,Y,Z) :- r19(X,Y,Z).



Q1(A,C) :- p1(A), r1(A, B, C), s1(C).
Q1(A,C)?
"""
output = """
#rewriting: 1
"""
