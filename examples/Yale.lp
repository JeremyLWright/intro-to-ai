
% Yale shooting domain
% There is a turkey and a gun
% Actions are: load (means loading the gun), and shoot (means shooting at the turkey).
% Loading the gun causes the gun to be loaded.
% Shooting the gun (aimed at the turkey) causes the turkey to be dead, assumed the gun was loaded.
% Shoot causes the gun to be unloading if it was loaded before.
% Initial Solution: gun is unloaded; turkey is alive.
% Hypothetical Reasoning: What happens if we load the gun and then shoot the turkey.

% Planning and hypothetical reasoning are connected. 
% Planning is, I want to do this, what do I do?
% Hypothetical reasoning is, I did this, what will happen.

time(0..3).
alive(0).
nloaded(0).

load(0). %the action load happens at time point 0.
shoot(1).

loaded(T) :- not nloaded(T), time(T). %Closed world assumption, if the gun is not loaded, it is loaded
dead(T) :- not alive(T), time(T). % Closed world assumption.



%Loading the gun causes the gun to be loaded.
loaded(T + 1 ) :- load(T), time(T), nloaded(T). % loaded(T) if load T, and it is notloaded

%Shooting the gun causes the turkey to be dead
dead(T + 1) :- loaded(T), shoot(T), time(T).

%Shoot causes the gun to be unloaded if it was loaded before.
nloaded(T+1) :- loaded(T), shoot(T), time(T).

% If an action does not affect a fluent, then the fluent's values remains unchanged.
% Normally, a fluent does not change value, unless an action changes it.
% FRAME axioms (inertia axioms):
ab(alive, T+1) :- loaded(T), shoot(T), time(T).
alive(T + 1) :- alive(T), time(T), not ab(alive, T + 1).

nloaded(T+1) :- nloaded(T), time(T), not ab(nloaded, T+1).

ab(nloaded, T+1) :- load(T), nloaded(T), time(T).

#hide time(X).
#hide ab(X,Y).
