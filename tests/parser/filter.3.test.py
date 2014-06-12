input = """
propositional_and_quite_a_long_name | -propositional_and_quite_a_long_name.
nonprop1(X) | -nonprop1(X) :- domain(X), propositional_and_quite_a_long_name.
nonprop2(X,Y) | -nonprop2(X,Y) :- domain(X), domain(Y), -propositional_and_quite_a_long_name.

domain(d).

"""
output = """
propositional_and_quite_a_long_name | -propositional_and_quite_a_long_name.
nonprop1(X) | -nonprop1(X) :- domain(X), propositional_and_quite_a_long_name.
nonprop2(X,Y) | -nonprop2(X,Y) :- domain(X), domain(Y), -propositional_and_quite_a_long_name.

domain(d).

"""
