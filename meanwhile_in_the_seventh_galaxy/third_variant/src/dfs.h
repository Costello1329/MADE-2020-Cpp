#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H

#include "type_list.h"
#include "value_list.h"
#include "graph.h"



template <typename Graph, size_t start, size_t end>
struct PathExists {
    static constexpr bool value = false;
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H.
