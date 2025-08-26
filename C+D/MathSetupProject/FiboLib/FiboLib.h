#pragma once

#ifdef FIBOLIB_EXPORTS              // auto-defined by the FiboLib project
#  define FIBO_API __declspec(dllexport)
#else
#  define FIBO_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	// Returns the nth Fibonacci number (n >= 0). For n < 0 returns -1.
	FIBO_API int __cdecl fibonacci(int n);

#ifdef __cplusplus
}
#endif
