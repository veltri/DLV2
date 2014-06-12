input = """
P(a). LongPredicate(a).
Q. QuasiPredicate.

TRUE :- P(a), LongPredicate(a), Q, QuasiPredicate.
"""
output = """
P(a). LongPredicate(a).
Q. QuasiPredicate.

TRUE :- P(a), LongPredicate(a), Q, QuasiPredicate.
"""
