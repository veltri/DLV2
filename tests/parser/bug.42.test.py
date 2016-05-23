input = """
true.
a(1) :- true.
b(1) :- true.

gen1 :- not a(1).
gen2 :- not b(1).

%%%%%%%%%%%%%%%%%%%%%%

unrel | a(2).
gen3 :- unrel.

gen3 :- gen1.
a(2) :- not gen3.

gen4 :- gen2.
b(2) :- not gen4.

"""
output = """
true.
a(1) :- true.
b(1) :- true.

gen1 :- not a(1).
gen2 :- not b(1).

%%%%%%%%%%%%%%%%%%%%%%

unrel | a(2).
gen3 :- unrel.

gen3 :- gen1.
a(2) :- not gen3.

gen4 :- gen2.
b(2) :- not gen4.

"""
