input = """
% An example for which a wrong version of the quick model check caused 
% answer sets to be missed.
% Provided by Francesco Ricca.

not_p12|p14|p2|p11:-not p5,p24. 
p1|p15|p15|not_p18:-not p5,p24. 
p24|p8|not_p4:-p24,p2,not p25. 
p21|p5|p11|p25|not_p20:-p14. 
p15|p8|p4|p18. 
p15|p14|p9|p3. 
not_p25|p11|p24|p3. 
p2|p23|p15:-not p23. 
p2|p24|not_p12:-not p23. 
:-p22,not_p22. 
not_p19:-not p19. 


"""
output = """
% An example for which a wrong version of the quick model check caused 
% answer sets to be missed.
% Provided by Francesco Ricca.

not_p12|p14|p2|p11:-not p5,p24. 
p1|p15|p15|not_p18:-not p5,p24. 
p24|p8|not_p4:-p24,p2,not p25. 
p21|p5|p11|p25|not_p20:-p14. 
p15|p8|p4|p18. 
p15|p14|p9|p3. 
not_p25|p11|p24|p3. 
p2|p23|p15:-not p23. 
p2|p24|not_p12:-not p23. 
:-p22,not_p22. 
not_p19:-not p19. 


"""
