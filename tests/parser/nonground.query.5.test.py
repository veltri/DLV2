input = """
% This is solvable just by the grounding.

person(gerald ,pfeifer  ,1842).
person(peter  ,meyers   ,47).
person(nicola ,leone    ,1843).
person(ornella,muti     ,47).
person(michi  ,konsel   ,11).
person(peter  ,wohlfahrt,11).

department(  11,"Football").
department(1842,"DBAI").
department(1843,"Datenbank Irgendwas").
department(4711,"Olefactory Chemistry").
"""
output = """
% This is solvable just by the grounding.

person(gerald ,pfeifer  ,1842).
person(peter  ,meyers   ,47).
person(nicola ,leone    ,1843).
person(ornella,muti     ,47).
person(michi  ,konsel   ,11).
person(peter  ,wohlfahrt,11).

department(  11,"Football").
department(1842,"DBAI").
department(1843,"Datenbank Irgendwas").
department(4711,"Olefactory Chemistry").
"""
