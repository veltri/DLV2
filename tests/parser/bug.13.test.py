input = """
F1_melts | F2_melts :- B_high.
F1_melts | F2_melts :- R1_low, R2_low.
Light_off :- F1_melts.
Light_off :- F2_melts.
Light_off :- Bulb_broken.
"""
output = """
F1_melts | F2_melts :- B_high.
F1_melts | F2_melts :- R1_low, R2_low.
Light_off :- F1_melts.
Light_off :- F2_melts.
Light_off :- Bulb_broken.
"""
