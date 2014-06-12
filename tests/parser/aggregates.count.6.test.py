input = """
%Non ground rules, constraints and weak constraints with the aggregate
%function count in the body. Guards for count are non ground, too.

a(2).
b(1).
c(1,2).
c(2,1).
c(2,2).
p(2).
q(1).
v(3).
t(4).


%----  #count{nonGroundAtoms} op var ----(at the end)

okay01(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} = M.           
  
okay02(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(V,M)} < M.           
 
okay03(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} <= M.          

okay04(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} > N.           
    
okay05(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} >= N.          

:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} = N.
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} = N.           

:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} < N.           
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} < N. 
   
:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} <= N.          
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} <= N.          

:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} > M.           
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} > M. 

%:- p(M),q(N), #count{V:a(M),b(N),c(V,M)} >= M.
%:- p(M),q(N), #count{V:a(M),b(N),c(V,M)} >= M.

%----  #count{nonGroundAtoms} op var ----(at the beginning)

okay06(M, N) :- #count{V:a(M),b(N),c(M,V)} = M, p(M),q(N).           

okay07(M, N) :- #count{V:a(M),b(N),c(V,M)} < M, p(M),q(N).           

okay08(M, N) :- #count{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).          

okay09(M, N) :- #count{V:a(M),b(N),c(M,V)} > N, p(M),q(N).           

okay10(M, N) :- #count{V:a(M),b(N),c(M,V)} >= N, p(M),q(N).    

:- #count{V:a(M),b(N),c(M,V)} = N, p(M),q(N).  
%:- #count{V:a(M),b(N),c(M,V)} = N, p(M),q(N).         

:- #count{V:a(M),b(N),c(M,V)} < N, p(M),q(N).
%:- #count{V:a(M),b(N),c(M,V)} < N, p(M),q(N).           

:- #count{V:a(M),b(N),c(M,V)} <= N, p(M),q(N). 
%:- #count{V:a(M),b(N),c(M,V)} <= N, p(M),q(N).          

:- #count{V:a(M),b(N),c(M,V)} > M, p(M),q(N).  
%:- #count{V:a(M),b(N),c(M,V)} > M, p(M),q(N).          

%:- #count{V:a(M),b(N),c(V,M)} >= M, p(M),q(N). 
%:- #count{V:a(M),b(N),c(V,M)} >= M, p(M),q(N).     

%----  #count{nonGroundAtoms} op var ----(in the middle)

okay11(M, N) :- p(M), #count{V:a(M),b(N),c(M,V)} = M, q(N).           

okay12(M, N) :- p(M), #count{V:a(M),b(N),c(V,M)} < M, q(N).           

okay13(M, N) :- p(M), #count{V:a(M),b(N),c(M,V)} <= M, q(N).          

okay14(M, N) :- p(M), #count{V:a(M),b(N),c(M,V)} > N, q(N).           

okay15(M, N) :- p(M),#count{V:a(M),b(N),c(M,V)} >= N, q(N).    

:- p(M), #count{V:a(M),b(N),c(M,V)} = N, q(N).  
%:- p(M), #count{V:a(M),b(N),c(M,V)} = N, q(N).         

:- p(M), #count{V:a(M),b(N),c(M,V)} < N, q(N).
%:- p(M), #count{V:a(M),b(N),c(M,V)} < N, q(N).           

:- p(M), #count{V:a(M),b(N),c(M,V)} <= N, q(N). 
%:- p(M), #count{V:a(M),b(N),c(M,V)} <= N, q(N).          

:- p(M), #count{V:a(M),b(N),c(M,V)} > M, q(N).  
%:- p(M), #count{V:a(M),b(N),c(M,V)} > M, q(N).          

%:- p(M), #count{V:a(M),b(N),c(V,M)} >= M, q(N). 
%:- p(M), #count{V:a(M),b(N),c(V,M)} >= M, q(N).
 
%----  var op #count{nonGroundAtoms}----(at the end) 

okay16(M, N) :- p(M),q(N), M = #count{V:a(M),b(N),c(M,V)}.           

okay17(M, N) :- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)}.           

okay18(M, N) :- p(M),q(N), M <= #count{V:a(M),b(N),c(M,V)}.           

okay19(M, N) :- p(M),q(N), M  > #count{V:a(M),b(N),c(V,M)}.           

okay20(M, N) :- p(M),q(N), M >= #count{V:a(M),b(N),c(M,V)}.     

:- p(M),q(N), N = #count{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N = #count{V:a(M),b(N),c(M,V)}.  
 
:- p(M),q(N), M < #count{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), M < #count{V:a(M),b(N),c(M,V)}.

%:- p(M),q(N), M <= #count{V:a(M),b(N),c(V,M)}.           
%:- p(M),q(N), M <= #count{V:a(M),b(N),c(V,M)}.

:- p(M),q(N), N > #count{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N > #count{V:a(M),b(N),c(M,V)}.           

:- p(M),q(N), N >= #count{V:a(M),b(N),c(M,V)}.          
%:- p(M),q(N), N >= #count{V:a(M),b(N),c(M,V)}.          

%----  var op #count{nonGroundAtoms}---- (at the beginning)

okay21(M, N) :- M = #count{V:a(M),b(N),c(M,V)}, p(M),q(N).          

okay22(M, N) :- N < #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay23(M, N) :- M <= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay24(M, N) :- M > #count{V:a(M),b(N),c(V,M)}, p(M),q(N).          

okay25(M, N) :- M >= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

:- N = #count{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N = #count{V:a(M),b(N),c(M,V)}, p(M),q(N).   

:- M < #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         
%:- M < #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

%:- M <= #count{V:a(M),b(N),c(V,M)}, p(M),q(N). 
%:- M <= #count{V:a(M),b(N),c(V,M)}, p(M),q(N).         

:- N >#count{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N >#count{V:a(M),b(N),c(M,V)}, p(M),q(N).          

:- N >= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).     
%:- N >= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).

    
%----  var op #count{nonGroundAtoms}---- (in the middle)

okay26(M, N) :- p(M), M = #count{V:a(M),b(N),c(M,V)}, q(N).          

okay27(M, N) :- p(M), N < #count{V:a(M),b(N),c(M,V)}, q(N).         

okay28(M, N) :- p(M), M <= #count{V:a(M),b(N),c(M,V)}, q(N).         

okay29(M, N) :- p(M), M > #count{V:a(M),b(N),c(V,M)}, q(N).          

okay30(M, N) :- p(M), M >= #count{V:a(M),b(N),c(M,V)}, q(N).         

:- p(M), N = #count{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N = #count{V:a(M),b(N),c(M,V)}, q(N).   

:- p(M), M < #count{V:a(M),b(N),c(M,V)}, q(N).         
%:- p(M), M < #count{V:a(M),b(N),c(M,V)}, q(N).         

%:- p(M), M <= #count{V:a(M),b(N),c(V,M)}, q(N). 
%:- p(M), M <= #count{V:a(M),b(N),c(V,M)}, q(N).         

:- p(M), N >#count{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N >#count{V:a(M),b(N),c(M,V)}, q(N).          

:- p(M), N >= #count{V:a(M),b(N),c(M,V)}, q(N).     
%:- p(M), N >= #count{V:a(M),b(N),c(M,V)}, q(N).

%---- var < #count{nonGroundAtoms} < var ----


okay31(M,N) :- v(M),q(N), N < #count{V:a(M),b(N),c(M,V)} < M.    

okay32(M,N) :- N < #count{V:a(M),b(N),c(M,V)} < M, v(M),q(N).

okay33(M,N) :- v(M), N < #count{V:a(M),b(N),c(M,V)} < M, q(N).   


:- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)} < M.      

:- N < #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).   
  
:- p(M), N < #count{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)} < M.      

%:- N < #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N < #count{V:a(M),b(N),c(M,V)} < M, q(N).     

%---- var < #count{} <= var ----


okay34(M, N) :- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)} <= M.     

okay35(M, N) :- N < #count{V:a(M),b(N),c(M,V)} <= M, p(M),q(N). 

okay36(M, N) :- p(M), N < #count{V:a(M),b(N),c(M,V)} <= M, q(N).


%:- p(M),q(N), N < #count{V:a(M),b(N),c(V,M)} <= M.     

%:- N < #count{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

%:- p(M), N < #count{V:a(M),b(N),c(V,M)} <= M, q(N).  


%:- p(M),q(N), N < #count{V:a(M),b(N),c(V,M)} <= M.     

%:- N < #count{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

%:- p(M), N < #count{V:a(M),b(N),c(V,M)} <= M, q(N).

%---- var <= #count{nonGroundAtoms} < var ----

okay37(M, N) :- p(M),q(N), N <= #count{V:a(M),b(N),c(V,M)} < M.     

okay38(M, N) :- N <= #count{V:a(M),b(N),c(V,M)} < M, p(M),q(N).     

okay39(M, N) :- p(M), N <= #count{V:a(M),b(N),c(V,M)} < M, q(N).


:- p(M),q(N), N <= #count{V:a(M),b(N),c(M,V)} < M.     

:- N <= #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).  

:- p(M), N <= #count{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N <= #count{V:a(M),b(N),c(M,V)} < M.     

%:- N <= #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N <= #count{V:a(M),b(N),c(M,V)} < M, q(N).
   
%---- var <= #count{nonGroundAtoms} <= var ----


okay40(M, N) :- p(M),q(N), N <= #count{V:a(M),b(N),c(M,V)} <= M.    

okay41(M, N) :- M <= #count{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).    

okay42(M, N) :- p(M), M <= #count{V:a(M),b(N),c(M,V)} <= M, q(N).


:- v(M),t(N), M <= #count{V:a(M),b(N),c(M,V)} <= N.  

:- M <= #count{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

:- v(M), M <= #count{V:a(M),b(N),c(M,V)} <= N, t(N).   



%:- v(M),t(N), M <= #count{V:a(M),b(N),c(M,V)} <= N.    

%:- M <= #count{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

%:- v(M), M <= #count{V:a(M),b(N),c(M,V)} <= N, t(N).    




"""
output = """
%Non ground rules, constraints and weak constraints with the aggregate
%function count in the body. Guards for count are non ground, too.

a(2).
b(1).
c(1,2).
c(2,1).
c(2,2).
p(2).
q(1).
v(3).
t(4).


%----  #count{nonGroundAtoms} op var ----(at the end)

okay01(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} = M.           
  
okay02(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(V,M)} < M.           
 
okay03(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} <= M.          

okay04(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} > N.           
    
okay05(M, N) :- p(M),q(N), #count{V:a(M),b(N),c(M,V)} >= N.          

:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} = N.
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} = N.           

:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} < N.           
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} < N. 
   
:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} <= N.          
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} <= N.          

:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} > M.           
%:- p(M),q(N), #count{V:a(M),b(N),c(M,V)} > M. 

%:- p(M),q(N), #count{V:a(M),b(N),c(V,M)} >= M.
%:- p(M),q(N), #count{V:a(M),b(N),c(V,M)} >= M.

%----  #count{nonGroundAtoms} op var ----(at the beginning)

okay06(M, N) :- #count{V:a(M),b(N),c(M,V)} = M, p(M),q(N).           

okay07(M, N) :- #count{V:a(M),b(N),c(V,M)} < M, p(M),q(N).           

okay08(M, N) :- #count{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).          

okay09(M, N) :- #count{V:a(M),b(N),c(M,V)} > N, p(M),q(N).           

okay10(M, N) :- #count{V:a(M),b(N),c(M,V)} >= N, p(M),q(N).    

:- #count{V:a(M),b(N),c(M,V)} = N, p(M),q(N).  
%:- #count{V:a(M),b(N),c(M,V)} = N, p(M),q(N).         

:- #count{V:a(M),b(N),c(M,V)} < N, p(M),q(N).
%:- #count{V:a(M),b(N),c(M,V)} < N, p(M),q(N).           

:- #count{V:a(M),b(N),c(M,V)} <= N, p(M),q(N). 
%:- #count{V:a(M),b(N),c(M,V)} <= N, p(M),q(N).          

:- #count{V:a(M),b(N),c(M,V)} > M, p(M),q(N).  
%:- #count{V:a(M),b(N),c(M,V)} > M, p(M),q(N).          

%:- #count{V:a(M),b(N),c(V,M)} >= M, p(M),q(N). 
%:- #count{V:a(M),b(N),c(V,M)} >= M, p(M),q(N).     

%----  #count{nonGroundAtoms} op var ----(in the middle)

okay11(M, N) :- p(M), #count{V:a(M),b(N),c(M,V)} = M, q(N).           

okay12(M, N) :- p(M), #count{V:a(M),b(N),c(V,M)} < M, q(N).           

okay13(M, N) :- p(M), #count{V:a(M),b(N),c(M,V)} <= M, q(N).          

okay14(M, N) :- p(M), #count{V:a(M),b(N),c(M,V)} > N, q(N).           

okay15(M, N) :- p(M),#count{V:a(M),b(N),c(M,V)} >= N, q(N).    

:- p(M), #count{V:a(M),b(N),c(M,V)} = N, q(N).  
%:- p(M), #count{V:a(M),b(N),c(M,V)} = N, q(N).         

:- p(M), #count{V:a(M),b(N),c(M,V)} < N, q(N).
%:- p(M), #count{V:a(M),b(N),c(M,V)} < N, q(N).           

:- p(M), #count{V:a(M),b(N),c(M,V)} <= N, q(N). 
%:- p(M), #count{V:a(M),b(N),c(M,V)} <= N, q(N).          

:- p(M), #count{V:a(M),b(N),c(M,V)} > M, q(N).  
%:- p(M), #count{V:a(M),b(N),c(M,V)} > M, q(N).          

%:- p(M), #count{V:a(M),b(N),c(V,M)} >= M, q(N). 
%:- p(M), #count{V:a(M),b(N),c(V,M)} >= M, q(N).
 
%----  var op #count{nonGroundAtoms}----(at the end) 

okay16(M, N) :- p(M),q(N), M = #count{V:a(M),b(N),c(M,V)}.           

okay17(M, N) :- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)}.           

okay18(M, N) :- p(M),q(N), M <= #count{V:a(M),b(N),c(M,V)}.           

okay19(M, N) :- p(M),q(N), M  > #count{V:a(M),b(N),c(V,M)}.           

okay20(M, N) :- p(M),q(N), M >= #count{V:a(M),b(N),c(M,V)}.     

:- p(M),q(N), N = #count{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N = #count{V:a(M),b(N),c(M,V)}.  
 
:- p(M),q(N), M < #count{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), M < #count{V:a(M),b(N),c(M,V)}.

%:- p(M),q(N), M <= #count{V:a(M),b(N),c(V,M)}.           
%:- p(M),q(N), M <= #count{V:a(M),b(N),c(V,M)}.

:- p(M),q(N), N > #count{V:a(M),b(N),c(M,V)}.           
%:- p(M),q(N), N > #count{V:a(M),b(N),c(M,V)}.           

:- p(M),q(N), N >= #count{V:a(M),b(N),c(M,V)}.          
%:- p(M),q(N), N >= #count{V:a(M),b(N),c(M,V)}.          

%----  var op #count{nonGroundAtoms}---- (at the beginning)

okay21(M, N) :- M = #count{V:a(M),b(N),c(M,V)}, p(M),q(N).          

okay22(M, N) :- N < #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay23(M, N) :- M <= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

okay24(M, N) :- M > #count{V:a(M),b(N),c(V,M)}, p(M),q(N).          

okay25(M, N) :- M >= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

:- N = #count{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N = #count{V:a(M),b(N),c(M,V)}, p(M),q(N).   

:- M < #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         
%:- M < #count{V:a(M),b(N),c(M,V)}, p(M),q(N).         

%:- M <= #count{V:a(M),b(N),c(V,M)}, p(M),q(N). 
%:- M <= #count{V:a(M),b(N),c(V,M)}, p(M),q(N).         

:- N >#count{V:a(M),b(N),c(M,V)}, p(M),q(N).          
%:- N >#count{V:a(M),b(N),c(M,V)}, p(M),q(N).          

:- N >= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).     
%:- N >= #count{V:a(M),b(N),c(M,V)}, p(M),q(N).

    
%----  var op #count{nonGroundAtoms}---- (in the middle)

okay26(M, N) :- p(M), M = #count{V:a(M),b(N),c(M,V)}, q(N).          

okay27(M, N) :- p(M), N < #count{V:a(M),b(N),c(M,V)}, q(N).         

okay28(M, N) :- p(M), M <= #count{V:a(M),b(N),c(M,V)}, q(N).         

okay29(M, N) :- p(M), M > #count{V:a(M),b(N),c(V,M)}, q(N).          

okay30(M, N) :- p(M), M >= #count{V:a(M),b(N),c(M,V)}, q(N).         

:- p(M), N = #count{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N = #count{V:a(M),b(N),c(M,V)}, q(N).   

:- p(M), M < #count{V:a(M),b(N),c(M,V)}, q(N).         
%:- p(M), M < #count{V:a(M),b(N),c(M,V)}, q(N).         

%:- p(M), M <= #count{V:a(M),b(N),c(V,M)}, q(N). 
%:- p(M), M <= #count{V:a(M),b(N),c(V,M)}, q(N).         

:- p(M), N >#count{V:a(M),b(N),c(M,V)}, q(N).          
%:- p(M), N >#count{V:a(M),b(N),c(M,V)}, q(N).          

:- p(M), N >= #count{V:a(M),b(N),c(M,V)}, q(N).     
%:- p(M), N >= #count{V:a(M),b(N),c(M,V)}, q(N).

%---- var < #count{nonGroundAtoms} < var ----


okay31(M,N) :- v(M),q(N), N < #count{V:a(M),b(N),c(M,V)} < M.    

okay32(M,N) :- N < #count{V:a(M),b(N),c(M,V)} < M, v(M),q(N).

okay33(M,N) :- v(M), N < #count{V:a(M),b(N),c(M,V)} < M, q(N).   


:- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)} < M.      

:- N < #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).   
  
:- p(M), N < #count{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)} < M.      

%:- N < #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N < #count{V:a(M),b(N),c(M,V)} < M, q(N).     

%---- var < #count{} <= var ----


okay34(M, N) :- p(M),q(N), N < #count{V:a(M),b(N),c(M,V)} <= M.     

okay35(M, N) :- N < #count{V:a(M),b(N),c(M,V)} <= M, p(M),q(N). 

okay36(M, N) :- p(M), N < #count{V:a(M),b(N),c(M,V)} <= M, q(N).


%:- p(M),q(N), N < #count{V:a(M),b(N),c(V,M)} <= M.     

%:- N < #count{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

%:- p(M), N < #count{V:a(M),b(N),c(V,M)} <= M, q(N).  


%:- p(M),q(N), N < #count{V:a(M),b(N),c(V,M)} <= M.     

%:- N < #count{V:a(M),b(N),c(V,M)} <= M, p(M),q(N).

%:- p(M), N < #count{V:a(M),b(N),c(V,M)} <= M, q(N).

%---- var <= #count{nonGroundAtoms} < var ----

okay37(M, N) :- p(M),q(N), N <= #count{V:a(M),b(N),c(V,M)} < M.     

okay38(M, N) :- N <= #count{V:a(M),b(N),c(V,M)} < M, p(M),q(N).     

okay39(M, N) :- p(M), N <= #count{V:a(M),b(N),c(V,M)} < M, q(N).


:- p(M),q(N), N <= #count{V:a(M),b(N),c(M,V)} < M.     

:- N <= #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).  

:- p(M), N <= #count{V:a(M),b(N),c(M,V)} < M, q(N).


%:- p(M),q(N), N <= #count{V:a(M),b(N),c(M,V)} < M.     

%:- N <= #count{V:a(M),b(N),c(M,V)} < M, p(M),q(N).

%:- p(M), N <= #count{V:a(M),b(N),c(M,V)} < M, q(N).
   
%---- var <= #count{nonGroundAtoms} <= var ----


okay40(M, N) :- p(M),q(N), N <= #count{V:a(M),b(N),c(M,V)} <= M.    

okay41(M, N) :- M <= #count{V:a(M),b(N),c(M,V)} <= M, p(M),q(N).    

okay42(M, N) :- p(M), M <= #count{V:a(M),b(N),c(M,V)} <= M, q(N).


:- v(M),t(N), M <= #count{V:a(M),b(N),c(M,V)} <= N.  

:- M <= #count{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

:- v(M), M <= #count{V:a(M),b(N),c(M,V)} <= N, t(N).   



%:- v(M),t(N), M <= #count{V:a(M),b(N),c(M,V)} <= N.    

%:- M <= #count{V:a(M),b(N),c(M,V)} <= N, v(M),t(N).

%:- v(M), M <= #count{V:a(M),b(N),c(M,V)} <= N, t(N).    




"""
