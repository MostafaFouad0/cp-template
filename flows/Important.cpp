Common matching variations
--------------------------
             |               Bipartite               |   Non-Bipartite
+------------+---------------------------------------+------------------+
| Unweighted | - Max flow algorithms                 | - Edmond's       |
|   Edges    | - Repeated augmenting paths with DFS  |   blossom alg.   |
|            | - Hopcroft-Karp / Kuhn's              |                  |
+------------+---------------------------------------+------------------+
| Weighted   | - Min cost max flow algorithms        | - DP solution    |
|   Edges    | - Hungarian algorithm (perfect match) |   for small      |
|            | - LP network simplex                  |   graphs         |
+------------+---------------------------------------+------------------+

given a set1 one and set2 and each edge have wieght .. use hungarian

//if you need the smallest lexicographically permutation -> Kuhn
