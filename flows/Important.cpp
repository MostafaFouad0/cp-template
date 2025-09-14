// Common matching variations
// --------------------------
//              |               Bipartite               |   Non-Bipartite
// +------------+---------------------------------------+------------------+
// | Unweighted | - Max flow algorithms                 | - Edmond's       |
// |   Edges    | - Repeated augmenting paths with DFS  |   blossom alg.   |
// |            | - Hopcroft-Karp                       |                  |
// +------------+---------------------------------------+------------------+
// | Weighted   | - Min cost max flow algorithms        | - DP solution    |
// |   Edges    | - Hungarian algorithm (perfect match) |   for small      |
// |            | - LP network simplex                  |   graphs         |
// +------------+---------------------------------------+------------------+
