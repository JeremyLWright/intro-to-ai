% Graph
%  |--<(3) <------ 2 ---------> (5) >|
%  |    ^ <_                 />  ^  |
%  |    |   \_3_         _1_/    |  |
%  |    |       \__     /        2  |
%  |    3          (6)</         |  |
%  |    |              <\__     |   |
%  |    |                  4_   |   2
%  2    v                    >  |   |
%  |   (1) <------ 2 -------> (2)   |
%  |   ^                       ^    |
%  |   |                       |    |
%  |   1                       2    |
%  |   |---------->4<----------|    |
%  |               ^                |
%  |---------------|----------------|
%

% Encode the costs: cost(From, To, Weight)
cost(1, 2, 2). cost(1, 3, 2). cost(1, 4, 1).
cost(2, 4, 2). cost(2, 5, 2). cost(2, 6, 1).
cost(3, 1, 3). cost(3, 4, 2). cost(3, 5, 2).
cost(4, 1, 1). cost(4, 2, 2).
cost(5, 3, 2). cost(5, 4, 2). cost(5, 6, 1).
cost(6, 2, 4). cost(6, 3, 3). cost(6, 5, 1).

% Generate
1 { cycle(X, Y) : edge(X,Y) } 1 :- node(X).
1 { cycle(X, Y) : edge(X,Y) } 1 :- node(Y).

% Define
reached(Y) :- cycle(1,Y).
reached(Y) :- cycle(X,Y), reached(X).

:- node(Y), not reached(Y).

