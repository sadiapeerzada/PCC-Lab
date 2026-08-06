# PCC-Lab
# ⚙️ Parallel & Cloud Computing Laboratory — B.Sc. (Hons.) Computer Application V Semester

<div align="center">

![AMU](https://img.shields.io/badge/Aligarh_Muslim_University-006747?style=for-the-badge&logoColor=white)
![Course](https://img.shields.io/badge/Course_Code-CABSXO--5P01-8B0000?style=for-the-badge)
![Credits](https://img.shields.io/badge/Credits-02-0057A8?style=for-the-badge)
![Semester](https://img.shields.io/badge/Semester-V-gold?style=for-the-badge)
![Session](https://img.shields.io/badge/Session-2025--2026-333333?style=for-the-badge)

> *"When a nation becomes devoid of art and learning, it invites poverty and when poverty comes it brings in its wake thousands of crimes."*
> — **Sir Syed Ahmad Khan**

</div>

---

## 📋 Table of Contents

- [About the Course](#-about-the-course)
- [Course Details](#-course-details)
- [Assessment Scheme](#-assessment-scheme)
- [Weekly Lab Index](#-weekly-lab-index)
- [Tech Stack](#-tech-stack)
- [Lab File Format](#-lab-file-format)
- [Department Info](#-department-info)

---

## 📖 About the Course

This laboratory course is designed for **B.Sc. (Computer Application) V Semester** students to build a working foundation in **Parallel and Cloud Computing**. The course begins with core C programming and array handling, advances through shared-memory parallelism with **OpenMP**, distributed-memory communication with **MPI**, and concludes with **Cloud Computing** concepts — security, data analytics, and simulation using **CloudSim**.

Students progress from sequential C code to multi-threaded and multi-process parallel programs, and finally to cloud-based service and simulation environments, gaining hands-on exposure to the full spectrum of modern high-performance and distributed computing.

---

## 📌 Course Details

| Field | Details |
|---|---|
| **Course Title** | Laboratory Course-V |
| **Course Code** | CABSXO-5P01 |
| **Programme** | B.Sc. (Hons.) Computer Application |
| **Semester** | V |
| **Credits** | 02 |
| **Periods Per Week** | 03 |
| **Department** | Computer Science, AMU Aligarh |
| **Edition** | Revised — January 2026 |

### 🎯 Course Objectives

- Build a strong foundation in C programming, control flow, and array manipulation
- Understand and implement shared-memory parallelism using OpenMP
- Understand and implement distributed-memory communication using MPI
- Apply parallel techniques to numerical methods and sorting algorithms
- Understand cloud security fundamentals, data analytics, and cloud simulation using CloudSim

### ✅ Course Outcomes

After completing this course, students will be able to:

- Write, debug, and reason about sequential C programs involving numbers, characters, and arrays
- Parallelize computational problems using OpenMP directives, threads, and synchronization constructs
- Design and implement message-passing programs using MPI, including collective communication
- Apply parallel sorting and numerical methods to solve computationally intensive problems
- Evaluate basic cloud security practices and simulate cloud environments using CloudSim

---

## 📊 Assessment Scheme

```
Total Marks: 100
├── Continuous Assessment  →  60 Marks
│   ├── Sessional I        →  30 Marks
│   │   ├── Lab Report (signed)   →  20 Marks
│   │   ├── Lab Question (in-lab) →   5 Marks
│   │   └── Viva Voce             →   5 Marks
│   └── Sessional II       →  30 Marks
│       ├── Lab Report (signed)   →  20 Marks
│       ├── Lab Question (in-lab) →   5 Marks
│       └── Viva Voce             →   5 Marks
└── Final Lab Examination   →  40 Marks
```

> ⚠️ **Minimum Requirement:** At least **10** timely completed and duly signed weekly assignments are compulsory to appear in the Final Lab Examination.

---

## 📅 Weekly Lab Index

### Week 1 — Basic C Programming and Array Operations ✅ *(this folder)*

**Objectives:** Build foundational C programming skills — control flow, functions, and array handling — before moving into parallel programming.

| # | Problem | File |
|---|---|---|
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

**Tools:** GCC (GNU C Compiler)

**How to compile & run:**

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

> 📝 Programs 8, 9, and 10 are **interactive** — they first ask for the array size `N`, then prompt for each element. Program 9 allocates one extra slot (`N + 1`) to safely insert the new value. All 10 programs were compiled and tested with `gcc -Wall` and produced no errors or warnings.

---

### Week 2 — Basic OpenMP Programming and Number Checks

**Objectives:** Get started with the OpenMP API; parallelize simple number-checking problems.

---

### Week 3 — OpenMP Task Distribution and Mathematical Computation

**Objectives:** Distribute independent tasks across threads; parallelize basic mathematical computations.

---

### Week 4 — Introduction to OpenMP Environment & Tools

**Objectives:** Set up the OpenMP development environment; understand compiler flags and thread configuration.

---

### Week 5 — Parallelizing with Threads & Basic Problems

**Objectives:** Parallelize classic problems using `#pragma omp parallel` and thread-level constructs.

---

### Week 6 — Data Environment & Synchronization

**Objectives:** Understand shared vs. private data clauses; apply synchronization constructs (critical, barrier, lock).

---

### Week 7 — Advanced Work-Sharing & Reduction

**Objectives:** Use work-sharing constructs (`for`, `sections`) and the `reduction` clause for parallel aggregation.

---

### Week 8 — Introduction to MPI Environment & Basic Communication

**Objectives:** Set up the MPI environment; implement point-to-point send/receive communication.

---

### Week 9 — Collective Communication Operations

**Objectives:** Implement collective MPI operations — broadcast, scatter, gather, and reduce.

---

### Week 10 — Parallel Numerical Methods & Advanced Sorting (OpenMP Focus)

**Objectives:** Apply OpenMP to numerical methods and parallel sorting algorithms.

---

### Week 11 — Advanced Parallel Sorting (OpenMP & MPI)

**Objectives:** Compare and implement advanced parallel sorting algorithms using both OpenMP and MPI.

---

### Week 12 — Cloud Security Fundamentals & Basic Web Services

**Objectives:** Understand core cloud security principles; work with basic web services.

---

### Week 13 — Cloud Data Analytics & Advanced Security

**Objectives:** Explore cloud-based data analytics tools and advanced security practices.

---

### Week 14 — Cloud Simulation with CloudSim

**Objectives:** Simulate cloud computing environments and resource allocation strategies using CloudSim.

---

## 🛠️ Tech Stack

| Tool | Purpose |
|---|---|
| ![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white) | Core sequential programming (Week 1) |
| ![OpenMP](https://img.shields.io/badge/OpenMP-FF6600?style=flat-square) | Shared-memory parallel programming (Weeks 2–7, 10–11) |
| ![MPI](https://img.shields.io/badge/MPI-004C97?style=flat-square) | Distributed-memory message passing (Weeks 8–11) |
| ![CloudSim](https://img.shields.io/badge/CloudSim-2E8B57?style=flat-square) | Cloud environment simulation (Week 14) |
| **GCC** | C / OpenMP compilation |

---

**Deliverables per exercise (teacher-signed):**
- Source code with sample input/output
- Screenshot of compilation and execution *(from Week 2 onward)*

---

## 📁 Lab File Format

```
Lab File Index Template
─────────────────────────────────────────────────────
Week No. │ Problems with Description │ Page No. │ Teacher Signature & Date
─────────────────────────────────────────────────────
   1     │ 1#, 2#, ... 10#           │          │
   2     │ 1#, 2#, 3#                │          │
  ...    │ ...                       │          │
─────────────────────────────────────────────────────
Header: Page Number
Footer: Roll Number & Name
```

---

## 🏛️ Department Info

| Field | Details |
|---|---|
| **Department** | Department of Computer Science |
| **University** | Aligarh Muslim University, Aligarh (U.P.) India |
| **Lab Manual Edition** | Revised — January 2026 |
| **Convener** | Prof. Aasim Zafar |
| **Committee Members** | Prof. Mohammad Ubaidullah Bokhari · Dr. Arman Rasool Faridi · Dr. Faisal Anwer |
| **Design & Compilation** | Dr. Faraz Masood |

---

<div align="center">

**Department of Computer Science · Aligarh Muslim University**

*Lab Manual CABSXO-5P01 · Revised Edition January 2026*

</div>
