#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H

#include "xor_sum.h"
#include "binary.h"



template <size_t... Heaps>
struct Game {
    static constexpr bool first_player_wins = XorSum<Heaps...>::value;
    static constexpr ssize_t first_move_heap_index = -1;
    static constexpr ssize_t first_move_rocks_count = -1;
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_GAME_H.
