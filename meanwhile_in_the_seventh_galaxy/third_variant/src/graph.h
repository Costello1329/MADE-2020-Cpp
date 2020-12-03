#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_GRAPH_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_GRAPH_H

#include "type_list.h"



/// Edge:
template <size_t _from, size_t _to>
struct Edge {
    static constexpr size_t from = _from;
    static constexpr size_t to = _to;
    static_assert(_from != _to);
};

/**
 * Checks The edge.
 * type = true, payload = index of vertex: checks that all Edges::from are = to the index.
 * type = false, payload = vertices count: checks that all Edges::to are < vertices count
 */
template <bool, size_t, typename...>
struct CheckEdges {};

template <bool type, size_t payload>
struct CheckEdges<type, payload, NullType> {
    using list = NullType;
};

template <bool type, size_t payload, typename... Edges>
struct CheckEdges<type, payload, TypeList<Edges...>> {
private:
    using Head = typename TypeList<Edges...>::Head;
    using Tail = typename TypeList<Edges...>::Tail;
    using _Tail = typename CheckEdges<type, payload, Tail>::list;

public:
    static_assert(type ? Head::from == payload : Head::to < payload);
    using list = typename Concat<Head, _Tail>::type;
};


/// Vertex
template <size_t _index, typename... _Edges>
struct Vertex {
    static constexpr size_t index = _index;
    using Edges = typename CheckEdges<true, _index, TypeList<_Edges...>>::list;
};

template <size_t _index>
struct Vertex<_index> {
    static constexpr size_t index = _index;
    using Edges = NullType;
};

/**
 * Should be used only by CheckVertices!!!
 */
template <size_t _index, typename... _Edges>
struct ConstructVertex {
    static constexpr size_t index = _index;
    using Edges = NullType;
};

template <size_t _index, typename... _Edges>
struct ConstructVertex<_index, TypeList<_Edges...>> {
    static constexpr size_t index = _index;
    using Edges = TypeList<_Edges...>;
};

/**
 * Checks The Vertices and theirs edges (Edge::to).
 */
template <size_t, size_t, typename...>
struct CheckVertices {};

template <size_t _index, size_t _vertices_count>
struct CheckVertices<_index, _vertices_count, NullType> {
    using list = NullType;
};

template <size_t index, size_t vertices, typename... Vertices>
struct CheckVertices<index, vertices, TypeList<Vertices...>> {
private:
    using Head = typename TypeList<Vertices...>::Head;
    using Tail = typename TypeList<Vertices...>::Tail;
    using _Edges = typename CheckEdges<false, vertices, typename Head::Edges>::list;
    using _Head = ConstructVertex<Head::index, _Edges>;
    using _Tail = typename CheckVertices<index + 1, vertices, Tail>::list;

public:
    static_assert(Head::index == index);
    using list = typename Concat<_Head, _Tail>::type;
};


/// Graph:
template <typename... _Vertices>
struct Graph {
    using Vertices =
        typename CheckVertices<0, sizeof...(_Vertices), TypeList<_Vertices...>>::list;
};

template <>
struct Graph<> {
    using Vertices = NullType;
};


#endif /// MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_GRAPH_H.
