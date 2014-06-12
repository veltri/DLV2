input = """
n(eins).
n(zwei).
n(drei).
n(vier).
n(fuenf).
n(sechs).
n(sieben).
n(acht).
n(neun).

even(zwei).
even(vier).
even(sechs).
even(acht).

odd(I) :- n(I), not even(I).

even2(I) :- n(I), not odd(I).
"""
output = """
n(eins).
n(zwei).
n(drei).
n(vier).
n(fuenf).
n(sechs).
n(sieben).
n(acht).
n(neun).

even(zwei).
even(vier).
even(sechs).
even(acht).

odd(I) :- n(I), not even(I).

even2(I) :- n(I), not odd(I).
"""
