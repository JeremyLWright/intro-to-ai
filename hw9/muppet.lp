%Write the rules for enumerating the various possibilities to complete the Muppet World puzzle.
%1. Each row has exactly one item from element 1, one from element 2 and one from element 3.
%2. Each of the items in the various elements appear in exactly one row.
%
% ----------------------------------------------------------------------------------------
% Muppet world
% (From http://www.questionotd.com/2010/11/thinking-of-muppets-today.html)
% Three of the famous Muppets travel to their favorite amusement parks using either a bike, car, or bus. 
% From the given clues, tell which park each Muppet visited and what kind of transportation each used.
% Kermit the Frog went to Disneyland.
% The Muppet who went to Marine World used a bike.
% Miss Piggy went in a car.
% Fozzie Bear did not use a bus.
% Only one Muppet has been to Magic Mountain.

cindex(1..3).  %column index
rindex(1..3).  %row index
col(1,muppet).
col(2,vehicle).
col(3,park).

element(1,kermit). element(1, piggy). element(1,fozzie).
element(2,bike). element(2, bus). element(2,car).
element(3,disney). element(3,magic). element(3,marine).

% :- not went(kermit,disney).      % Kermit the Frog went to Disneyland.
:- rindex(I), rindex(J), row(I,kermit), row(J, disney), I!=J.

% :- muppet(X), went(X,marine), not travel(X,bike). %The Muppet who went to Marine World used a bike.
:- rindex(I), rindex(J), row(I,marine), row(J, bike), I!=J.

%:- not travel(piggy,car). %Miss Piggy went in a car.
:- rindex(I), rindex(J), row(I,piggy), row(J, car), I!=J.

%:- travel(fozzie,bus).  %Fozzie Bear did not use a bus.
:- rindex(I), row(I,fozzie), row(I, bus).

%  We have to enumerate the various possibilities about the rows.
row(R, E) :- rindex(R), cindex(C), element(C, E), not notrow(R, E). %Every row has an element, or doesn't have an element
notrow(R, E) :- rindex(R), cindex(C), element(C, E), not row(R, E).
%  Each row has exactly one item from element 1, one from element 2 and one from element 3.

1 { row(R, E) : rindex(R)} 1 :- element(1, E).
1 { row(R, E) : rindex(R)} 1 :- element(2, E).
1 { row(R, E) : rindex(R)} 1 :- element(3, E).


%1 { row(1, E) : element(1, E) : cindex(C) } 1 :- rindex(R). 
%1 { row(2, E) : element(C, E) : cindex(C) } 1 :- rindex(R). 
%1 { row(3, E) : element(C, E) : cindex(C) } 1 :- rindex(R). 
%1 { row(R, E) : rindex(R) : element(C,E) } 1 :- rindex(R) , cindex(C).
%  Each of the items in the various elements appear in exactly one row.
1 { element(C, E) : cindex(C)} 1 :- row(R, E).
%1 { element(C, E) : cindex(C)} 1 :- rindex(R),  element(C, E).
% Anchoring
row(1, kermit).
row(2, piggy).
row(3, fozzie).

#hide.
#show row/2.
