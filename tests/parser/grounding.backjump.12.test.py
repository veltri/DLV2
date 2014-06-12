input = """
meets_conditions(S,R,P):- component(P,R),
                    var_k(S,X), var_k(R,Y), not var_k(S,Y), not var_k(R,X). 

component(P,R):- var1(P,X), k_vertex1(R,_), not var_k(R,X).
component(query,root).

var_k(S,X):- k_vertex1(S,P), var1(P,X).

k_vertex1("a",a).
k_vertex1("c",c).
k_vertex1("d",d).
k_vertex1("e",e).
k_vertex1("a_c",a).
k_vertex1("a_c",c).
k_vertex1("a_d",a).
k_vertex1("a_d",d).
k_vertex1("a_e",a).
k_vertex1("a_e",e).
k_vertex1("c_d",c).
k_vertex1("c_d",d).
k_vertex1("c_e",c).
k_vertex1("c_e",e).
k_vertex1("d_e",d).
k_vertex1("d_e",e).
k_vertex1("a_c_d",a).
k_vertex1("a_c_d",c).
k_vertex1("a_c_d",d).
k_vertex1("a_c_e",a).
k_vertex1("a_c_e",c).
k_vertex1("a_c_e",e).
k_vertex1("a_d_e",a).
k_vertex1("a_d_e",d).
k_vertex1("a_d_e",e).
k_vertex1("c_d_e",c).
k_vertex1("c_d_e",d).
k_vertex1("c_d_e",e).
var1(a,x1).
var1(a,x2).
var1(a,x4).
var1(a,x5).
var1(a,xp1).
var1(a,xp2).
var1(a,xp4).
var1(a,xp5).
var1(c,x4).
var1(c,x5).
var1(c,xp4).
var1(c,xp5).
var1(c,y).
var1(c,x6).
var1(c,xp6).
var1(d,x1).
var1(d,x4).
var1(d,z).
var1(e,x2).
var1(e,x5).
var1(e,z).

"""
output = """
meets_conditions(S,R,P):- component(P,R),
                    var_k(S,X), var_k(R,Y), not var_k(S,Y), not var_k(R,X). 

component(P,R):- var1(P,X), k_vertex1(R,_), not var_k(R,X).
component(query,root).

var_k(S,X):- k_vertex1(S,P), var1(P,X).

k_vertex1("a",a).
k_vertex1("c",c).
k_vertex1("d",d).
k_vertex1("e",e).
k_vertex1("a_c",a).
k_vertex1("a_c",c).
k_vertex1("a_d",a).
k_vertex1("a_d",d).
k_vertex1("a_e",a).
k_vertex1("a_e",e).
k_vertex1("c_d",c).
k_vertex1("c_d",d).
k_vertex1("c_e",c).
k_vertex1("c_e",e).
k_vertex1("d_e",d).
k_vertex1("d_e",e).
k_vertex1("a_c_d",a).
k_vertex1("a_c_d",c).
k_vertex1("a_c_d",d).
k_vertex1("a_c_e",a).
k_vertex1("a_c_e",c).
k_vertex1("a_c_e",e).
k_vertex1("a_d_e",a).
k_vertex1("a_d_e",d).
k_vertex1("a_d_e",e).
k_vertex1("c_d_e",c).
k_vertex1("c_d_e",d).
k_vertex1("c_d_e",e).
var1(a,x1).
var1(a,x2).
var1(a,x4).
var1(a,x5).
var1(a,xp1).
var1(a,xp2).
var1(a,xp4).
var1(a,xp5).
var1(c,x4).
var1(c,x5).
var1(c,xp4).
var1(c,xp5).
var1(c,y).
var1(c,x6).
var1(c,xp6).
var1(d,x1).
var1(d,x4).
var1(d,z).
var1(e,x2).
var1(e,x5).
var1(e,z).

"""
