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
w :- ny7, ny6, x2.
w :- ny10, ny6, x2.
w :- x3, x2, ny10.
w :- ny7, x2, ny8.
w :- ny6, nx5, x4.
w :- y8, nx5, y9.
w :- ny9, ny6, nx3.
w :- x1, nx4, y6.
w :- y8, y6, nx1.
w :- ny10, nx5, x4.
w :- nx4, y10, y8.
w :- x4, nx2, ny9.
w :- y8, y10, y7.
w :- y7, nx3, nx1.
w :- ny9, nx2, nx5.
w :- y10, x4, ny7.
w :- y8, y10, y6.
w :- ny7, y8, x4.
w :- ny6, ny9, nx5.
w :- ny8, nx3, ny7.
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
w :- ny7, ny6, x2.
w :- ny10, ny6, x2.
w :- x3, x2, ny10.
w :- ny7, x2, ny8.
w :- ny6, nx5, x4.
w :- y8, nx5, y9.
w :- ny9, ny6, nx3.
w :- x1, nx4, y6.
w :- y8, y6, nx1.
w :- ny10, nx5, x4.
w :- nx4, y10, y8.
w :- x4, nx2, ny9.
w :- y8, y10, y7.
w :- y7, nx3, nx1.
w :- ny9, nx2, nx5.
w :- y10, x4, ny7.
w :- y8, y10, y6.
w :- ny7, y8, x4.
w :- ny6, ny9, nx5.
w :- ny8, nx3, ny7.
w ?
"""
