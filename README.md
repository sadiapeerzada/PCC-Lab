# 📘 CABSXO-5P01 — Parallel Computing and Cloud Computing
### Laboratory Manual

---

## 📑 Table of Contents

| Week | Laboratory Focus | Page |
|:----:|-------------------|:----:|
| 1 | **Basic C Programming and Array Operations** ✅ *(this folder)* | 5 |
| 2 | Basic OpenMP Programming and Number Checks | 6 |
| 3 | OpenMP Task Distribution and Mathematical Computation | 7 |
| 4 | Introduction to OpenMP Environment & Tools | 8 |
| 5 | Parallelizing with Threads & Basic Problems | 15 |
| 6 | Data Environment & Synchronization | 22 |
| 7 | Advanced Work-Sharing & Reduction | 29 |
| 8 | Introduction to MPI Environment & Basic Communication | 37 |
| 9 | Collective Communication Operations | 47 |
| 10 | Parallel Numerical Methods & Advanced Sorting (OpenMP Focus) | 55 |
| 11 | Advanced Parallel Sorting (OpenMP & MPI) | 61 |
| 12 | Cloud Security Fundamentals & Basic Web Services | 69 |
| 13 | Cloud Data Analytics & Advanced Security | 73 |
| 14 | Cloud Simulation with CloudSim | 77 |

---

## 🗂️ Week 1 — Basic C Programming and Array Operations

This week builds the foundation needed before moving into parallel
programming (OpenMP/MPI) in later weeks — core C syntax, control flow,
functions, and array handling.

| # | Program | File |
|:-:|---------|------|
| 1 | Check if the entered number is a palindrome | `1_palindrome.c` |
| 2 | Find the roots of a quadratic equation | `2_quadratic_roots.c` |
| 3 | Determine if the entered year is a leap year | `3_leap_year.c` |
| 4 | Calculate compound and simple interest | `4_simple_compound_interest.c` |
| 5 | Check whether a character is a vowel or consonant | `5_vowel_consonant.c` |
| 6 | Print prime numbers between a given range | `6_primes_in_range.c` |
| 7 | Find the LCM and HCF of two numbers | `7_lcm_hcf.c` |
| 8 | Find the largest and smallest number in an array of size N | `8_largest_smallest_array.c` |
| 9 | Insert a value at a particular location in an array of size N | `9_insert_in_array.c` |
| 10 | Search for a value in an array of size N | `10_search_in_array.c` |

### ⚙️ How to Compile & Run

```bash
cd "Week 1"

# compile a single program (use -lm for programs 2 and 4, which use math.h)
gcc 1_palindrome.c -o palindrome
./palindrome

gcc 2_quadratic_roots.c -o quadratic -lm
./quadratic

# or compile everything in one go
for f in *.c; do gcc "$f" -o "${f%.c}.out" -lm; done
```

### 📝 Notes

- Programs 8, 9, and 10 are **interactive** — they first ask for the
  array size `N`, then prompt for each element one at a time.
- Program 9 allocates one extra slot in the array (`N + 1`) so the
  new value can be inserted without overflowing the array bounds.
- Program 2 and Program 4 need the `-lm` flag while compiling since
  they use `sqrt()` and `pow()` from `math.h`.
- All 10 programs were compiled and tested with `gcc -Wall` and
  produced no errors or warnings.

---

## 👥 Credits

**Originally Designed by the Lab Manual Committee:**

- Prof. Mohammad Ubaidullah Bokhari
- Dr. Arman Rasool Faridi
- Dr. Faisal Anwer
- Prof. Aasim Zafar *(Convener)*

**Design & Compilation:**

- Dr. Faraz Masood

---

<div align="center">

*CABSXO-5P01 · Parallel Computing and Cloud Computing Laboratory*

</div>
