// ----------------------- polynomialDriver.cpp ------------------------------

// James Truong CSS501A

// Created: 11/11/2020

// Last Modified: 11/22/2020

// ----------------------------------------------------------------------------

// A driver that tests the polynomial object and its class methods. It ensures
// the implementation of the respective object is correct and complete. The
// polynomial object allows adding and subtracting polynomials, equivalence
// comparison, and outputs as a polynomial function.
//
// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// ----------------------------------------------------------------------------

#include <iostream>
#include "polynomial.h"

using namespace std;

int main()
{
	// testing sample driver.
	cout << "=========TESTING SAMPLE DRIVER.CPP TESTS=========" << endl;
	Polynomial p1;
	p1.changeCoefficient(1, 1);
	p1.changeCoefficient(4, 4);
	p1.changeCoefficient(2.2, 2);
	p1.changeCoefficient(-3.8, 3);
	cout << "p1 = " << p1 << endl;
	p1.changeCoefficient(0, 2);
	cout << "p1 = " << p1 << endl;
	Polynomial p2 = p1;
	p2.changeCoefficient(9.5, 2);
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	Polynomial p3 = p1 + p2;
	cout << "p3 = " << p3 << endl << endl;

	// testing defautl constructor, changeCoefficient, degree(),
	// coefficient(int) public methods
	Polynomial p;
	cout << "=========TESTING POYNOMIAL CLASS=========" << endl;
	cout << "default constructor of a polynomial p is " << p << endl;
	cout << "default p has coefficient of " << p.coefficient(0) << endl;
	cout << "default p has degree of " << p.degree() << endl;

	cout << "After p.changeCoefficient(2, 2), ";
	p.changeCoefficient(2, 2);
	cout << "x^2 has coefficient of " << p.coefficient(2);
	cout << " and p.degree() is " << p.degree() << endl;
	cout << "p = " << p << endl;

	cout << "After p.changeCoefficient(4, 3), ";
	p.changeCoefficient(4, 3);
	cout << "x^3 has coefficient of " << p.coefficient(3);
	cout << " and p.degree() is " << p.degree() << endl;
	cout << "p = " << p << endl;

	cout << "After p.changeCoefficient(1, 1), ";
	p.changeCoefficient(1, 1);
	cout << "and x has coefficient of " << p.coefficient(1) << endl;
	cout << "p = " << p << endl;

	cout << "After p.changeCoefficient(-3, 0), ";
	p.changeCoefficient(-3, 0);
	cout << "x^0 has coefficient of " << p.coefficient(0) << endl;
	cout << "p = " << p << endl;

	cout << "After p.changeCoefficient(-6, 5), ";
	p.changeCoefficient(-6, 5);
	cout << "x^5 has coefficient of " << p.coefficient(5);
	cout << " and p.degree() is " << p.degree() << endl;
	cout << "p = " << p << endl;

	cout << "After p.changeCoefficient(0, 2), ";
	p.changeCoefficient(0, 2);
	cout << "x^2 has coefficient of " << p.coefficient(2) << endl;
	cout << "p = " << p << endl;

	cout << "After p.changeCoefficient(0, 5), ";
	p.changeCoefficient(0, 5);
	cout << "x^5 has coefficient of " << p.coefficient(5) << endl;
	cout << "p = " << p << endl;

	cout << "running changeCoefficient(0, 1), (0, 3), (0, 0), (0, 0),";
	cout << " (2, -3), (0, 5)" << endl;
	cout << "p.changeCoefficient(0, 1) is ";
	cout << (p.changeCoefficient(0, 1) ? "true" : "false") << endl;
	cout << "p.changeCoefficient(0, 0) is ";
	cout << (p.changeCoefficient(0, 0) ? "true" : "false") << endl;
	cout << "p.changeCoefficient(0, 3) is ";
	cout << (p.changeCoefficient(0, 3) ? "true" : "false") << endl;
	cout << "p.changeCoefficient(0, 0) is ";
	cout << (p.changeCoefficient(0, 0) ? "true" : "false") << endl;
	cout << "p.changeCoefficient(2, -3) is ";
	cout << (p.changeCoefficient(2, -3) ? "true" : "false") << endl;
	cout << "p.changeCoefficient(0, 5) is ";
	cout << (p.changeCoefficient(0, 5) ? "true" : "false") << endl;
	cout << "After removing all, p = " << p << endl;

	// testing x^0 terms only
	p.changeCoefficient(1, 0);
	cout << "After p.changeCoefficient(1, 0), p is " << p << endl;
	p.changeCoefficient(-8, 0);
	cout << "After p.changeCoefficient(-8, 0), p is " << p << endl;
	p.changeCoefficient(-1, 0);
	cout << "After p.changeCoefficient(-1, 0), p is " << p << endl;
	p.changeCoefficient(-5, 0);
	cout << "After p.changeCoefficient(-5, 0), p is " << p << endl;

	// testing x^1 terms in front
	p.changeCoefficient(1, 1);
	cout << "After p.changeCoefficient(1, 1), p is " << p << endl;
	p.changeCoefficient(-1, 1);
	cout << "After p.changeCoefficient(-1, 1), p is " << p << endl;
	p.changeCoefficient(-1, 2);
	cout << "After p.changeCoefficient(-1, 2), p is " << p << endl;
	p.changeCoefficient(-1, 3);
	cout << "After p.changeCoefficient(-1, 3), p is " << p << endl;
	p.changeCoefficient(1, 4);
	cout << "After p.changeCoefficient(1, 4), p is " << p << endl;
	cout << endl;

	// Testing +, -, ==, !=. +=. -=
	cout << "======TESTING ADD, SUBTRACT, AND COMPARISON=====" << endl;
	Polynomial f;
	f.changeCoefficient(5, 5);
	f.changeCoefficient(4, 4);
	f.changeCoefficient(3, 3);
	f.changeCoefficient(2, 2);
	f.changeCoefficient(1, 1);
	f.changeCoefficient(5, 0);
	cout << "f = " << f << endl << endl;

	Polynomial g(f);
	cout << "g(f) = " << g << endl << endl;
	Polynomial h = g + Polynomial();
	cout << "h = g + Polynomial() is " << h << endl;
	h = g + f;
	cout << "h = g + f is " << h << endl;

	cout << "TESTING COMPARISON" << endl;
	cout << "g == f is " << ((g == f) ? "true" : "false") << endl;
	cout << "g == h is " << ((g == h) ? "true" : "false") << endl;
	cout << "g != f is " << ((g != f) ? "true" : "false") << endl;
	cout << "h != g is " << ((h != g) ? "true" : "false") << endl;

	cout << "TESTING REPLACEMENT ARITHMETIC" << endl;
	h += g;
	cout << "h += g is " << h << endl;
	h += Polynomial();
	cout << "h += Polynomial() is " << h << endl;
	h = h - f;
	cout << "h = h - f is " << h << endl;
	h -= f;
	cout << "h -= f is " << h << endl;
	h -= g + f;
	cout << "h -= g + f is " << h << endl;
	h -= h;
	cout << "h -= h is " << h << endl;

	// size of polynomial k < f
	Polynomial k;
	cout << "===TESTING DIFFERENT SIZE POLYNOMIAL K===" << endl;
	k.changeCoefficient(-6, 6);
	k.changeCoefficient(-7, 7);
	k.changeCoefficient(-3, 1);
	k.changeCoefficient(-10, 0);
	cout << "f = " << f << endl;
	cout << endl;
	cout << "k = " << k << endl;
	cout << endl;
	cout << "k + f = " << k + f << endl;
	cout << "f + k = " << f + k << endl;
	cout << "k - f = " << k - f << endl;
	cout << "f - k = " << f - k << endl;
	k += f;
	cout << "k += f is " << k << endl;
	k -= f;
	cout << "k -= f is " << k << endl;
	k -= f;
	cout << "k -= f is " << k << endl;

	// size of polynomial x > y
	cout << "===TESTING DIFFERENT SIZE POLYNOMIAL X,Y===" << endl;
	Polynomial x, y;
	x.changeCoefficient(10, 10);
	x.changeCoefficient(-9.2, 8);
	x.changeCoefficient(4.7, 4);
	x.changeCoefficient(45.6, 0);
	x.changeCoefficient(7.6, 2);

	y.changeCoefficient(-10, 10);
	y.changeCoefficient(5.2, 8);
	y.changeCoefficient(45.6, 0);
	y.changeCoefficient(-5.9, 3);
	cout << "x = " << x << endl;
	cout << endl;
	cout << "y = " << y << endl;
	cout << endl;
	cout << "x + y = " << x + y << endl;
	cout << "y + x = " << y + x << endl;
	cout << "x - y = " << x - y << endl;
	cout << "y - x = " << y - x << endl;
	x += y;
	cout << "x += y is " << x << endl;
	x -= y;
	cout << "x -= y is " << x << endl;
	x -= y;
	cout << "x -= y is " << x << endl;
	x += y;
	cout << "x += y is " << x << endl;

	// size of polynomial z >> a
	cout << "===TESTING DIFFERENT SIZE POLYNOMIAL Z,A===" << endl;
	Polynomial z, a;
	for (int i = 0; i < 11; i++)
	{
		z.changeCoefficient(i, i);
	}
	a.changeCoefficient(1, 1);
	cout << "z = " << z << endl;
	cout << endl;
	cout << "a = " << a << endl;
	cout << endl;
	cout << "a + z = " << a + z << endl;
	cout << "z + a = " << z + a << endl;
	cout << "a - z = " << a - z << endl;
	cout << "z - a = " << z - a << endl;
	z += a;
	cout << "z += a is " << z << endl;
	z -= a;
	cout << "z -= a is " << z << endl;
	z -= a;
	cout << "z -= a is " << z << endl;
	z += a;
	cout << "z += a is " << z << endl;
	a += z;
	cout << "a += z is " << a << endl;
	a -= z;
	cout << "a -= z is " << a << endl;
	a -= z;
	cout << "a -= z is " << a << endl;
	a += z;
	cout << "a += z is " << a << endl;

	a = z;
	cout << a << endl;
	a.deleteLargestCoeff();
	cout << a;

	return 0;
}