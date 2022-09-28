#include<stdio.h>
#include<cmath>


// Returns the sum of two sahasras.
//DONE
char* sahasra_add(const char* sahasra1, const char* sahasra2);

// Returns the comparison value of two sahasras.
// Returns 0 when both are equal.
// Returns +1 when sahasra1 is greater, and -1 when sahasra2 is greater.
//DONE
int sahasra_compare(const char* sahasra1, const char* sahasra2);

// Returns the difference (obviously, nonnegative) of two sahasras.
//DONE
char* sahasra_diff(const char* sahasra1, const char* sahasra2);

// Returns the product of two sahasras.
//DONE
char* sahasra_multiply(const char* sahasra1, const char* sahasra2);

// Returns sahasra1 mod sahasra2
// The mod value should be in the range [0, sahasra2 - 1].
// sahasra2 > 1
// Implement a O(log sahasra1) time taking algorithm.
// O(sahasra1 / sahasra2) time taking algorithm may exceed time limit.
// O(sahasra1 / sahasra2) algorithm may repeatedly subtract sahasra2 from sahasra1.
// That will take sahasra1/sahasra2 iterations.
// You need to design a O(log sahasra1) time taking algorithm.
// Generate your own testcases at https://www.omnicalculator.com/math/modulo
//DONE
char* sahasra_mod(const char* sahasra1, const char* sahasra2);

// Returns sahasra1 ^ sahasra2.
// Let 0 ^ n = 0, where n is an sahasra.
// Implement a O(log n) sahasra multiplications algorithm.
// 2^3000 has less than 1000 decimal digits. 3000 sahasra multiplications may exceed time limit.
//DONE
char* sahasra_pow(const char* sahasra1, unsigned int n);

// Returns Greatest Common Devisor of sahasra1 and sahasra2.
// Let GCD be "0" if both sahasra1 and sahasra2 are "0" even though it is undefined, mathematically.
// Use Euclid's theorem to not exceed the time limit.
//DONE
char* sahasra_gcd(const char* sahasra1, const char* sahasra2);

// Returns nth fibonacci number.
// sahasra_fibonacci(0) = sahasra "0".
// sahasra_fibonacci(1) = sahasra "1".
//DONE
char* sahasra_fibonacci(unsigned int n);

// Returns the factorial of n.
//DONE
char* sahasra_factorial(unsigned int n);

// Returns the Binomial Coefficient C(n,k).
// 0 <= k <= n
// C(n,k) < 10^1000 because the returning value is expected to be less than 10^1000.
// Use the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1)
// Make sure the intermediate sahasra values do not cross C(n,k).
// Use Dynamic Programming. Use extra space of not more than O(k) number of sahasras. Do not allocate the whole O(nk) DP table.
// Don't let C(1000,900) take more time than C(1000,500). Time limit may exceed otherwise.
char* sahasra_bincoeff(unsigned int n, unsigned int k);

// Returns the offset of the largest sahasra in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
//DONE
int sahasra_max(char **arr, int n);

// Returns the offset of the smallest sahasra in the array.
// Return the smallest offset if there are multiple occurrences.
// 1 <= n <= 1000
//DONE
int sahasra_min(char **arr, int n);

// Returns the offset of the first occurrence of the key sahasra in the array.
// Returns -1 if the key is not found.
// 1 <= n <= 1000
//DONE
int sahasra_search(char **arr, int n, const char* key);

// Returns the offset of the first occurrence of the key sahasra in the SORTED array.
// Returns -1 if the key is not found.
// The array is sorted in nondecreasing order.
// 1 <= n <= 1000
// The implementation should be a O(log n) algorithm.
//DONE
int sahasra_binsearch(char **arr, int n, const char* key);

// Sorts the array of n sahasras.
// 1 <= n <= 1000
// The implementation should be a O(n log n) algorithm.
//DONE
void sahasra_sort(char **arr, int n);

// Coin-Row Problem - Dynamic Programming Solution
// There is a row of n coins whose values are some positive integers C[0..n-1].
// The goal is to pick up the maximum amount of money subject to the constraint that
// no two coins adjacent in the initial row can be picked up.
// 1 <= n <= 1000
// The implementation should be O(n) time and O(1) extra space even though the DP table may be of O(n) size.
// Eg: Coins = [10, 2, 4, 6, 3, 9, 5] returns 25
char* coin_row_problem(char **arr, int n);