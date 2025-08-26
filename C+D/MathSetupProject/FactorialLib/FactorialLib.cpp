#include "pch.h"              
#include "FactorialLib.h"


extern "C" FACT_API long long __cdecl factorial(int n)
{
    if (n < 0) return -1;
    long long res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}
