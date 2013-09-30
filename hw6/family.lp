% Summer has finally arrived! To celebrate the occasion, 
% Dan and Janet Smith decided to throw a barbeque and afternoon 
% party at their summerhouse on Fiesta Lake. Telling all their 
% friends to bring their family, friends, and of course bathing 
% suits, they ended up with quite a houseful and the party was 
% a great success. The Smiths were especially pleased because 
% some of their relatives who lived farther away managed to attend. 
% Determine from the clues the full name of the family members in 
% attendance, their relationship to Dan and Janet Smith, and 
% the city where each had their home.
% 
% 1. Natalie, whose last name wasn't West, didn't live in Boston.
% 
% 2. Janet's cousin didn't live in New York though her last name was Mann.
% 
% 3. George didn't live in Providence. Sara's last name wasn't Green.
% 
% 4. Robert, who was Dan's uncle, didn't live in New York. Ms. Green lived in New York.
% 
% 5. Sara wasn't Janet's sister. Mr. Smith wasn't related to Janet.
% 
% 6. Dan's brother lived in Chicago. The man whose last name is West lives in Providence. 

first_name(natalie;janet;george;robert;dan;sara;janet).
last_name(smith;west;mann;green).
city(boston;new_york;providence;chicago).


0 { live(P, C) } 1 :- first_name(P), city(C).
:- live(natalie, boston).
:- live(janet, new_york).
:- live(george, providence).
:- live(robert, new_york).


0 { full_name(F, L) } 1 :- first_name(F), last_name(L). 
:- full_name(natalie, west).
:- not full_name(dan,smith).
:- not full_name(janet,smith).
:- not full_name(janet,mann).

:- full_name(sara,green).



