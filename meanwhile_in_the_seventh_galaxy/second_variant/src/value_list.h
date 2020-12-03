#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_SECOND_VARIANT_VALUE_LIST_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_SECOND_VARIANT_VALUE_LIST_H

#define Type bool


/// NullType:
struct NullType {};

/// ValueList:
template <Type _Head, Type... _Tail>
struct ValueList {
    static constexpr Type Head = _Head;
    using Tail = ValueList<_Tail...>;
};

template <Type _Head>
struct ValueList<_Head> {
    static constexpr Type Head = _Head;
    using Tail = NullType;
};


/// PushFront:
template <Type Value, typename T>
struct PushFront {};

template <Type Value, Type Head, Type... Tail>
struct PushFront<Value, ValueList<Head, Tail...>> {
    using type = ValueList<Value, Head, Tail...>;
};

template <Type Value>
struct PushFront<Value, NullType> {
    using type = ValueList<Value>;
};


/// PushBack:
template <Type Value, typename T>
struct PushBack {};

template <Type Value, Type Head, Type... Tail>
struct PushBack<Value, ValueList<Head, Tail...>> {
    using type = ValueList<Head, Tail..., Value>;
};

template <Type Value>
struct PushBack<Value, NullType> {
    using type = ValueList<Value>;
};


/// PopFront:
template <typename T>
struct PopFront {};

template <Type Head, Type Second, Type... Tail>
struct PopFront<ValueList<Head, Second, Tail...>> {
    using type = ValueList<Second, Tail...>;
};


/// PopBack:
template <typename T>
struct PopBack {};

template <Type First, Type Second, Type... Tail>
struct PopBack<ValueList<First, Second, Tail...>> {
private:
    using List = ValueList<First, Second, Tail...>;

public:
    using type =
        typename PushFront<
            First,
            typename PopBack<
                typename PopFront<List>::type
            >::type
        >::type;
};

template <Type First, Type Second>
struct PopBack<ValueList<First, Second>> {
    using type = ValueList<First>;
};


/// Get:
template <size_t, typename>
struct Get {};

template <size_t i, Type Head, Type... Tail>
struct Get<i, ValueList<Head, Tail...>> {
private:
    using List = ValueList<Head, Tail...>;

public:
    static_assert(i <= sizeof...(Tail));
    static constexpr Type value = Get<i - 1, typename PopFront<List>::type>::value;
};

template <Type Head, Type... Tail>
struct Get<0, ValueList<Head, Tail...>> {
    static constexpr Type value = Head;
};


/// Set:
template <size_t, Type, typename>
struct Set {};

template <size_t i, Type Value, Type Head, Type... Tail>
struct Set<i, Value, ValueList<Head, Tail...>> {
private:
    using List = ValueList<Head, Tail...>;

public:
    static_assert(i <= sizeof...(Tail));
    using type =
        typename PushFront<Head,
            typename Set<i - 1, Value, typename PopFront<List>::type>::type
        >::type;
};

template <Type Value, Type Head, Type... Tail>
struct Set<0, Value, ValueList<Head, Tail...>> {
private:
    using List = ValueList<Head, Tail...>;

public:
    using type = typename PushFront<Value, typename PopFront<List>::type>::type;
};

template <Type Value, Type Head>
struct Set<0, Value, ValueList<Head>> {
    using type = ValueList<Value>;
};


/// Construct:
template <Type Value, size_t i>
struct Construct {
    static_assert(i != 0);
    using type = typename PushFront<Value, typename Construct<Value, i - 1>::type>::type;
};

template <Type Value>
struct Construct<Value, 1> {
    using type = ValueList<Value>;
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_SECOND_VARIANT_BOOL_LIST_H.
