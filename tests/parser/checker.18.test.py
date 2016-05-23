input = """
% Synthetic example constructed to trigger a bug in the quick model check
% (with -OH- set, to control choices).

:- not ta2.
:- not ta3.
ta1. 

CHOICE1 | ta3. 
CHOICE2 | fa1 :- ta3, CHOICE1. 
CHOICE1 | CHOICE3 :- ta2. 

ta2 | ta1 :- ta3. 
ta3 | fa3 :- ta3, ta1,  not CHOICE3. 
ta2 | fa2 . 
ta1 | ta3. 

"""
output = """
% Synthetic example constructed to trigger a bug in the quick model check
% (with -OH- set, to control choices).

:- not ta2.
:- not ta3.
ta1. 

CHOICE1 | ta3. 
CHOICE2 | fa1 :- ta3, CHOICE1. 
CHOICE1 | CHOICE3 :- ta2. 

ta2 | ta1 :- ta3. 
ta3 | fa3 :- ta3, ta1,  not CHOICE3. 
ta2 | fa2 . 
ta1 | ta3. 

"""
