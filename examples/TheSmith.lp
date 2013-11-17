%Problem #1: Mr Smith Family
%the Smith family and their three children want to pay a visit but they do not
%all have the time to do so. Following are few hints who will go and who will not.


person(mr_smith; mrs_smith; matt; john; tim).

% Generation
0 { go(X) : person(X) } 5.


%Eliminations

% - If Mr. Smith comes, his wife will come too.
:- go(mr_smith), not go(mrs_smith).

% - At least one of their two sons Matt, or john will come.
:- not go(matt), not go(john).

% - Either Mts Smith or Time will come, but not both.
:- go(mrs_smith), go(tim).
:- not go(mrs_smith), not go(tim). % Not possible that neither go

% - Either Time or John will come, or neither will come.
:- not go(tim), go(john).
:- go(tim),not go(tim).

% - If matt comes, then John and his father will also come.
:- go(matt), not go(john).
:- go(matt), not go(mr_smith).

#hide.
#show go(X).
