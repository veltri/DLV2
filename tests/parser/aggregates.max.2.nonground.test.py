input = """
a(1).
a(2).
a(3).
b(1).
b(2).
%c(1).
%c(2).
c(3).
c(4).
d.
e(1).
e(2).
e(3).
e(4).
e(5).
p(1,3).
%p(2,4).
%p(1,6).
%p(1,7).

%----  #max{...} op var ----(at the end)

okay1(M, N) :- p(M, N), #max{V : a(V)} = N.           
  
okay2(M, N) :- p(M, N), #max{V : b(V)} < N.           
 
okay3(M, N) :- p(M, N), #max{V : a(V)} <= N.          

okay4(M, N) :- p(M, N), #max{V : c(V)} > N.           
    
okay5(M, N) :- p(M, N), #max{V : a(V)} >= N.          

:- p(M, N), #max{V : a(V)} = M.           
%:- p(M, N), #max{V : a(V)} = M.           

:- p(M, N), #max{V : a(V)} < M.           
%:- p(M, N), #max{V : a(V)} < M. 
   
:- p(M, N), #max{V : a(V)} <= M.          
%:- p(M, N), #max{V : a(V)} <= M.          

:- p(M, N), #max{V : a(V)} > N.           
%:- p(M, N), #max{V : a(V)} > N. 

:- p(M, N), #max{V : b(V)} >= N.
%:- p(M, N), #max{V : b(V)} >= N.

%----  #max{...} op var ----(at the beginning)

okay6(M, N) :- #max{V : a(V)} = N, p(M, N).           

okay7(M, N) :- #max{V : b(V)} < N, p(M, N).           

okay8(M, N) :- #max{V : a(V)} <= N, p(M, N).          

okay9(M, N) :- #max{V : c(V)} > M, p(M, N).           

okay10(M, N) :- #max{V : a(V)} >= N, p(M, N).    

:- #max{V : b(V)} = N, p(M, N).  
%:- #max{V : b(V)} = N, p(M, N).         

:- #max{V : a(V)} < M, p(M, N).
%:- #max{V : a(V)} < M, p(M, N).           

:- #max{V : a(V)} <= M, p(M, N). 
%:- #max{V : a(V)} <= M, p(M, N).          

:- #max{V : a(V)} > N, p(M, N).  
%:- #max{V : a(V)} > N, p(M, N).          

:- #max{V : b(V)} >= N, p(M, N). 
%:- #max{V : b(V)} >= N, p(M, N).     
 
%----  var op #max{...}----(at the end) 


okay11(M, N) :- p(M, N), N = #max{V : a(V)}.           

okay12(M, N) :- p(M, N), M < #max{V : a(V)}.           

okay13(M, N) :- p(M, N), N <= #max{V : a(V)}.           

okay14(M, N) :- p(M, N), N  > #max{V : b(V)}.           

okay15(M, N) :- p(M, N), N >= #max{V : a(V)}.     


:- p(M, N), N = #max{V : b(V)}.           
%:- p(M, N), N = #max{V : b(V)}.  
 
:- p(M, N), N < #max{V : a(V)}.           
%:- p(M, N), N < #max{V : a(V)}.

:- p(M, N), N <= #max{V : b(V)}.           
%:- p(M, N), N <= #max{V : b(V)}.

:- p(M, N), M > #max{V : a(V)}.           
%:- p(M, N), M > #max{V : a(V)}.           

:- p(M, N), M >= #max{V : a(V)}.          
%:- p(M, N), M >= #max{V : a(V)}.          

%----  var op #max{...}---- (at the beginning)

okay16(M, N) :- N = #max{V : a(V)}, p(M, N).          

okay17(M, N) :- M < #max{V : a(V)}, p(M, N).         

okay18(M, N) :- N <= #max{V : a(V)}, p(M, N).         

okay19(M, N) :- N > #max{V : b(V)}, p(M, N).          

okay20(M, N) :- N >= #max{V : a(V)}, p(M, N).         

:- M = #max{V : a(V)}, p(M, N).          
%:- M = #max{V : a(V)}, p(M, N).   

:- N < #max{V : a(V)}, p(M, N).         
%:- N < #max{V : a(V)}, p(M, N).         

:- N <= #max{V : b(V)}, p(M, N). 
%:- N <= #max{V : b(V)}, p(M, N).         

:- M > #max{V : a(V)}, p(M, N).          
%:- M > #max{V : a(V)}, p(M, N).          

:- M >= #max{V : a(V)}, p(M, N).     
%:- M >= #max{V : a(V)}, p(M, N).     

%---- var < #max{...} < var ----


okay21(M, N) :- p(M, N), M < #max{V : b(V)} < N.      

okay22(M, N) :- M < #max{V : b(V)} < N, p(M, N). 
    


:- p(M, N), M < #max{V : a(V)} < N.      

:- M < #max{V : a(V), d} < N, p(M, N).   
  


%:- p(M, N), M < #max{V : a(V)} < N.      

%:- M < #max{V : a(V)} < N, p(M, N).     

%---- var < #max{...} <= var ----


okay23(M, N) :- p(M, N), M < #max{V : a(V)} <= N.     

okay24(M, N) :- M < #max{V : a(V)} <= N, p(M, N). 



:- p(M, N), M < #max{V : c(V)} <= N.     

:- M < #max{V : c(V)} <= N, p(M, N).


%:- p(M, N), M < #max{V : c(V)} <= N.     

%:- M < #max{V : c(V)} <= N, p(M, N).

%---- var <= #max{...} < var ----


okay25(M, N) :- p(M, N), M <= #max{V : b(V)} < N.     

okay26(M, N) :- M <= #max{V : b(V)} < N, p(M, N).     



:- p(M, N), M <= #max{V : c(V), d} < N.     

:- M <= #max{V : c(V), d} < N, p(M, N).  



%:- p(M, N), M <= #max{V : c(V), d} < N.     

%:- M <= #max{V : c(V), d} < N, p(M, N).  
   
%---- var <= #max{...} <= var ----


okay27(M, N) :- p(M, N), M <= #max{V : a(V)} <= N.    

okay28(M, N) :- M <= #max{V : a(V)} <= N, p(M, N).    



:- p(M, N), M <= #max{V : c(V)} <= N.    

:- M <= #max{V : c(V), d} <= N, p(M, N).    



%:- p(M, N), M <= #max{V : c(V), d} <= N.    

%:- M <= #max{V : c(V), d} <= N, p(M, N).
"""
output = """
a(1).
a(2).
a(3).
b(1).
b(2).
%c(1).
%c(2).
c(3).
c(4).
d.
e(1).
e(2).
e(3).
e(4).
e(5).
p(1,3).
%p(2,4).
%p(1,6).
%p(1,7).

%----  #max{...} op var ----(at the end)

okay1(M, N) :- p(M, N), #max{V : a(V)} = N.           
  
okay2(M, N) :- p(M, N), #max{V : b(V)} < N.           
 
okay3(M, N) :- p(M, N), #max{V : a(V)} <= N.          

okay4(M, N) :- p(M, N), #max{V : c(V)} > N.           
    
okay5(M, N) :- p(M, N), #max{V : a(V)} >= N.          

:- p(M, N), #max{V : a(V)} = M.           
%:- p(M, N), #max{V : a(V)} = M.           

:- p(M, N), #max{V : a(V)} < M.           
%:- p(M, N), #max{V : a(V)} < M. 
   
:- p(M, N), #max{V : a(V)} <= M.          
%:- p(M, N), #max{V : a(V)} <= M.          

:- p(M, N), #max{V : a(V)} > N.           
%:- p(M, N), #max{V : a(V)} > N. 

:- p(M, N), #max{V : b(V)} >= N.
%:- p(M, N), #max{V : b(V)} >= N.

%----  #max{...} op var ----(at the beginning)

okay6(M, N) :- #max{V : a(V)} = N, p(M, N).           

okay7(M, N) :- #max{V : b(V)} < N, p(M, N).           

okay8(M, N) :- #max{V : a(V)} <= N, p(M, N).          

okay9(M, N) :- #max{V : c(V)} > M, p(M, N).           

okay10(M, N) :- #max{V : a(V)} >= N, p(M, N).    

:- #max{V : b(V)} = N, p(M, N).  
%:- #max{V : b(V)} = N, p(M, N).         

:- #max{V : a(V)} < M, p(M, N).
%:- #max{V : a(V)} < M, p(M, N).           

:- #max{V : a(V)} <= M, p(M, N). 
%:- #max{V : a(V)} <= M, p(M, N).          

:- #max{V : a(V)} > N, p(M, N).  
%:- #max{V : a(V)} > N, p(M, N).          

:- #max{V : b(V)} >= N, p(M, N). 
%:- #max{V : b(V)} >= N, p(M, N).     
 
%----  var op #max{...}----(at the end) 


okay11(M, N) :- p(M, N), N = #max{V : a(V)}.           

okay12(M, N) :- p(M, N), M < #max{V : a(V)}.           

okay13(M, N) :- p(M, N), N <= #max{V : a(V)}.           

okay14(M, N) :- p(M, N), N  > #max{V : b(V)}.           

okay15(M, N) :- p(M, N), N >= #max{V : a(V)}.     


:- p(M, N), N = #max{V : b(V)}.           
%:- p(M, N), N = #max{V : b(V)}.  
 
:- p(M, N), N < #max{V : a(V)}.           
%:- p(M, N), N < #max{V : a(V)}.

:- p(M, N), N <= #max{V : b(V)}.           
%:- p(M, N), N <= #max{V : b(V)}.

:- p(M, N), M > #max{V : a(V)}.           
%:- p(M, N), M > #max{V : a(V)}.           

:- p(M, N), M >= #max{V : a(V)}.          
%:- p(M, N), M >= #max{V : a(V)}.          

%----  var op #max{...}---- (at the beginning)

okay16(M, N) :- N = #max{V : a(V)}, p(M, N).          

okay17(M, N) :- M < #max{V : a(V)}, p(M, N).         

okay18(M, N) :- N <= #max{V : a(V)}, p(M, N).         

okay19(M, N) :- N > #max{V : b(V)}, p(M, N).          

okay20(M, N) :- N >= #max{V : a(V)}, p(M, N).         

:- M = #max{V : a(V)}, p(M, N).          
%:- M = #max{V : a(V)}, p(M, N).   

:- N < #max{V : a(V)}, p(M, N).         
%:- N < #max{V : a(V)}, p(M, N).         

:- N <= #max{V : b(V)}, p(M, N). 
%:- N <= #max{V : b(V)}, p(M, N).         

:- M > #max{V : a(V)}, p(M, N).          
%:- M > #max{V : a(V)}, p(M, N).          

:- M >= #max{V : a(V)}, p(M, N).     
%:- M >= #max{V : a(V)}, p(M, N).     

%---- var < #max{...} < var ----


okay21(M, N) :- p(M, N), M < #max{V : b(V)} < N.      

okay22(M, N) :- M < #max{V : b(V)} < N, p(M, N). 
    


:- p(M, N), M < #max{V : a(V)} < N.      

:- M < #max{V : a(V), d} < N, p(M, N).   
  


%:- p(M, N), M < #max{V : a(V)} < N.      

%:- M < #max{V : a(V)} < N, p(M, N).     

%---- var < #max{...} <= var ----


okay23(M, N) :- p(M, N), M < #max{V : a(V)} <= N.     

okay24(M, N) :- M < #max{V : a(V)} <= N, p(M, N). 



:- p(M, N), M < #max{V : c(V)} <= N.     

:- M < #max{V : c(V)} <= N, p(M, N).


%:- p(M, N), M < #max{V : c(V)} <= N.     

%:- M < #max{V : c(V)} <= N, p(M, N).

%---- var <= #max{...} < var ----


okay25(M, N) :- p(M, N), M <= #max{V : b(V)} < N.     

okay26(M, N) :- M <= #max{V : b(V)} < N, p(M, N).     



:- p(M, N), M <= #max{V : c(V), d} < N.     

:- M <= #max{V : c(V), d} < N, p(M, N).  



%:- p(M, N), M <= #max{V : c(V), d} < N.     

%:- M <= #max{V : c(V), d} < N, p(M, N).  
   
%---- var <= #max{...} <= var ----


okay27(M, N) :- p(M, N), M <= #max{V : a(V)} <= N.    

okay28(M, N) :- M <= #max{V : a(V)} <= N, p(M, N).    



:- p(M, N), M <= #max{V : c(V)} <= N.    

:- M <= #max{V : c(V), d} <= N, p(M, N).    



%:- p(M, N), M <= #max{V : c(V), d} <= N.    

%:- M <= #max{V : c(V), d} <= N, p(M, N).
"""
