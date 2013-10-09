%
%
% Action Description Language
% move(x,y) causes on(x,y), ~clear(y) if clear(y)
holds(on(X,Y), T+1) :- holds(clear(Y), T), occurs(move(X,Y), T), time(T), block(X;Y).
nholds(clear(Y), T+1) :- holds(clear(Y), T), occurs(move(X,Y), T), time(T), block(X;Y).

% move(x,y) causes ~ontable(x), if ontable(x)
nholds(ontable(X), T+1) :- occurs(move(X, T), T), holds(ontable(X), T), block(X;Y), time(T).

% move(x,y) causes ~on(x,z), clear(z) if on(x,z).
nholds(on(X,Z), T+1) :- occurs(move(X, Y), T), holds(on(X,Z), T), block(X;Y;Z), time(T).
holds(clear(Z), T+1) :- occurs(move(X, Y), T), nholds(on(X, Z), T), block(X;Y;Z), time(T).

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

% execute move(x,y) if clear(y), clear(x)
executable(move(X,Y), T) :- holds(clear(Y), T), holds(clear(Y), T), time(T), block(X;Y).

% execute mtable(x) if clear(x), ~ontable(x)
executable(mtable(X), T) :- holds(clear(X), T), nholds(ontable(X), T), time(T), block(X).


% mtable(x) causes ontable(x) if ~ontable(x).
holds(ontable(X), T+1) :- occurs(mtable(X), T), nholds(ontable(X), T), time(T), block(X).

% mtable(x) causes clear(y) ~on(x,y) if on(x,y)
holds(clear(Y), T+1) :- occurs(mtable(X), T), holds(on(X,Y), T), block(X;Y), time(T).
nholds(on(X,Y), T+1) :- occurs(mtable(X), T), holds(on(X,Y), T), block(X;Y), time(T).

block(a;b;c;d).

fluent(ontable(X)) :- block(X).
fluent(on(X, Y)) :- block(X;Y).
fluent(clear(X)) :-  block(X).

action(move(X, Y)) :- block(X;Y).
action(mtable(X)) :-  block(X).

time(1..3).

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



% Initerial Actions (Frame Axioms)
holds(X, T+1) :- holds(X, T), fluent(X), time(T), not nholds(X, T+1).
nholds(X, T+1) :- nholds(X, T), fluent(X), time(T), not holds(X, T+1).

% Assume complete information
nholds(F, 0) :- fluent(F), not holds(F, 0).

:- occurs(A, T), not executable(A, T), action(A), time(T).
% Then the professor manually executes a time step
% occurs(move(c,d), 0).
% Add another step
% occurs(move(b,d), 1). % This causes unsatisfiable, because d is not clear.


% now that we've checked a few actions, we can move on to planning

1 { occurs(A,T) : action(A) } 1 :- time(T), T < 3.

%Goal 
finally(ontable(c)).
finally(ontable(a)).
finally(on(b,c)).
finally(on(d,a)).
finally(clear(b)).
finally(clear(d)).

:- finally(F), fluent(F), not holds(F, 3).

%
%
%:- not goal(100).
%


