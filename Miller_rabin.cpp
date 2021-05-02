#include <iostream>
#include <cmath>
// #include <stdlib.h>
using namespace std;
#define ulli signed long long int

/*
 * Intuition - MillerRabin:
 * 
 * Based on Fermat primality - a^(n-1) congruent to 0 mod(n)
 *
 * factorizing n-1 as multiplication of even and odd values.
 * i.e. (n - 1) = 2^s * d; // d = odd.
 *
 * substituting above equation in a^(n-1) congruent to 0 mod(n).
 * and rearranging.
 * (a^(2^(s-1) * d) + 1) (a^(2^(s-2) * d) + 1) (a^(2^(s-3) * d) + 1) .... (a^d + 1) (a^d - 1) congruent to 0 mod(n).
 * if the no. is prime, it should be divisible by any of the above factors in the LHS.
 */

ulli fast_power(ulli base, ulli exponent, ulli modulus) {
	ulli ans = 1;
	base %= modulus;
	while(exponent) {
		// odd exponent = 1 multiply.
		if (exponent & 1) {
			ans = (ulli) ans * base % modulus;
		}
		// else 2 multiply - even power.
		base = (ulli) base * base % modulus;
		exponent >>= 1; // exponent /= 2;
	} 
	return ans;
}


bool check_prime (ulli a, ulli d, ulli s, ulli n) {
	ulli x;
	x = fast_power(a, d, n);

	// checking for (a^d + 1) and (a^d - 1) 
	if (x == 1 || x == n - 1) {
		return true;
	}
	// checking for other multipliers.
	for (int i = 1; i < s; i++) {
		x = (ulli) (x * x % n);
		if (x == n - 1) {
			return true;
		}	
	}
	return false;
}

bool millerRabinTest(ulli n, ulli k = 5) {
	// k is the accuracy parameter.
	if (n < 4) {
		if (n == 2 || n == 3) return true;
	}
	// finding s.
	int s = 0;
	ulli d = n - 1;
	while ((d & 1) == 0) {
		d >>= 1; // divided by 2.
		s++;
	}

	// iterating k times
	int i;
	for (i=0;i<k;i++) {
		// choosing some random value between [2, n - 3]; since n < 4 is covered.
		ulli a = 2 + rand() % (n - 3);
		// ulli x;
		// x = fast_power(a, d, n);
		//checking prime.
		if (check_prime(a, d, s, n) == true) {
			return true;
		}
	}
	return false;
	
}
// int main() {
// 	ulli n = 5;
// 	cout << "isPrime? " << millerRabinTest(n) << "\n";
// 	return 1;
// }
