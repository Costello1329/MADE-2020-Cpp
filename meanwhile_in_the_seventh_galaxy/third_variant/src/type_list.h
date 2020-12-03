#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_TYPE_LIST_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_TYPE_LIST_H



/// NullType:
struct NullType {};


/// TypeList:
template <typename... Args>
struct TypeList {};

template <typename H, typename... T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};

template <typename H>
struct TypeList<H> {
    using Head = H;
    using Tail = NullType;
};

template <>
struct TypeList<> {
    using Head = NullType;
    using Tail = NullType;
};


/// Length:
template <typename... T>
struct Length {};

template <typename... T>
struct Length<TypeList<T...>> {
    static constexpr size_t value = 1 + Length<typename TypeList<T...>::Tail>::value;
};

template <>
struct Length<TypeList<>> {
    static constexpr size_t value = 0;
};

template <>
struct Length<NullType> {
    static constexpr size_t value = 0;
};


/// Concat:
template <typename... T>
struct Concat {};

template <typename T, typename... U>
struct Concat<T, TypeList<U...>> {
    using type = TypeList<T, U...>;
};

template <typename T>
struct Concat<T, TypeList<>> {
    using type = TypeList<T>;
};

template <typename T>
struct Concat<T, NullType> {
    using type = TypeList<T>;
};


/// TypeAt
template <size_t, typename...>
struct TypeAt {};

template <size_t i, typename... T>
struct TypeAt<i, TypeList<T...>> {
    static_assert(i < sizeof...(T));
    using type = typename TypeAt<i - 1, typename TypeList<T...>::Tail>::type;
};

template <typename... T>
struct TypeAt<0, TypeList<T...>> {
    using type = typename TypeList<T...>::Head;
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_TYPE_LIST_H.
