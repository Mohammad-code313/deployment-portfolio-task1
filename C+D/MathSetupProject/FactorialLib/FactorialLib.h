#pragma once

#ifdef FACTORIALLIB_EXPORTS   // <-- EXACT project-defined symbol
#  define FACT_API __declspec(dllexport)
#else
#  define FACT_API __declspec(dllimport)
#endif

extern "C" FACT_API long long __cdecl factorial(int n);
