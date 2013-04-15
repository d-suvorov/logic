#include <iostream>
#include "primitives.hpp"


constexpr int (*add)(int, int) = R1< U11, S13<N, U33> >;
constexpr int (*mul)(int, int) = R1< Z, S23<add, U13, U33> >;

constexpr int (*one)(int) = S11<N, Z>;
constexpr int (*pow)(int, int) = R1< one, S23<mul, U13, U33> >;

constexpr int (*dec_impl)(int, int) = R1<Z, U23>;
// dec(x) = max(x - 1, 0)
constexpr int (*dec)(int) = S21<dec_impl, Z, U11>;
// sub(x, y) = max(x - y, 0)
constexpr int (*sub)(int, int) = R1< U11, S13<dec, U33> >;

constexpr int (*zero3)(int, int, int) = S13<Z, U33>;
constexpr int (*one3)(int, int, int) = S13< N, zero3 >;
constexpr int (*is_not_zero_impl)(int, int) = R1<Z, one3>;
constexpr int (*is_not_zero)(int) = S21<is_not_zero_impl, Z, U11>;

constexpr int (*gr)(int, int) = S12< is_not_zero, sub >;

constexpr int (*is_zero_impl)(int, int) = R1< one, zero3 >;
constexpr int (*is_zero)(int) = S21<is_zero_impl, Z, U11>;

constexpr int (*gr_or_equal)(int, int) = S12< is_zero, S22<gr, U22, U12> >;

constexpr int (*x_is_gr_or_equal_than_yz)(int, int, int, int) =
        S24< gr_or_equal, U14, S24<mul, U24, S14<N, U34>> >;

constexpr int (*zero2)(int, int) = S12< Z, U22 >;
// div_impl_g(x, y, z, w) = w + (x >= y * z)
constexpr int (*div_impl_g)(int, int, int, int) =
        S24<add, U44, x_is_gr_or_equal_than_yz>;

// int div_impl(int x, int y, int z)
// {
//     if (z == 0) return 0;
//     return div_impl(x, y, z - 1) + (x >= y * z);
// }
constexpr int (*div_impl)(int, int, int) = R2< zero2, div_impl_g >;

constexpr int (*divide)(int, int) = S32< div_impl, U12, U22, U12 >;

constexpr int (*mod)(int, int) = S22< sub, U12, S22< mul, divide, U22 > >;


// int div_count(int x, int d)
// {
//     if (d <= 0) return 0;
//     return (x % (d + 1) == 0) + div_count(x, d - 1);
// }
constexpr int (*y_plus_2)(int, int, int) = S13< N, S13<N, U23> >;
constexpr int (*div_count)(int, int) =
        R1< Z, S23< add, U33, S13< is_zero, S23<mod, U13, y_plus_2> > > >;
constexpr int (*minus_2)(int) = S11< dec, S11<dec, U11> >;

//1 if x = 0 or x = 1
constexpr int (*prime)(int) = S11< is_zero, S21<div_count, U11, minus_2> >;

constexpr int (*is_one)(int) =
        S21< mul, S11<is_zero, S11<dec, U11>>, S11<is_not_zero, U11> >;

// returns 1 if x == 0 and f(0) == 1
// int limex_impl<f>(x)
// {
//     if (x = 0) return f(0) == 1;
//     return (f(x - 1) == 1) + limex_impl<f>(x - 1);
// }
template<int (*f)(int)>
int limex_impl(int x, int y)
{
    return R1< S11<f, Z>, S23< add, S13< is_one, S13<f, U23> >, U33 > >(x, y);
}

template<int (*f)(int)>
int limex(int x)
{
    constexpr int(*limex_impl_front)(int) = S11< is_not_zero, S21<limex_impl<f>, Z, U11> >;
    return S21<mul, is_not_zero, limex_impl_front>(x);
}


int main()
{
    using std::cout;
    using std::endl;

    cout << add(5, 5) << endl;
    cout << mul(3, 4) << endl;
    cout << pow(2, 10) << endl;
    cout << dec(5) << endl;
    cout << sub(15, 6) << endl;
    cout << gr(4, 2) << endl;
    cout << divide(22, 3) << endl;
    cout << mod(22, 9) << endl;

    for (int i = 0; i < 22; i++)
        if (prime(i))
            cout << i << " ";
    cout << endl;

    cout << limex<is_not_zero>(1) << endl;
    cout << limex<prime>(4) << endl;

    return 0;
}
