# Breaking Modularity for Efficiency

## Overview

This project demonstrates how **breaking modularity** through function fusion can improve CPU performance in compute-heavy loops. It benchmarks two approaches:

- **Modular**: Separate `Multiply` and `Add` functions.
- **Fused**: A single `FusedMulAdd` function that performs both operations in one call.

It also compares **optimized** vs **non-optimized** builds to show the real impact of compiler optimization flags like `-O3`, `-march=native`, and `-ffast-math`.

---

## Build & Run
```bash
## 1. Clone the repo:
git clone https://github.com/AniDashyan/modularity_and_efficiency
cd modularity_and_efficiency

## 2. Build the project and run both benchmarks:
cmake -S . -B build
cmake --build build --target run_benchmarks

## This executes both:
   * `fused_debug` — Unoptimized build (no compiler optimizations)
   * `fused_opt` — Optimized build (with `-O3`, `-march=native`, etc.)

## 3. If you only run:
cmake --build build
./build/fused_debug
```

## Example Output

```text
[Unoptimized Build]
Modular Time: 194ms
Fused Time: 198ms
[Optimized Build]
Modular Time: 10ms
Fused Time: 9ms
```

## How Does It Work?

### Modular vs Fused

* **Modular functions**: `Multiply(a, b)` and `Add(x, y)` are separate. This is clean but may involve extra function call overhead and memory traffic.
* **Fused function**: `FusedMulAdd(a, b, c)` does `a * b + c` in a single expression. This reduces overhead and can be **vectorized** more easily by the compiler.

### Optimization Flags

Compiler optimizations transform the code to run faster:

| Flag             | Description                                                      |
| ---------------- | ---------------------------------------------------------------- |
| `-O3`            | Enables aggressive optimization (loop unrolling, inlining, etc.) |
| `-march=native`  | Uses the full instruction set of your CPU (e.g. AVX, SSE)        |
| `-ffast-math`    | Relaxes IEEE compliance for faster math                          |
| `-funroll-loops` | Unrolls loops for better instruction throughput                  |

Without these, the compiler leaves code mostly as-is, resulting in:

* Extra function calls
* Poor loop performance
* No vectorization
Let me know if you want the README in markdown file format (`README.md`) or want to include profiling/`perf` instructions as well!
```
