input = """
%Non ground rules, constraints and weak constraints with the aggregate
%function count in the body. Guards for count are integer.
%All the functions count are satisfied.  

a(1).
b(1).
p(1).
q(1).
c(1,1).
c(1,2).

%----  #count{nonGroundAtoms} op int ----(at the end)

okay01(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} = 2.           
  
okay02(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} < 3.           
 
okay03(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} <= 2.          

okay04(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} > 1.           
    
okay05(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} >= 2.          

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} = 3.
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} = 3.           

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} < 2.           
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} < 2. 
   
:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} <= 1.          
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} <= 1.          

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} > 2.           
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} > 2. 

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} >= 3.
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} >= 3.

%----  #count{nonGroundAtoms} op int ----(at the beginning)

okay06(M, N) :- #count{V : a(M),b(N),c(M,V)} = 2, p(M),q(N).           

okay07(M, N) :- #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).           

okay08(M, N) :- #count{V : a(M),b(N),c(M,V)} <= 2, p(M),q(N).          

okay09(M, N) :- #count{V : a(M),b(N),c(M,V)} > 1, p(M),q(N).           

okay10(M, N) :- #count{V : a(M),b(N),c(M,V)} >= 2, p(M),q(N).    

:- #count{V : a(M),b(N),c(M,V)} = 3, p(M),q(N).  
%:- #count{V : a(M),b(N),c(M,V)} = 3, p(M),q(N).         

:- #count{V : a(M),b(N),c(M,V)} < 2, p(M),q(N).
%:- #count{V : a(M),b(N),c(M,V)} < 2, p(M),q(N).           

:- #count{V : a(M),b(N),c(M,V)} <= 1, p(M),q(N). 
%:- #count{V : a(M),b(N),c(M,V)} <= 1, p(M),q(N).          

:- #count{V : a(M),b(N),c(M,V)} > 2, p(M),q(N).  
%:- #count{V : a(M),b(N),c(M,V)} > 2, p(M),q(N).          

:- #count{V : a(M),b(N),c(M,V)} >= 3, p(M),q(N). 
%:- #count{V : a(M),b(N),c(M,V)} >= 3, p(M),q(N).     

%----  #count{nonGroundAtoms} op int ----(in the middle)

okay11(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} = 2, q(N).           

okay12(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} < 3, q(N).           

okay13(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} <= 2, q(N).          

okay14(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} > 1, q(N).           

okay15(M, N) :- p(M),#count{V : a(M),b(N),c(M,V)} >= 2, q(N).    

:- p(M), #count{V : a(M),b(N),c(M,V)} = 3, q(N).  
%:- p(M), #count{V : a(M),b(N),c(M,V)} = 3, q(N).         

:- p(M), #count{V : a(M),b(N),c(M,V)} < 2, q(N).
%:- p(M), #count{V : a(M),b(N),c(M,V)} < 2, q(N).           

:- p(M), #count{V : a(M),b(N),c(M,V)} <= 1, q(N). 
%:- p(M), #count{V : a(M),b(N),c(M,V)} <= 1, q(N).          

:- p(M), #count{V : a(M),b(N),c(M,V)} > 2, q(N).  
%:- p(M), #count{V : a(M),b(N),c(M,V)} > 2, q(N).          

:- p(M), #count{V : a(M),b(N),c(M,V)} >= 3, q(N). 
%:- p(M), #count{V : a(M),b(N),c(M,V)} >= 3, q(N).
 
%----  int op #count{nonGroundAtoms}----(at the end) 

okay16(M, N) :- p(M),q(N), 2 = #count{V : a(M),b(N),c(M,V)}.           

okay17(M, N) :- p(M),q(N), 1 < #count{V : a(M),b(N),c(M,V)}.           

okay18(M, N) :- p(M),q(N), 2 <= #count{V : a(M),b(N),c(M,V)}.           

okay19(M, N) :- p(M),q(N), 3  > #count{V : a(M),b(N),c(M,V)}.           

okay20(M, N) :- p(M),q(N), 2 >= #count{V : a(M),b(N),c(M,V)}.     

:- p(M),q(N), 1 = #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 1 = #count{V : a(M),b(N),c(M,V)}.  
 
:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)}.

:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)}.

:- p(M),q(N), 2 > #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 2 > #count{V : a(M),b(N),c(M,V)}.           

:- p(M),q(N), 1 >= #count{V : a(M),b(N),c(M,V)}.          
%:- p(M),q(N), 1 >= #count{V : a(M),b(N),c(M,V)}.          

%----  int op #count{nonGroundAtoms}---- (at the beginning)

okay21(M, N) :- 2 = #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          

okay22(M, N) :- 1 < #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

okay23(M, N) :- 2 <= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

okay24(M, N) :- 3 > #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          

okay25(M, N) :- 2 >= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

:- 1 = #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          
%:- 1 = #count{V : a(M),b(N),c(M,V)}, p(M),q(N).   

:- 2 < #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         
%:- 2 < #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

:- 3 <= #count{V : a(M),b(N),c(M,V)}, p(M),q(N). 
%:- 3 <= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

:- 2 > #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          
%:- 2 > #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          

:- 1 >= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).     
%:- 1 >= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).

    
%----  int op #count{nonGroundAtoms}---- (in the middle)

okay26(M, N) :- p(M), 2 = #count{V : a(M),b(N),c(M,V)}, q(N).          

okay27(M, N) :- p(M), 1 < #count{V : a(M),b(N),c(M,V)}, q(N).         

okay28(M, N) :- p(M), 2 <= #count{V : a(M),b(N),c(M,V)}, q(N).         

okay29(M, N) :- p(M), 3 > #count{V : a(M),b(N),c(M,V)}, q(N).          

okay30(M, N) :- p(M), 2 >= #count{V : a(M),b(N),c(M,V)}, q(N).         

:- p(M), 1 = #count{V : a(M),b(N),c(M,V)}, q(N).          
%:- p(M), 1 = #count{V : a(M),b(N),c(M,V)}, q(N).   

:- p(M), 2 < #count{V : a(M),b(N),c(M,V)}, q(N).         
%:- p(M), 2 < #count{V : a(M),b(N),c(M,V)}, q(N).         

:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)}, q(N). 
%:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)}, q(N).         

:- p(M), 2 > #count{V : a(M),b(N),c(M,V)}, q(N).          
%:- p(M), 2 > #count{V : a(M),b(N),c(M,V)}, q(N).          

:- p(M), 1 >= #count{V : a(M),b(N),c(M,V)}, q(N).     
%:- p(M), 1 >= #count{V : a(M),b(N),c(M,V)}, q(N).

%---- int < #count{nonGroundAtoms} < int ----


okay31(M,N) :- p(M),q(N), 1 < #count{V : a(M),b(N),c(M,V)} < 3.      

okay32(M,N) :- 1 < #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).

okay33(M,N) :- p(M), 1 < #count{V : a(M),b(N),c(M,V)} < 3, q(N).   


:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} < 3.      

:- 2 < #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).   
  
:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} < 3, q(N).


%:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} < 3.      

%:- 2 < #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).

%:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} < 3, q(N).     

%---- int < #count{} <= int ----


okay34(M, N) :- p(M),q(N), 1 < #count{V : a(M),b(N),c(M,V)} <= 2. 

okay35(M, N) :- 1 < #count{V : a(M),b(N),c(M,V)} <= 2, p(M),q(N). 

okay36(M, N) :- p(M), 1 < #count{V : a(M),b(N),c(M,V)} <= 2, q(N).


:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} <= 3.     

:- 2 < #count{V : a(M),b(N),c(M,V)} <= 3, p(M),q(N).

:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} <= 3, q(N).  


%:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} <= 3.     

%:- 2 < #count{V : a(M),b(N),c(M,V)} <= 3, p(M),q(N).

%:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} <= 3, q(N).

%---- int <= #count{nonGroundAtoms} < int ----

okay37(M, N) :- p(M),q(N), 2 <= #count{V : a(M),b(N),c(M,V)} < 3.     

okay38(M, N) :- 2 <= #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).     

okay39(M, N) :- p(M), 2 <= #count{V : a(M),b(N),c(M,V)} < 3, q(N).


:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} < 4.     

:- 3 <= #count{V : a(M),b(N),c(M,V)} < 4, p(M),q(N).  

:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} < 4, q(N).


%:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} < 4.     

%:- 3 <= #count{V : a(M),b(N),c(M,V)} < 4, p(M),q(N).

%:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} < 4, q(N).
   
%---- int <= #count{nonGroundAtoms} <= int ----


okay40(M, N) :- p(M),q(N), 2 <= #count{V : a(M),b(N),c(M,V)} <= 3.    

okay41(M, N) :- 2 <= #count{V : a(M),b(N),c(M,V)} <= 3, p(M),q(N).    

okay42(M, N) :- p(M), 2 <= #count{V : a(M),b(N),c(M,V)} <= 3, q(N).


:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4.    

:- 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, p(M),q(N).

:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, q(N).   



%:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4.    

%:- 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, p(M),q(N).

%:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, q(N).    

"""
output = """
%Non ground rules, constraints and weak constraints with the aggregate
%function count in the body. Guards for count are integer.
%All the functions count are satisfied.  

a(1).
b(1).
p(1).
q(1).
c(1,1).
c(1,2).

%----  #count{nonGroundAtoms} op int ----(at the end)

okay01(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} = 2.           
  
okay02(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} < 3.           
 
okay03(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} <= 2.          

okay04(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} > 1.           
    
okay05(M, N) :- p(M),q(N), #count{V : a(M),b(N),c(M,V)} >= 2.          

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} = 3.
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} = 3.           

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} < 2.           
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} < 2. 
   
:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} <= 1.          
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} <= 1.          

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} > 2.           
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} > 2. 

:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} >= 3.
%:- p(M),q(N), #count{V : a(M),b(N),c(M,V)} >= 3.

%----  #count{nonGroundAtoms} op int ----(at the beginning)

okay06(M, N) :- #count{V : a(M),b(N),c(M,V)} = 2, p(M),q(N).           

okay07(M, N) :- #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).           

okay08(M, N) :- #count{V : a(M),b(N),c(M,V)} <= 2, p(M),q(N).          

okay09(M, N) :- #count{V : a(M),b(N),c(M,V)} > 1, p(M),q(N).           

okay10(M, N) :- #count{V : a(M),b(N),c(M,V)} >= 2, p(M),q(N).    

:- #count{V : a(M),b(N),c(M,V)} = 3, p(M),q(N).  
%:- #count{V : a(M),b(N),c(M,V)} = 3, p(M),q(N).         

:- #count{V : a(M),b(N),c(M,V)} < 2, p(M),q(N).
%:- #count{V : a(M),b(N),c(M,V)} < 2, p(M),q(N).           

:- #count{V : a(M),b(N),c(M,V)} <= 1, p(M),q(N). 
%:- #count{V : a(M),b(N),c(M,V)} <= 1, p(M),q(N).          

:- #count{V : a(M),b(N),c(M,V)} > 2, p(M),q(N).  
%:- #count{V : a(M),b(N),c(M,V)} > 2, p(M),q(N).          

:- #count{V : a(M),b(N),c(M,V)} >= 3, p(M),q(N). 
%:- #count{V : a(M),b(N),c(M,V)} >= 3, p(M),q(N).     

%----  #count{nonGroundAtoms} op int ----(in the middle)

okay11(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} = 2, q(N).           

okay12(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} < 3, q(N).           

okay13(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} <= 2, q(N).          

okay14(M, N) :- p(M), #count{V : a(M),b(N),c(M,V)} > 1, q(N).           

okay15(M, N) :- p(M),#count{V : a(M),b(N),c(M,V)} >= 2, q(N).    

:- p(M), #count{V : a(M),b(N),c(M,V)} = 3, q(N).  
%:- p(M), #count{V : a(M),b(N),c(M,V)} = 3, q(N).         

:- p(M), #count{V : a(M),b(N),c(M,V)} < 2, q(N).
%:- p(M), #count{V : a(M),b(N),c(M,V)} < 2, q(N).           

:- p(M), #count{V : a(M),b(N),c(M,V)} <= 1, q(N). 
%:- p(M), #count{V : a(M),b(N),c(M,V)} <= 1, q(N).          

:- p(M), #count{V : a(M),b(N),c(M,V)} > 2, q(N).  
%:- p(M), #count{V : a(M),b(N),c(M,V)} > 2, q(N).          

:- p(M), #count{V : a(M),b(N),c(M,V)} >= 3, q(N). 
%:- p(M), #count{V : a(M),b(N),c(M,V)} >= 3, q(N).
 
%----  int op #count{nonGroundAtoms}----(at the end) 

okay16(M, N) :- p(M),q(N), 2 = #count{V : a(M),b(N),c(M,V)}.           

okay17(M, N) :- p(M),q(N), 1 < #count{V : a(M),b(N),c(M,V)}.           

okay18(M, N) :- p(M),q(N), 2 <= #count{V : a(M),b(N),c(M,V)}.           

okay19(M, N) :- p(M),q(N), 3  > #count{V : a(M),b(N),c(M,V)}.           

okay20(M, N) :- p(M),q(N), 2 >= #count{V : a(M),b(N),c(M,V)}.     

:- p(M),q(N), 1 = #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 1 = #count{V : a(M),b(N),c(M,V)}.  
 
:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)}.

:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)}.

:- p(M),q(N), 2 > #count{V : a(M),b(N),c(M,V)}.           
%:- p(M),q(N), 2 > #count{V : a(M),b(N),c(M,V)}.           

:- p(M),q(N), 1 >= #count{V : a(M),b(N),c(M,V)}.          
%:- p(M),q(N), 1 >= #count{V : a(M),b(N),c(M,V)}.          

%----  int op #count{nonGroundAtoms}---- (at the beginning)

okay21(M, N) :- 2 = #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          

okay22(M, N) :- 1 < #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

okay23(M, N) :- 2 <= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

okay24(M, N) :- 3 > #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          

okay25(M, N) :- 2 >= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

:- 1 = #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          
%:- 1 = #count{V : a(M),b(N),c(M,V)}, p(M),q(N).   

:- 2 < #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         
%:- 2 < #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

:- 3 <= #count{V : a(M),b(N),c(M,V)}, p(M),q(N). 
%:- 3 <= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).         

:- 2 > #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          
%:- 2 > #count{V : a(M),b(N),c(M,V)}, p(M),q(N).          

:- 1 >= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).     
%:- 1 >= #count{V : a(M),b(N),c(M,V)}, p(M),q(N).

    
%----  int op #count{nonGroundAtoms}---- (in the middle)

okay26(M, N) :- p(M), 2 = #count{V : a(M),b(N),c(M,V)}, q(N).          

okay27(M, N) :- p(M), 1 < #count{V : a(M),b(N),c(M,V)}, q(N).         

okay28(M, N) :- p(M), 2 <= #count{V : a(M),b(N),c(M,V)}, q(N).         

okay29(M, N) :- p(M), 3 > #count{V : a(M),b(N),c(M,V)}, q(N).          

okay30(M, N) :- p(M), 2 >= #count{V : a(M),b(N),c(M,V)}, q(N).         

:- p(M), 1 = #count{V : a(M),b(N),c(M,V)}, q(N).          
%:- p(M), 1 = #count{V : a(M),b(N),c(M,V)}, q(N).   

:- p(M), 2 < #count{V : a(M),b(N),c(M,V)}, q(N).         
%:- p(M), 2 < #count{V : a(M),b(N),c(M,V)}, q(N).         

:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)}, q(N). 
%:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)}, q(N).         

:- p(M), 2 > #count{V : a(M),b(N),c(M,V)}, q(N).          
%:- p(M), 2 > #count{V : a(M),b(N),c(M,V)}, q(N).          

:- p(M), 1 >= #count{V : a(M),b(N),c(M,V)}, q(N).     
%:- p(M), 1 >= #count{V : a(M),b(N),c(M,V)}, q(N).

%---- int < #count{nonGroundAtoms} < int ----


okay31(M,N) :- p(M),q(N), 1 < #count{V : a(M),b(N),c(M,V)} < 3.      

okay32(M,N) :- 1 < #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).

okay33(M,N) :- p(M), 1 < #count{V : a(M),b(N),c(M,V)} < 3, q(N).   


:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} < 3.      

:- 2 < #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).   
  
:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} < 3, q(N).


%:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} < 3.      

%:- 2 < #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).

%:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} < 3, q(N).     

%---- int < #count{} <= int ----


okay34(M, N) :- p(M),q(N), 1 < #count{V : a(M),b(N),c(M,V)} <= 2. 

okay35(M, N) :- 1 < #count{V : a(M),b(N),c(M,V)} <= 2, p(M),q(N). 

okay36(M, N) :- p(M), 1 < #count{V : a(M),b(N),c(M,V)} <= 2, q(N).


:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} <= 3.     

:- 2 < #count{V : a(M),b(N),c(M,V)} <= 3, p(M),q(N).

:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} <= 3, q(N).  


%:- p(M),q(N), 2 < #count{V : a(M),b(N),c(M,V)} <= 3.     

%:- 2 < #count{V : a(M),b(N),c(M,V)} <= 3, p(M),q(N).

%:- p(M), 2 < #count{V : a(M),b(N),c(M,V)} <= 3, q(N).

%---- int <= #count{nonGroundAtoms} < int ----

okay37(M, N) :- p(M),q(N), 2 <= #count{V : a(M),b(N),c(M,V)} < 3.     

okay38(M, N) :- 2 <= #count{V : a(M),b(N),c(M,V)} < 3, p(M),q(N).     

okay39(M, N) :- p(M), 2 <= #count{V : a(M),b(N),c(M,V)} < 3, q(N).


:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} < 4.     

:- 3 <= #count{V : a(M),b(N),c(M,V)} < 4, p(M),q(N).  

:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} < 4, q(N).


%:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} < 4.     

%:- 3 <= #count{V : a(M),b(N),c(M,V)} < 4, p(M),q(N).

%:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} < 4, q(N).
   
%---- int <= #count{nonGroundAtoms} <= int ----


okay40(M, N) :- p(M),q(N), 2 <= #count{V : a(M),b(N),c(M,V)} <= 3.    

okay41(M, N) :- 2 <= #count{V : a(M),b(N),c(M,V)} <= 3, p(M),q(N).    

okay42(M, N) :- p(M), 2 <= #count{V : a(M),b(N),c(M,V)} <= 3, q(N).


:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4.    

:- 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, p(M),q(N).

:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, q(N).   



%:- p(M),q(N), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4.    

%:- 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, p(M),q(N).

%:- p(M), 3 <= #count{V : a(M),b(N),c(M,V)} <= 4, q(N).    

"""
