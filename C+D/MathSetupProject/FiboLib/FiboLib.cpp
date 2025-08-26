#include "pch.h"        

#include "FiboLib.h"

// Iterative (fast, non-recursive) implementation
extern "C" FIBO_API int __cdecl fibonacci(int n) {
    if (n < 0) return -1;         // simple error code
    if (n <= 1) return n;

    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}
