#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_XOR_SUM_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_XOR_SUM_H



template <size_t Head, size_t... Tail>
struct XorSum {
    static constexpr size_t value = Head ^ XorSum<Tail...>::value;
};

template <size_t Head>
struct XorSum<Head> {
    static constexpr size_t value = Head;
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_FIRST_VARIANT_XOR_SUM_H.
