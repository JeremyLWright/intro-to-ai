%
%
% Action Description Language
% move(x,y) causes on(x,y) if clear(x).
% move(x,y) causes ~clear(y)
% mtable(x) causes ontable(x) if clear(x).
%
% initially ontable(a).
% initially ~ontable(b).
% initially ~ontable(c).
% initially ontable(d).
% initially on(b,a)
% initially on(c,b)
% initially clear(c)
% initially clear(d)
% initially ~clear(b)
% initally ~clear(a)
%
% execute move(x,y) if clear(y).
% execute mtable(x) if not(ontable(x))
%

block(a;b;c;d).

fluent(ontable(X)) :- block(X).
fluent(on(X, Y)) :- block(X;Y).
fluent(clear(X)) :-  block(X).

action(move(X, Y)) :- block(X;Y).
action(mtable(X)) :-  block(X).

time(1..100).

%Initiallies
holds(ontable(a), 0).
nholds(ontable(b), 0).
nholds(ontable(c), 0).
holds(ontable(d), 0).

holds(on(b,a), 0).
holds(on(c,b), 0).

holds(clear(c), 0).
holds(clear(d), 0).
nholds(clear(b), 0).
nholds(clear(a), 0).

% Assume complete information
nholds(F, 0) :- fluent(F), not holds(F, 0).

% Actions
holds(on(X,Y), T+1) :- occurs(move(X,Y), T), holds(clear(X), T), time(T), block(X;Y).

nholds(clear(Y), T+1) :- occurs(move(X,Y), T), time(T), block(X;Y).

holds(ontable(X), T+1) :- occurs(mtable(X), T), holds(clear(X), T), time(T), block(X).


executable(move(X,Y), T) :- holds(clear(Y), T), time(T), block(X;Y).
executable(mtable(X), T) :- nholds(ontable(X), T), time(T), block(X).

:- action(A), time(T), occurs(A,T), not executable(A,T).

goal(T) :- holds(ontable(c), T), holds(ontable(a), T), holds(on(b, c), T), holds(on(d, a), T), time(T).

:- not goal(100).

1 { occurs(A,T) : action(A) } 1 :- time(T).


