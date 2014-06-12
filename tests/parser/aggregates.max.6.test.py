input = """
%Non ground rules, constraints and weak constraints with the aggregate
%function max in the body. Guards are non ground, too.

a(2).
a(3).
b(1).
c(3,1).
c(3,2).
c(2,1).
c(2,2).
p(2).
q(1).
v(3).
t(3).    

%----  #max{nonGroundAtoms} op var ----(at the end)

okay01(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} = M.           
  
okay02(M, N) :- p(M),t(N), #max{V:a(M),c(M,V)} < N.           
 
okay03(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} <= M.          

okay04(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} > N.           
    
okay05(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} >= M.          

:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} = N.
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} = N.           

:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} < N.           
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} < N. 
   
:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} <= N.          
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} <= N.          

:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} > M.           
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} > M. 

:- p(M),t(N), #max{V:a(M),b(N),c(V,M)} >= N.
%:- p(M),t(N), #max{V:a(M),b(N),c(V,M)} >= N.

%----  #max{nonGroundAtoms} op var ----(at the beginning)

okay06(M, N) :- #max{V:a(M),b(N),c(M,V)} = M, p(M),q(N).           

okay07(M, N) :- #max{V:a(M),c(M,V)} < N, p(M),t(N).           

okay08(M, N) :- #max{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).          

okay09(M, N) :- #max{V:a(M),b(N),c(M,V)} > N, p(M),q(N).           

okay10(M, N) :- #max{V:a(M),b(N),c(M,V)} >= N, p(M),q(N).    

:- #max{V:a(M),b(N),c(M,V)} = N, p(M),q(N).  
%:- #max{V:a(M),b(N),c(M,V)} = N, p(M),q(N).         

:- #max{V:a(M),b(N),c(M,V)} < N, p(M),q(N).
%:- #max{V:a(M),b(N),c(M,V)} < N, p(M),q(N).           

:- #max{V:a(M),b(N),c(M,V)} <= N, p(M),q(N). 
%:- #max{V:a(M),b(N),c(M,V)} <= N, p(M),q(N).          

:- #max{V:a(M),b(N),c(M,V)} > M, p(M),q(N).  
%:- #max{V:a(M),b(N),c(M,V)} > M, p(M),q(N).          

:- #max{V:a(M),b(N),c(V,M)} >= N, p(M),t(N). 
%:- #max{V:a(M),b(N),c(V,M)} >= N, p(M),t(N).     

%----  #max{nonGroundAtoms} op var ----(in the middle)

okay11(M, N) :- p(M), #max{V:a(M),b(N),c(M,V)} = M, q(N).           

okay12(M, N) :- p(M), #max{V:a(M),c(M,V)} < N, t(N).           

okay13(M, N) :- p(M), #max{V:a(M),b(N),c(M,V)} <= M, q(N).          

okay14(M, N) :- p(M), #max{V:a(M),b(N),c(M,V)} > N, q(N).           

okay15(M, N) :- p(M),#max{V:a(M),b(N),c(M,V)} >= N, q(N).    

:- p(M), #max{V:a(M),b(N),c(M,V)} = N, q(N).  
%:- p(M), #max{V:a(M),b(N),c(M,V)} = N, q(N).         

:- p(M), #max{V:a(M),b(N),c(M,V)} < N, q(N).
%:- p(M), #max{V:a(M),b(N),c(M,V)} < N, q(N).           

:- p(M), #max{V:a(M),b(N),c(M,V)} <= N, q(N). 
%:- p(M), #max{V:a(M),b(N),c(M,V)} <= N, q(N).          

:- p(M), #max{V:a(M),b(N),c(M,V)} > M, q(N).  
%:- p(M), #max{V:a(M),b(N),c(M,V)} > M, q(N).          

:- p(M), #max{V:a(M),b(N),c(V,M)} >= M, t(N). 
%:- p(M), #max{V:a(M),b(N),c(V,M)} >= M, t(N).
 
%----  var op #max{nonGroundAtoms}----(at the end) 

okay16(M, N) :- p(M),q(N), M = #max{V:a(M),b(N),c(M,V)}.           

okay17(M, N) :- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)}.           

okay18(M, N) :- p(M),q(N), M <= #max{V:a(M),b(N),c(M,V)}.           

okay19(M, N) :- p(M),t(N), N  > #max{V:a(M),c(M,V)}.           

okay20(M, N) :- p(M),q(N), M >= #max{V:a(M),b(N),c(M,V)}.     

:- p(M),q(N), N = #max{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N = #max{V:a(M),b(N),c(M,V)}.  
 
:- p(M),q(N), M < #max{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), M < #max{V:a(M),b(N),c(M,V)}.

:- p(M),t(N), M <= #max{V:a(M),b(N),c(V,M)}.           
%:- p(M),t(N), M <= #max{V:a(M),b(N),c(V,M)}.

:- p(M),q(N), N > #max{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N > #max{V:a(M),b(N),c(M,V)}.           

:- p(M),q(N), N >= #max{V:a(M),b(N),c(M,V)}.          
%:- p(M),q(N), N >= #max{V:a(M),b(N),c(M,V)}.          

%----  var op #max{nonGroundAtoms}---- (at the beginning)

okay21(M, N) :- M = #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          

okay22(M, N) :- N < #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay23(M, N) :- M <= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay24(M, N) :- N > #max{V:a(M),c(M,V)}, p(M),t(N).          

okay25(M, N) :- M >= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

:- N = #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N = #max{V:a(M),b(N),c(M,V)}, p(M),q(N).   

:- M < #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         
%:- M < #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

:- N <= #max{V:a(M),b(N),c(V,M)}, p(M),t(N). 
%:- N <= #max{V:a(M),b(N),c(V,M)}, p(M),t(N).         

:- N > #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N > #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          

:- N >= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).     
%:- N >= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).

    
%----  var op #max{nonGroundAtoms}---- (in the middle)

okay26(M, N) :- p(M), M = #max{V:a(M),b(N),c(M,V)}, q(N).          

okay27(M, N) :- p(M), N < #max{V:a(M),b(N),c(M,V)}, q(N).         

okay28(M, N) :- p(M), M <= #max{V:a(M),b(N),c(M,V)}, q(N).         

okay29(M, N) :- p(M), N > #max{V:a(M),c(M,V)}, t(N).          

okay30(M, N) :- p(M), M >= #max{V:a(M),b(N),c(M,V)}, q(N).         

:- p(M), N = #max{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N = #max{V:a(M),b(N),c(M,V)}, q(N).   

:- p(M), M < #max{V:a(M),b(N),c(M,V)}, q(N).         
%:- p(M), M < #max{V:a(M),b(N),c(M,V)}, q(N).         

:- p(M), N <= #max{V:a(M),b(N),c(V,M)}, t(N). 
%:- p(M), N <= #max{V:a(M),b(N),c(V,M)}, t(N).         

:- p(M), N >#max{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N >#max{V:a(M),b(N),c(M,V)}, q(N).          

:- p(M), N >= #max{V:a(M),b(N),c(M,V)}, q(N).     
%:- p(M), N >= #max{V:a(M),b(N),c(M,V)}, q(N).

%---- var < #max{nonGroundAtoms} < var ----


okay31(M,N) :- t(M),q(N), N < #max{V:a(M),b(N),c(M,V)} < M.    

okay32(M,N) :- N < #max{V:a(M),b(N),c(M,V)} < M, t(M),q(N).

okay33(M,N) :- t(M), N < #max{V:a(M),b(N),c(M,V)} < M, q(N).   


:- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)} < M.      

:- N < #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).   
  
:- p(M), N < #max{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)} < M.      

%:- N < #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N < #max{V:a(M),b(N),c(M,V)} < M, q(N).     

%---- var < #max{} <= var ----


okay34(M, N) :- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)} <= M.     

okay35(M, N) :- N < #max{V:a(M),b(N),c(M,V)} <= M, p(M),q(N). 

okay36(M, N) :- p(M), N < #max{V:a(M),b(N),c(M,V)} <= M, q(N).


:- p(M),q(N), N < #max{V:a(M),b(N),c(V,M)} <= M.     

:- N < #max{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

:- p(M), N < #max{V:a(M),b(N),c(V,M)} <= M, q(N).  


%:- p(M),q(N), N < #max{V:a(M),b(N),c(V,M)} <= M.     

%:- N < #max{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

%:- p(M), N < #max{V:a(M),b(N),c(V,M)} <= M, q(N).

%---- var <= #max{nonGroundAtoms} < var ----

okay37(M, N) :- t(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} < M.     

okay38(M, N) :- N <= #max{V:a(M),b(N),c(M,V)} < M, t(M),q(N).     

okay39(M, N) :- t(M), N <= #max{V:a(M),b(N),c(M,V)} < M, q(N).


:- p(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} < M.     

:- N <= #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).  

:- p(M), N <= #max{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} < M.     

%:- N <= #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N <= #max{V:a(M),b(N),c(M,V)} < M, q(N).
   
%---- var <= #max{nonGroundAtoms} <= var ----


okay40(M, N) :- p(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} <= M.    

okay41(M, N) :- M <= #max{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).    

okay42(M, N) :- p(M), M <= #max{V:a(M),b(N),c(M,V)} <= M, q(N).


:- v(M),t(N), M <= #max{V:a(M),b(N),c(M,V)} <= N.  

:- M <= #max{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

:- v(M), M <= #max{V:a(M),b(N),c(M,V)} <= N, t(N).   



%:- v(M),t(N), M <= #max{V:a(M),b(N),c(M,V)} <= N.    

%:- M <= #max{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

%:- v(M), M <= #max{V:a(M),b(N),c(M,V)} <= N, t(N).    




"""
output = """
%Non ground rules, constraints and weak constraints with the aggregate
%function max in the body. Guards are non ground, too.

a(2).
a(3).
b(1).
c(3,1).
c(3,2).
c(2,1).
c(2,2).
p(2).
q(1).
v(3).
t(3).    

%----  #max{nonGroundAtoms} op var ----(at the end)

okay01(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} = M.           
  
okay02(M, N) :- p(M),t(N), #max{V:a(M),c(M,V)} < N.           
 
okay03(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} <= M.          

okay04(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} > N.           
    
okay05(M, N) :- p(M),q(N), #max{V:a(M),b(N),c(M,V)} >= M.          

:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} = N.
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} = N.           

:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} < N.           
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} < N. 
   
:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} <= N.          
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} <= N.          

:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} > M.           
%:- p(M),q(N), #max{V:a(M),b(N),c(M,V)} > M. 

:- p(M),t(N), #max{V:a(M),b(N),c(V,M)} >= N.
%:- p(M),t(N), #max{V:a(M),b(N),c(V,M)} >= N.

%----  #max{nonGroundAtoms} op var ----(at the beginning)

okay06(M, N) :- #max{V:a(M),b(N),c(M,V)} = M, p(M),q(N).           

okay07(M, N) :- #max{V:a(M),c(M,V)} < N, p(M),t(N).           

okay08(M, N) :- #max{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).          

okay09(M, N) :- #max{V:a(M),b(N),c(M,V)} > N, p(M),q(N).           

okay10(M, N) :- #max{V:a(M),b(N),c(M,V)} >= N, p(M),q(N).    

:- #max{V:a(M),b(N),c(M,V)} = N, p(M),q(N).  
%:- #max{V:a(M),b(N),c(M,V)} = N, p(M),q(N).         

:- #max{V:a(M),b(N),c(M,V)} < N, p(M),q(N).
%:- #max{V:a(M),b(N),c(M,V)} < N, p(M),q(N).           

:- #max{V:a(M),b(N),c(M,V)} <= N, p(M),q(N). 
%:- #max{V:a(M),b(N),c(M,V)} <= N, p(M),q(N).          

:- #max{V:a(M),b(N),c(M,V)} > M, p(M),q(N).  
%:- #max{V:a(M),b(N),c(M,V)} > M, p(M),q(N).          

:- #max{V:a(M),b(N),c(V,M)} >= N, p(M),t(N). 
%:- #max{V:a(M),b(N),c(V,M)} >= N, p(M),t(N).     

%----  #max{nonGroundAtoms} op var ----(in the middle)

okay11(M, N) :- p(M), #max{V:a(M),b(N),c(M,V)} = M, q(N).           

okay12(M, N) :- p(M), #max{V:a(M),c(M,V)} < N, t(N).           

okay13(M, N) :- p(M), #max{V:a(M),b(N),c(M,V)} <= M, q(N).          

okay14(M, N) :- p(M), #max{V:a(M),b(N),c(M,V)} > N, q(N).           

okay15(M, N) :- p(M),#max{V:a(M),b(N),c(M,V)} >= N, q(N).    

:- p(M), #max{V:a(M),b(N),c(M,V)} = N, q(N).  
%:- p(M), #max{V:a(M),b(N),c(M,V)} = N, q(N).         

:- p(M), #max{V:a(M),b(N),c(M,V)} < N, q(N).
%:- p(M), #max{V:a(M),b(N),c(M,V)} < N, q(N).           

:- p(M), #max{V:a(M),b(N),c(M,V)} <= N, q(N). 
%:- p(M), #max{V:a(M),b(N),c(M,V)} <= N, q(N).          

:- p(M), #max{V:a(M),b(N),c(M,V)} > M, q(N).  
%:- p(M), #max{V:a(M),b(N),c(M,V)} > M, q(N).          

:- p(M), #max{V:a(M),b(N),c(V,M)} >= M, t(N). 
%:- p(M), #max{V:a(M),b(N),c(V,M)} >= M, t(N).
 
%----  var op #max{nonGroundAtoms}----(at the end) 

okay16(M, N) :- p(M),q(N), M = #max{V:a(M),b(N),c(M,V)}.           

okay17(M, N) :- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)}.           

okay18(M, N) :- p(M),q(N), M <= #max{V:a(M),b(N),c(M,V)}.           

okay19(M, N) :- p(M),t(N), N  > #max{V:a(M),c(M,V)}.           

okay20(M, N) :- p(M),q(N), M >= #max{V:a(M),b(N),c(M,V)}.     

:- p(M),q(N), N = #max{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N = #max{V:a(M),b(N),c(M,V)}.  
 
:- p(M),q(N), M < #max{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), M < #max{V:a(M),b(N),c(M,V)}.

:- p(M),t(N), M <= #max{V:a(M),b(N),c(V,M)}.           
%:- p(M),t(N), M <= #max{V:a(M),b(N),c(V,M)}.

:- p(M),q(N), N > #max{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N > #max{V:a(M),b(N),c(M,V)}.           

:- p(M),q(N), N >= #max{V:a(M),b(N),c(M,V)}.          
%:- p(M),q(N), N >= #max{V:a(M),b(N),c(M,V)}.          

%----  var op #max{nonGroundAtoms}---- (at the beginning)

okay21(M, N) :- M = #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          

okay22(M, N) :- N < #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay23(M, N) :- M <= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay24(M, N) :- N > #max{V:a(M),c(M,V)}, p(M),t(N).          

okay25(M, N) :- M >= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

:- N = #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N = #max{V:a(M),b(N),c(M,V)}, p(M),q(N).   

:- M < #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         
%:- M < #max{V:a(M),b(N),c(M,V)}, p(M),q(N).         

:- N <= #max{V:a(M),b(N),c(V,M)}, p(M),t(N). 
%:- N <= #max{V:a(M),b(N),c(V,M)}, p(M),t(N).         

:- N > #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N > #max{V:a(M),b(N),c(M,V)}, p(M),q(N).          

:- N >= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).     
%:- N >= #max{V:a(M),b(N),c(M,V)}, p(M),q(N).

    
%----  var op #max{nonGroundAtoms}---- (in the middle)

okay26(M, N) :- p(M), M = #max{V:a(M),b(N),c(M,V)}, q(N).          

okay27(M, N) :- p(M), N < #max{V:a(M),b(N),c(M,V)}, q(N).         

okay28(M, N) :- p(M), M <= #max{V:a(M),b(N),c(M,V)}, q(N).         

okay29(M, N) :- p(M), N > #max{V:a(M),c(M,V)}, t(N).          

okay30(M, N) :- p(M), M >= #max{V:a(M),b(N),c(M,V)}, q(N).         

:- p(M), N = #max{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N = #max{V:a(M),b(N),c(M,V)}, q(N).   

:- p(M), M < #max{V:a(M),b(N),c(M,V)}, q(N).         
%:- p(M), M < #max{V:a(M),b(N),c(M,V)}, q(N).         

:- p(M), N <= #max{V:a(M),b(N),c(V,M)}, t(N). 
%:- p(M), N <= #max{V:a(M),b(N),c(V,M)}, t(N).         

:- p(M), N >#max{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N >#max{V:a(M),b(N),c(M,V)}, q(N).          

:- p(M), N >= #max{V:a(M),b(N),c(M,V)}, q(N).     
%:- p(M), N >= #max{V:a(M),b(N),c(M,V)}, q(N).

%---- var < #max{nonGroundAtoms} < var ----


okay31(M,N) :- t(M),q(N), N < #max{V:a(M),b(N),c(M,V)} < M.    

okay32(M,N) :- N < #max{V:a(M),b(N),c(M,V)} < M, t(M),q(N).

okay33(M,N) :- t(M), N < #max{V:a(M),b(N),c(M,V)} < M, q(N).   


:- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)} < M.      

:- N < #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).   
  
:- p(M), N < #max{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)} < M.      

%:- N < #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N < #max{V:a(M),b(N),c(M,V)} < M, q(N).     

%---- var < #max{} <= var ----


okay34(M, N) :- p(M),q(N), N < #max{V:a(M),b(N),c(M,V)} <= M.     

okay35(M, N) :- N < #max{V:a(M),b(N),c(M,V)} <= M, p(M),q(N). 

okay36(M, N) :- p(M), N < #max{V:a(M),b(N),c(M,V)} <= M, q(N).


:- p(M),q(N), N < #max{V:a(M),b(N),c(V,M)} <= M.     

:- N < #max{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

:- p(M), N < #max{V:a(M),b(N),c(V,M)} <= M, q(N).  


%:- p(M),q(N), N < #max{V:a(M),b(N),c(V,M)} <= M.     

%:- N < #max{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

%:- p(M), N < #max{V:a(M),b(N),c(V,M)} <= M, q(N).

%---- var <= #max{nonGroundAtoms} < var ----

okay37(M, N) :- t(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} < M.     

okay38(M, N) :- N <= #max{V:a(M),b(N),c(M,V)} < M, t(M),q(N).     

okay39(M, N) :- t(M), N <= #max{V:a(M),b(N),c(M,V)} < M, q(N).


:- p(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} < M.     

:- N <= #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).  

:- p(M), N <= #max{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} < M.     

%:- N <= #max{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N <= #max{V:a(M),b(N),c(M,V)} < M, q(N).
   
%---- var <= #max{nonGroundAtoms} <= var ----


okay40(M, N) :- p(M),q(N), N <= #max{V:a(M),b(N),c(M,V)} <= M.    

okay41(M, N) :- M <= #max{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).    

okay42(M, N) :- p(M), M <= #max{V:a(M),b(N),c(M,V)} <= M, q(N).


:- v(M),t(N), M <= #max{V:a(M),b(N),c(M,V)} <= N.  

:- M <= #max{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

:- v(M), M <= #max{V:a(M),b(N),c(M,V)} <= N, t(N).   



%:- v(M),t(N), M <= #max{V:a(M),b(N),c(M,V)} <= N.    

%:- M <= #max{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

%:- v(M), M <= #max{V:a(M),b(N),c(M,V)} <= N, t(N).    




"""
