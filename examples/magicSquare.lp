
%Generate a 9x9 magic square where ever row sums to the same value.

value(1..9).
num(1..3).
% cell(R, C, Value) reads as "cell (Row, Column) has the number Value"

%cell(R, C, Value) :- num(R), num(C), value(Value). <-- Wrong because doesnt generate all answer sets
% Generation
1 { cell(R, C, Value) : value(Value)} 1 :- num(R), num(C).

%Eliminations
%:- cell(R, R, Value) , num(R), value(Value).

%%Eliminte  number cannot occur twice in th same row or column
1 { cell(R, C, V) : num(R) : num(C) } 1 :- value(V).

% n*(n*n+1)/2
% Sum all rows
:- not 15 #sum[cell(R,C,Value) : value(Value) :  num(R) = Value ] 15 , num(C).
:- not 15 #sum[cell(R,C,Value) : value(Value) :  num(C) = Value ] 15 , num(R).

% Forward diagonal
:- not 15 #sum[cell(R,R, Value) : value(Value) :  num(R) = Value ] 15.

%Backward Diagnoncal
:- not 15 #sum[cell(R, 3-R+1, Value) : value(Value) :  num(R) = Value ] 15.

% Diagonal



