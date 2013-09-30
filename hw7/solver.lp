number(1..9).
index(1..9).
squares(1;4;7).

% At every location does or does not have a number in it.
x(X, Y, N) :- index(X;Y), number(N), not nx(X,Y, N).
nx(X, Y, N) :- index(X;Y), number(N), not x(X,Y, N).


% No row has the same number
:- x(X, Y1, N), x(X,Y2, N), index(X;Y1;Y2), number(N), Y1!=Y2.

%No column has the same number
:- x(X1, Y, N), x(X2,Y, N), index(X1;X2;Y), number(N), X1!=X2.

%Every square must have only 1 number
:- x(X, Y, N1), x(X, Y, N2), index(X;Y), number(N1;N2), N1 != N2.

%No cube has the same number
%% First Cube index 1 - 3
:- x(C, C, N), x(X2, Y2, N), number(N), squares(C), X2 >= C, X2 <= C+2, Y2 >= C, Y2 <= C+2. 

#hide.
#show x/3.
