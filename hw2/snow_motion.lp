% Snow Motion
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
rider(xerxes;blake;flynn;kira;ollie;regan;vanessa).
vehicle(innerTube1;toboggan;luge;innerTube2;plasticSled).
order(first;second;third;forth;fifth).

owner(vanessa,plasticSled).

capacity(innerTube1, 1).
capacity(innerTube2, 1).
capacity(toboggan, 2).
capacity(plasticSled, 1).
capacity(luge, 2).

sled(first, innerTube1).
sled(second, toboggan).
:- sled(fifth, innerTube1).

1 { sled(O, V) : vehicle(V) } 1 :- order(O). % For every order, sled a vehicle once

#hide rider/1.
#hide vehicle/1.
#hide order/1.
% sled(Xerxes,plasticSled).
% sled(Blake,plasticSled).
% sled(Flynn,plasticSled).
% sled(Kira,plasticSled).
% sled(Ollie,plasticSled).
% sled(Regan,plasticSled).

%1 { sled(Rider, V) : rider(Rider) } 1 :- vehicle(V).
%sled(X, innerTube1) :- rider(X).
%sled(X, innerTube2) :- rider(X).
%1 { sled(Rider, innerTube1) } 1 :- vehicle(innerTube1).
%1 { sled(Rider, innerTube2) } 1 :- vehicle(innerTube2).
%1 { sled(Rider, V) : rider(Rider) } 1 :- vehicle(V).
