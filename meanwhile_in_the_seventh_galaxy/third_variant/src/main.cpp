#include <iostream>
#include "graph.h"
#include "dfs.h"



int main () {
    using graph =
        Graph<
            Vertex<0, Edge<0, 1>>,
            Vertex<1, Edge<1, 2>, Edge<1, 5>>,
            Vertex<2, Edge<2, 3>, Edge<2, 0>>,
            Vertex<3, Edge<3, 4>>,
            Vertex<4, Edge<4, 1>>,
            Vertex<5, Edge<5, 4>>
        >;

    std::cout << "Path exists: " <<
        (PathExists<graph, 5, 0>::value ? "true" : "false") << std::endl;

    return 0;
}
