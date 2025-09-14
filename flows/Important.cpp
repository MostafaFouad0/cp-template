// Common matching variations
// --------------------------
//              |               Bipartite               |   Non-Bipartite
// +------------+---------------------------------------+------------------+
// | Unweighted | - Max flow algorithms                 | - Edmond's       |
// |   Edges    | - Repeated augmenting paths with DFS  |   blossom alg.   |
// |            | - Hopcroft-Karp / Kuhn's              |                  |
// +------------+---------------------------------------+------------------+
// | Weighted   | - Min cost max flow algorithms        | - DP solution    |
// |   Edges    | - Hungarian algorithm (perfect match) |   for small      |
// |            | - LP network simplex                  |   graphs         |
// +------------+---------------------------------------+------------------+

//if the maximum flow between two sets -> Hopcroft .. otherwise -> Kuhn's
