%
% domains
%
number(1..9).
index(1..9).
cubes(1;4;7).

% At every location does or does not have a number in it.
x(X, Y, N) :- index(X;Y), number(N), not nx(X,Y, N).
nx(X, Y, N) :- index(X;Y), number(N), not x(X,Y, N).

%% At every location does or does not have a 2 in it.
%x(X, Y, 2) :- index(X;Y), not nx(X,Y, 2).
%nx(X, Y, 2) :- index(X;Y), not x(X,Y, 2).
%
%% At every location does or does not have a 3 in it.
%x(X, Y, 3) :- index(X;Y), not nx(X,Y, 3).
%nx(X, Y, 3) :- index(X;Y), not x(X,Y, 3).
%
%% At every location does or does not have a 4 in it.
%x(X, Y, 4) :- index(X;Y), not nx(X,Y, 4).
%nx(X, Y, 4) :- index(X;Y), not x(X,Y, 4).
%
%% At every location does or does not have a 5 in it.
%x(X, Y, 5) :- index(X;Y), not nx(X,Y, 5).
%nx(X, Y, 5) :- index(X;Y), not x(X,Y, 5).
%
%% At every location does or does not have a 6 in it.
%x(X, Y, 6) :- index(X;Y), not nx(X,Y, 6).
%nx(X, Y, 6) :- index(X;Y), not x(X,Y, 6).
%
%% At every location does or does not have a 7 in it.
%x(X, Y, 7) :- index(X;Y), not nx(X,Y, 7).
%nx(X, Y, 7) :- index(X;Y), not x(X,Y, 7).
%
%% At every location does or does not have a 8 in it.
%x(X, Y, 8) :- index(X;Y), not nx(X,Y, 8).
%nx(X, Y, 8) :- index(X;Y), not x(X,Y, 8).
%
%% At every location does or does not have a 9 in it.
%x(X, Y, 9) :- index(X;Y), not nx(X,Y, 9).
%nx(X, Y, 9) :- index(X;Y), not x(X,Y, 9).


% alldifferent boxes
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
%#hide.
%#show x/3.
