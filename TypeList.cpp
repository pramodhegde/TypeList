#include <iostream>

struct meta_null {};

template<typename Head, typename Tail>
struct meta_node
{
    typedef Head head;
    typedef Tail tail;
};

template <int x>
struct meta_int
{
    static const int value = x;
};

template<typename Iter, typename End>
struct accumulate
{
    int operator()()
    {
        return Iter::head::value + accumulate<typename Iter::tail, End>()();
    }
};

template<typename End>
struct accumulate<End,End>
{
    int operator()()
    {
        return	0;
    }
};

template<typename Iter, typename End>
struct product
{
    int operator()()
    {
        return Iter::head::value * product<typename Iter::tail, End>()();
    }
};

template<typename End>
struct product<End,End>
{
    int operator()()
    {
        return 1;
    }
};

int main() {
    using meta_list = meta_node<meta_int<1>,
          meta_node<meta_int<2>,
          meta_node<meta_int<3>,
          meta_node<meta_int<4>,
          meta_node<meta_int<5>, meta_null>>>>>;

    std::cout << accumulate<meta_list, meta_null>()() << std::endl;
    std::cout << product<meta_list, meta_null>()() << std::endl;

    return 0;
}
