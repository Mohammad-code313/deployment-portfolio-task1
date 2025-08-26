// MathMasterApp.cpp
// Console app that calls two DLLs at runtime (Credit + Distinction):
//  - FactorialLib.dll : factorial(int) -> long long
//  - FiboLib.dll      : fibonacci(int) -> int
// Falls back to internal implementations if DLLs are not available.

#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <string>
#include <limits>

// --------------------- DLL signatures ---------------------
typedef long long(__cdecl* factorial_fn)(int); // FactorialLib.dll
typedef int(__cdecl* fibo_fn)(int);     // FiboLib.dll

template<class T>
static T load_proc(HMODULE mod, const char* name) {
    return reinterpret_cast<T>(GetProcAddress(mod, name));
}

// --------------------- internal fallbacks -----------------
static long long factorial_fallback(int n) {
    if (n < 0) return -1;
    long long res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

static int fibonacci_fallback(int n) {
    if (n < 0) return -1;
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int c = a + b; a = b; b = c;
    }
    return b;
}

// --------------------- main menu -------------------------
int main() {
    std::cout << "=== MathMaster (Credit + Distinction) ===\n";
    std::cout << "This app loads TWO DLLs at runtime:\n"
        << "  - FactorialLib.dll : factorial(int)\n"
        << "  - FiboLib.dll      : fibonacci(int)\n\n";

    while (true) {
        std::cout << "Choose an option:\n"
            << "  1) Factorial\n"
            << "  2) Fibonacci\n"
            << "  3) Exit\n"
            << "> ";

        int choice = 0;
        if (!(std::cin >> choice)) break;
        if (choice == 3) break;

        int n = 0;
        std::cout << "Enter a number: ";
        if (!(std::cin >> n)) break;

        // Eat any leftover newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            long long result = -1;
            bool usedDll = false;

            if (HMODULE h = LoadLibraryA("FactorialLib.dll")) {
                if (auto fn = load_proc<factorial_fn>(h, "factorial")) {
                    result = fn(n); usedDll = true;
                }
                FreeLibrary(h);
            }

            if (!usedDll) {
                result = factorial_fallback(n);
                std::cout << "(Using internal factorial)\n";
            }
            else {
                std::cout << "(Using FactorialLib.dll)\n";
            }

            std::cout << "factorial(" << n << ") = " << result << "\n\n";
        }
        else if (choice == 2) {
            int result = -1;
            bool usedDll = false;

            if (HMODULE h = LoadLibraryA("FiboLib.dll")) {
                if (auto fn = load_proc<fibo_fn>(h, "fibonacci")) {
                    result = fn(n); usedDll = true;
                }
                FreeLibrary(h);
            }

            if (!usedDll) {
                result = fibonacci_fallback(n);
                std::cout << "(Using internal fibonacci)\n";
            }
            else {
                std::cout << "(Using FiboLib.dll)\n";
            }

            std::cout << "fibonacci(" << n << ") = " << result << "\n\n";
        }
        else {
            std::cout << "Invalid choice.\n\n";
        }
    }

    std::cout << "Goodbye! Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}
