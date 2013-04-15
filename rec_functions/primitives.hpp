#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

int Z(int x) { return 0; }

int N(int x) { return x + 1; }



int U11(int x1) { return x1; }
int U12(int x1, int x2) { return x1; }
int U13(int x1, int x2, int x3) { return x1; }
int U14(int x1, int x2, int x3, int x4) { return x1; }

int U22(int x1, int x2) { return x2; }
int U23(int x1, int x2, int x3) { return x2; }
int U24(int x1, int x2, int x3, int x4) { return x2; }

int U33(int x1, int x2, int x3) { return x3; }
int U34(int x1, int x2, int x3, int x4) { return x3; }

int U44(int x1, int x2, int x3, int x4) { return x4; }



template< int (*f)(int), int (*g1)(int) >
int S11(int x1) { return f(g1(x1)); }

template< int (*f)(int), int (*g1)(int, int) >
int S12(int x1, int x2) { return f(g1(x1, x2)); }

template< int (*f)(int), int (*g1)(int, int, int) >
int S13(int x1, int x2, int x3) { return f(g1(x1, x2, x3)); }

template< int (*f)(int), int (*g1)(int, int, int, int) >
int S14(int x1, int x2, int x3, int x4) { return f(g1(x1, x2, x3, x4)); }

template< int (*f)(int, int), int (*g1)(int), int (*g2)(int) >
int S21(int x1) { return f(g1(x1), g2(x1)); }

template< int (*f)(int, int), int (*g1)(int, int), int (*g2)(int, int) >
int S22(int x1, int x2) { return f(g1(x1, x2), g2(x1, x2)); }

template< int (*f)(int, int), int (*g1)(int, int, int), int (*g2)(int, int, int) >
int S23(int x1, int x2, int x3) { return f(g1(x1, x2, x3), g2(x1, x2, x3)); }

template< int (*f)(int, int), int (*g1)(int, int, int, int), int (*g2)(int, int, int, int) >
int S24(int x1, int x2, int x3, int x4) { return f(g1(x1, x2, x3, x4), g2(x1, x2, x3, x4)); }

template< int (*f)(int, int, int), int (*g1)(int, int), int (*g2)(int, int), int (*g3)(int, int) >
int S32(int x1, int x2) { return f(g1(x1, x2), g2(x1, x2), g3(x1, x2)); }



template< int (*f)(int), int (*g)(int, int, int) >
int R1(int x1, int y)
{
    return y == 0 ? f(x1) : g(x1, y - 1, R1<f, g>(x1, y - 1));
}

template< int (*f)(int, int), int (*g)(int, int, int, int) >
int R2(int x1, int x2, int y)
{
    return y == 0 ? f(x1, x2) : g(x1, x2, y - 1, R2<f, g>(x1, x2, y - 1));
}

#endif // PRIMITIVES_HPP
