input = """
% |X| = 5   |Y| = 5
x1 | nx1.
x2 | nx2.
x3 | nx3.
x4 | nx4.
x5 | nx5.
y6 | ny6.
y6 :- w.
ny6 :- w.
y7 | ny7.
y7 :- w.
ny7 :- w.
y8 | ny8.
y8 :- w.
ny8 :- w.
y9 | ny9.
y9 :- w.
ny9 :- w.
y10 | ny10.
y10 :- w.
ny10 :- w.
w :- ny10, x1, x4.
w :- ny8, ny9, ny7.
w :- nx5, y9, ny10.
w :- nx1, y10, nx5.
w :- y8, ny10, ny6.
w :- ny6, nx5, ny7.
w :- ny9, x3, ny10.
w :- ny9, x3, nx5.
w :- nx3, nx5, y6.
w :- x4, y7, y8.
w :- x5, y7, x3.
w :- nx5, y7, ny10.
w :- ny6, y7, nx3.
w :- y9, y8, nx3.
w :- nx4, nx3, ny7.
w :- nx2, y10, nx1.
w :- ny10, y8, y6.
w :- nx1, x5, ny8.
w :- x3, ny8, y9.
w :- x4, nx1, y7.
w ?
"""
output = """
% |X| = 5   |Y| = 5
x1 | nx1.
x2 | nx2.
x3 | nx3.
x4 | nx4.
x5 | nx5.
y6 | ny6.
y6 :- w.
ny6 :- w.
y7 | ny7.
y7 :- w.
ny7 :- w.
y8 | ny8.
y8 :- w.
ny8 :- w.
y9 | ny9.
y9 :- w.
ny9 :- w.
y10 | ny10.
y10 :- w.
ny10 :- w.
w :- ny10, x1, x4.
w :- ny8, ny9, ny7.
w :- nx5, y9, ny10.
w :- nx1, y10, nx5.
w :- y8, ny10, ny6.
w :- ny6, nx5, ny7.
w :- ny9, x3, ny10.
w :- ny9, x3, nx5.
w :- nx3, nx5, y6.
w :- x4, y7, y8.
w :- x5, y7, x3.
w :- nx5, y7, ny10.
w :- ny6, y7, nx3.
w :- y9, y8, nx3.
w :- nx4, nx3, ny7.
w :- nx2, y10, nx1.
w :- ny10, y8, y6.
w :- nx1, x5, ny8.
w :- x3, ny8, y9.
w :- x4, nx1, y7.
w ?
"""
