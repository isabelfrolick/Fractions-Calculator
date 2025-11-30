# Fraction Class (C++)

This project implements a fully normalized, exception-safe **Fraction** class in C++, supporting arithmetic, comparison, increment, and stream operators. The assignment focused on object-oriented design, operator overloading, normalization via GCD, and robust handling of invalid input.

---

Fractions are always stored in **normalized form**, e.g.:

- `5/15` → `1/3`  
- `-2/4` → `-1/2`  
- `-3/-9` → `1/3`

The default constructor creates the zero fraction: **0/1**.

You implement:

- `fraction_<netid>.h` — interface  
- `fraction_<netid>.cpp` — implementation  

A provided test file `FractionTest.cpp` validates all required behaviors.

---

## How to Run

Compile with the test program:

```bash
g++ -std=c++11 FractionTest.cpp fraction_<netid>.cpp -o fraction
./fraction
