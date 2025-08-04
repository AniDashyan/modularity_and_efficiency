#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <random>

//  Multiply
int Multiply(int a, int b) {
    return a * b;
}

// Add
int Add(int a, int b) {
    return a + b;
}

// Fused Multiply-Add
int FusedMulAdd(int a, int b, int c) {
    return a * b + c;
}

void run_modular(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C) {
    for (size_t i = 0; i < A.size(); ++i) {
        int tmp = Multiply(A[i], B[i]);
        C[i] = Add(tmp, C[i]);
    }
}

void run_fused(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C) {
    for (size_t i = 0; i < A.size(); ++i) {
        C[i] = FusedMulAdd(A[i], B[i], C[i]);
    }
}

int main() {
    const size_t N = 1 << 24;
    std::vector<int> A(N), B(N), C(N, 1);

    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1, 100);
    for (size_t i = 0; i < N; ++i) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    #ifdef FUSED_VERSION_OPT
        std::cout << "[Optimized Build]\n";
    #elif defined(FUSED_VERSION_DEBUG)
        std::cout << "[Unoptimized Build]\n";
    #else
        std::cout << "[Unknown Optimization Level]\n";
    #endif


    auto start = std::chrono::steady_clock::now();
    run_modular(A, B, C);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Modular Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    std::fill(C.begin(), C.end(), 1.0f);
    start = std::chrono::steady_clock::now();
    run_fused(A, B, C);
    end = std::chrono::steady_clock::now();
    std::cout << "Fused Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
    return 0;
}
