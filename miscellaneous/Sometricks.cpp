// Erdős–Szekeres theorem :
// Consider a permutation p with length n. At least one of the following is true:
// There exists an increasing subsequence with length sqrt(n).
// There exists a decreasing subsequence with length sqrt(n).

// Assume you have n rocks with nonnegative integer weights a1,a2,…,an such that a1+a2+⋯+an=m
// You want to find out if there is a way to choose some rocks such that their total weight is w
// Suppose there are three rocks with equal weights a,a,a
// . Notice that it doesn't make any difference if we replace these three rocks with two rocks with weights a,2a
// . We can repeat this process of replacing until there are at most two rocks of each weight. The sum of weights is still m
// , so there can be only sqrt(m)
//  rocks (see next point). Now you can use a classical DP algorithm but with only sqrt(m)
//  elements, which can be lead to a better complexity in many cases.

