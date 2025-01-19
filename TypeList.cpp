#include <iostream>
#include <tuple>
#include <concepts>

template <int x>
using meta_int = std::integral_constant<int, x>;

template <typename Head, typename Tail>
struct meta_node {
    using head = Head;
    using tail = Tail;
};

using meta_null = std::tuple<>; // End of the type list

// Concepts to ensure valid types for accumulate and product
template <typename T>
concept meta_node_concept = requires {
    typename T::head;
    typename T::tail;
};

template <typename T>
concept integral_constant_concept = requires {
    { T::value } -> std::same_as<int>;
};

// Accumulate the list of meta_nodes
template <typename List>
struct accumulate;

template <meta_node_concept Node>
struct accumulate<Node> {
    static constexpr int value = Node::head::value + accumulate<typename Node::tail>::value;
};

template <>
struct accumulate<meta_null> {
    static constexpr int value = 0;
};

// Product the list of meta_nodes
template <typename List>
struct product;

template <meta_node_concept Node>
struct product<Node> {
    static constexpr int value = Node::head::value * product<typename Node::tail>::value;
};

template <>
struct product<meta_null> {
    static constexpr int value = 1;
};

int main() {
    using meta_list = meta_node<meta_int<1>,
          meta_node<meta_int<2>,
          meta_node<meta_int<3>,
          meta_node<meta_int<4>,
          meta_node<meta_int<5>, meta_null>>>>>;

    std::cout << "Sum: " << accumulate<meta_list>::value << std::endl;  // Outputs 15 (sum)
    std::cout << "Product: " << product<meta_list>::value << std::endl;    // Outputs 120 (product)

    return 0;
}

