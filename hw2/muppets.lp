% Example muppets

muppet(kermit;piggy;fozzy).
vehicle(bike;bus;car).
park(disney;magic;marine).

:- not went(kermit, disney).

:- muppet(X), went(X, marine), not travel(X, bike).

:- not travel(piggy, car).
:- travel(fozzy, bus).

1 { travel(X,Y) : muppet(X) } 1 :- vehicle(Y).
1 { travel(X,Y) : vehicle(X) } 1 :- muppet(Y).

1 { went(X,Y) : muppet(X) } 1 :- park(Y).
1 { went(X,Y) : park(X) } 1 :- muppet(Y).
