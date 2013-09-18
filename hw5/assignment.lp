%Given the following knowledge base:
author(david).
author(john).
author(michael).
author(emily).

wrote(david, paper1).
wrote(david, paper2).
wrote(john, paper2).
wrote(michael, paper3).
wrote(emily, paper4).

reviewer(greg).
reviewer(justin).
reviewer(jarred).

paper(paper1;paper2;paper3;paper4).

result(positive; negative).

review(greg, paper1, positive).
review(jarred, paper1, positive).
review(jarred, paper1, negative).

review(justin, paper2, positive).
review(greg, paper2, negative).
review(jarred, paper2, negative).

review(jarred, paper3, positive).
review(jarred, paper3, positive).

%Let reject(A,P) be read as: "send rejection letter to author A about paper P", and need_reviewer(X) as "Paper X need more reviewer(s)".
reject(A,P) :- paper(P), author(A).
need_reviewer(X) :- reviewer(X).

%Translate the following the sentence:
%1. A paper needs more reviewer(s) if and only if is it has not been reviewed by at least three different reviewers.
%% A paper needs more reviews if is have been reviewed by less than three reviewers.
%2. A paper is rejected if and only if it has not been positively reviewed by two different reviewers.

prob1a(P) :- paper(P), result(R), review(greg, P, R).
prob1b(P) :- paper(P), result(R), review(justin, P, R).
prob1c(P) :- paper(P), result(R), review(jarred, P, R).

nprob1(P) :- prob1a(P), prob1b(P), prob1c(P), paper(P).
prob1(P) :- not nprob1(P), paper(P).

#hide.
#show prob1(P).
