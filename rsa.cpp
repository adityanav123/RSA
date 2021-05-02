#include <iostream>
#include "Miller_rabin.cpp"
using namespace std;

/*
	RSA process - 
	1. generate 2 prime numbers p, q;
	2. find n = p * q;
	3. choose a number 'e' such that gcd(e, phi(n)) = 1.

*/
ulli secret_key, public_key_n, public_key_e;

ulli euclidean_gcd(ulli a, ulli b) {
	if (a == 0) return b;
	else 
		return euclidean_gcd(b % a, a);
}


ulli generatePrimes(int b) {
	// to generate b bit numbers and check if they are prime.
	ulli prime = (int)pow(2, b - 1) + rand() % (int)(pow(2, b) - 1);
	while(millerRabinTest(prime) == false) {
		prime = (int)pow(2, b - 1) + rand() % (int)(pow(2, b) - 1);
	}
	return prime;
}

ulli generate_pk(ulli q) {

	ulli e = 1 + rand() % q;
	while(euclidean_gcd(q, e) != 1) {
		e = 1 + rand() % q; // 1 < e < phi(n)
	}
	return e;
}

ulli extended_euclidean(ulli a, ulli b)  {
	ulli r_old = a, r_new = b;
	ulli x_old = 1, x_new = 0;
	ulli y_old = 0, y_new = 1;
	ulli quotient;

	while (r_new != 0) {
		quotient = (ulli)(r_old / r_new);
		// updates to the table.
		ulli t = r_new;
		r_new = r_old - quotient * r_new;
		r_old = t;

		// updating x and y.
		t = x_new;
		x_new = x_old - quotient * x_new;
		x_old = t;

		t = y_new;
		y_new = y_old - quotient * y_new;
		y_old = t;
	} 


	// x*phi_n + y*e = 1.
	// cout << "euler's eqation : " << x_old << " * phi_n + " << y_old << " * e" << " = 1.\n";

	return y_old;
}

ulli gcdUtility(ulli a, ulli b, ulli *x, ulli *y) {
	
	if(a == 0) {
		*x = 0; *y = 1;
		return b;
	}

	ulli xt, yt;  // intermidiate calculations.

	// recursion 
	ulli g = gcdUtility(b % a, a, &xt, &yt);

	ulli quotient = (b / a);

	*x = yt - quotient * xt;
	*y = xt;

	return g; // returning gcd, does'nt really matter here.
}

ulli extended_euclidean1(ulli a, ulli b)
{
	// source - pkc video - mit opencourseware
	ulli x, y;
	ulli g = gcdUtility(a, b, &x, &y); // calculates the table values.

	// x and y are calculated.

	// negative inverse is to be handled.
	ulli d = ((x % b) + b) % b;

	return d;
}

ulli generate_sk(ulli e, ulli phi_n) {
	// d.e = 1 mod(phi(n))
	ulli d;
	// d = extended_euclidean1(phi_n, e);
	d = extended_euclidean(phi_n, e);

	// d > 0.

	return d;
} 

ulli encrypt(ulli m) {
	ulli p, q;

	int bit = 4; 
	// how many bit the numbers should be ? 

	// generating prime - p and q where p != q.
	p = generatePrimes(bit);
	cout << "p : " << p << "\n";
	q = generatePrimes(bit);
	while(q == p) {
		q = generatePrimes(bit);
	}
	cout << "q : " << q << "\n";


	// n = p X q & phi(n) = (p - 1)(q - 1)
	ulli n = p * q;
	ulli phi_n = (p-1) * (q - 1);
	
	cout << "n : " << n << "\n";
	cout << "phi(n) : " << phi_n << "\n";

	// generate e where 1 < e < phi(e) and gcd(e, phi(e)) == 1.
	ulli e = generate_pk(phi_n);

	cout << "e : " << e << "\n";
	public_key_n = n;
	public_key_e = e;
	// PUBLIC KEY : (n, e)

	// SECRET KEY : d.
	ulli d = generate_sk(e, phi_n); // generating secret key 'd'

	secret_key = d;
	cout << "d : " << d << "\n";

	cout << "Encrypting - " << m << "\n";
	ulli enc = fast_power(m, e, n); 
	return enc;
}

void decrypt(ulli c, ulli d, ulli n) {
	// m = c^d mod(n)
	ulli ans = fast_power(c, d, n);
	cout << "decrypted message : " << ans << "\n";
}

void show_keys() {
	cout << "[ public keys : " << public_key_e << " , " << public_key_n << " ]\n";
	cout << "[ secret key : " << secret_key << " ]\n";
}
int main(){
	ulli message = 10;

	ulli enc = encrypt(message); // 4 - 4 bit message.

	show_keys();

	cout << "encrypted value for " << message << " is : " << enc << "\n"; 

	decrypt (enc , secret_key, public_key_n);
		

	// decrypt (enc , 15873, public_key_n);
	return 0;
}