% Homework #2 - CSE 471/CSE598
% Jeremy Wright
% I referenced the following sites while working on this assignment:
%  - http://www.youtube.com/watch?v=n2Wz9oKpZjs
%  - http://www.hakank.org/asp/
%  - http://potassco.sourceforge.net/labs.html
%  - http://peace.eas.asu.edu/aaai12tutorial/asp-tutorial-aaai.pdf
%  - https://www.csupomona.edu/~jrfisher/www/prolog_tutorial/contents.html
%  - http://www.csci.csusb.edu/dick/samples/prolog.html
%
% Snow Motion
%
% 
% Most winters, you’ll find the majority of Townsville over Harrier Hill,
% enjoying the snowfall. From the early morning until just after dusk, people
% sled down the snowy slope, laughing and cheering all the while. Yesterday
% morning, seven young people (including Xerxes) were the first down the
% slope, riding five vehicles (a luge, a plastic sled, a toboggan, and two
% inner tubes). Some vehicles contained only one person, while others held
% two-riders. The seven enjoyed their brief time alone on Harrier Hill, but it
% wasn’t long before a blizzard of other sledders joined them! From the
% information provided, determine the order in which each vehicle sledded down
% the snowy slope and the rider or riders who sat in each vehicle.
%
% 1.	Each of the two inner tubes (one of which was the first down the slope) had only one rider.
% 2.	The toboggan (which has two riders) was the second vehicle down the slope.
% 3.	Vanessa rode the plastic sled down the slope at some point after, but not immediately after, the luge went down
% 4.	Kira and Ollie (who rode on the same vehicle) slipped down the slope immediately before Regan.
% 5.	Blake and Flynn rode the same vehicle and it was not an inner tube.
% 
% 
% Result:
% 1st, inner tube 1, Xerxes
% 2nd, toboggan, Blake and Flynn
% 3rd, luge, Kira and Ollie
% 4th, inner tube 2, Regan
% 5th, plastic sled, Vanessa
% 
sleds(innerTube1;toboggan;luge;innerTube2;plasticSled).
persons(xerxes;blake_and_Flynn;vanessa;kira_and_Ollie;regan).

order(1..5).
% Generate
%
1 { went(Sled, T) : order(T) } 1 :- sleds(Sled).
1 { went(Sled, T) : sleds(Sled)} 1 :- order(T).

1 { sled(P, T) : order(T) } 1 :- persons(P).
1 { sled(P, T) : persons(P)} 1 :- order(T).

% story paragraph
% Xerxes went first
sled(xerxes, 1).

% #1
% innerTube1 was the first went first
went(innerTube1, 1).

% #2
% The toboggan went second.
went(toboggan, 2).

% #3
% vanessa sled on the plastic sled at some time T2
% the luge went down some time T1 
% where T1 is before T2, but not immediate
d3 :- 
    went(plasticSled, T2),
    sled(vanessa, T2),
    went(luge, T1),
    T1 < T2,
    T2 != T1 + 1.
:- not d3.

% #4 
% Kira and Ollie  went immediately before Regan.
d4 :-
    sled(kira_and_Ollie, T1),
    sled(regan, T2),
    T2 = T1 + 1.
:- not d4.

% #5
% Blake went in not an innertube.
d5 :- sled(blake_and_Flynn, T) , not went(innerTube2, T).
:- not d5.

% Print solution
sol(T, Person, Sled) :- sled(Person, T), went(Sled, T).

#hide.
#show sol(T, Person, Sled).
