#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_SECOND_VARIANT_BINARY_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_SECOND_VARIANT_BINARY_H



template <size_t Value>
struct Log2 {
    static constexpr size_t value = Log2<(Value >> size_t(1))>::value + 1;
};

template <>
struct Log2<0> {
    static constexpr size_t value = 0;
};


template <size_t i, size_t Value>
struct GetBit {
    static constexpr bool value = GetBit<i - 1, (Value >> size_t(1))>::value;
};

template <size_t Value>
struct GetBit<0, Value> {
    static constexpr bool value = (Value % 2) != 0;
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_SECOND_VARIANT_BINARY_H.
