#include <iostream>
#include "binary.h"
#include "value_list.h"



template <size_t width, size_t height>
struct Floor {
    static constexpr int value = 0;
};


int main () {
    std::cout << "Possibilities count: " << Floor<6, 100>::value << std::endl;
    return 0;
}
