%
% domains
%
number(1..9).
index(1..9).
cubes(1;4;7).

% At every location does or does not have a number in it.
x(X, Y, N) :- index(X;Y), number(N), not nx(X,Y, N).
nx(X, Y, N) :- index(X;Y), number(N), not x(X,Y, N).


% No row has the same number
:- x(X, Y1, N), x(X,Y2, N), index(X;Y1;Y2), number(N), Y1!=Y2.
:- x(X1, Y, N), x(X2,Y, N), index(X1;X2;Y), number(N), X1!=X2.
%:- x(X, Y1, N1), x(X,Y2, N2), index(Y1;Y2;X), N1!=N2, Y1!=Y2.

%1 { x(X,Y,N) : 
%    number(X;Y):
%    CubeX <= X:
%    X <= CubeX+2:
%    CubeY <= Y:
%    Y<=CubeY+2 } 1 :- number(N), cubes(CubeX;CubeY).
%
%1 { x(X,Y,N) : 
%    number(X;Y):
%    CubeX<=X:X<=CubeX+2:
%    CubeY<=Y:Y<=CubeY+2 } 1 :- number(N), cubes(CubeX;CubeY).
%1 { x(X,Y,N) : 
%    number(X;Y):
%    CubeX<=X:X<=CubeX+2:
%    CubeY<=Y:Y<=CubeY+2 } 1 :- number(N), cubes(CubeX;CubeY).
%
%% alldifferent rows, columns, values
%1 { x(X,Y,N) : number(N) } 1 :- number(X;Y).
%1 { x(X,Y,N) : number(X) } 1 :- number(N;Y).
%1 { x(X,Y,N) : number(Y) } 1 :- number(N;X). 
%
%% alternative:
%% :- 2 { x(X,Y,N) : number(N) }, number(X;Y).
%% :- 2 { x(X,Y,N) : number(X) }, number(N;Y).
%% :- 2 { x(X,Y,N) : number(Y) }, number(N;X). 
%
#hide.
#show x/3.
