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
w :- x1, y9, ny8.
w :- nx3, y7, ny10.
w :- x1, nx4, y8.
w :- y8, ny10, nx2.
w :- nx5, x1, y10.
w :- x4, x3, ny9.
w :- y7, x2, x1.
w :- x4, y9, ny6.
w :- ny9, y10, x1.
w :- ny9, nx1, y10.
w :- x1, x4, ny9.
w :- nx2, x1, ny9.
w :- y9, y10, ny7.
w :- y6, y10, x4.
w :- nx4, nx3, ny6.
w :- nx4, ny6, nx1.
w :- ny10, nx4, nx1.
w :- y9, x5, y8.
w :- y8, nx3, y10.
w :- ny9, x1, nx5.
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
w :- x1, y9, ny8.
w :- nx3, y7, ny10.
w :- x1, nx4, y8.
w :- y8, ny10, nx2.
w :- nx5, x1, y10.
w :- x4, x3, ny9.
w :- y7, x2, x1.
w :- x4, y9, ny6.
w :- ny9, y10, x1.
w :- ny9, nx1, y10.
w :- x1, x4, ny9.
w :- nx2, x1, ny9.
w :- y9, y10, ny7.
w :- y6, y10, x4.
w :- nx4, nx3, ny6.
w :- nx4, ny6, nx1.
w :- ny10, nx4, nx1.
w :- y9, x5, y8.
w :- y8, nx3, y10.
w :- ny9, x1, nx5.
w ?
"""
