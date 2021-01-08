// ----------------------------- polynomial.h ---------------------------------

// James Truong CSS501A

// Created: 11/11/2020

// Last Modified: 11/22/2020

// ----------------------------------------------------------------------------

// The polynomial class that represents a polynomial function. The polynomial
// object allows adding and subtracting polynomials, equivalence comparison,
// and outputs as a polynomial function. Does not allow multiplication or
// division of polynomial objects.
//
// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// ----------------------------------------------------------------------------

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;

struct Term {     // a term on the sparse polynomial
    double coeff;   // the coefficient of each term
    int power;      // the degree of each term
    Term *prev;     // a pointer to the previous higher term
    Term *next;     // a pointer to the next lower term
};

class Polynomial {

    /** Prints the Polynomial object in the form of:
    * Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
    * where n is the highest degree. If coefficient is negative for a term
    * less than Cn * X^n such as Cn-1 * X^n-1, will print 
    * Cn * x^n - Cn-1 * X^n-1 where Cn-1 is a negative coefficient.
    */ 
    friend ostream& operator<<( ostream &output, const Polynomial& p );

public:
    
    /** Initializes a 0-degree 0.0 coefficient polynomial object.
    * precondition: none.
    * postcondition: an empty polynomial object with a size of 0.
    */
    Polynomial( );

    /** Initializes a polynomial object with terms copied from another
    * another polynomial object.
    * precondition: another polynomial object.
    * postcondition: a separate copy of the polynomial object that was passed.
    */
    Polynomial( const Polynomial& p );

    /** Deconstructs the polynomial object.
    * precondition: none.
    * postcondition: a destructed polynomial object.
    */
    ~Polynomial( );

    /** Returns the highest degree of a term in the polynomial object.
    * precondition: none.
    * postcondition: returns the highest degree of a term in the polynomial.
    */
    int degree( ) const;

    /** Returns the coefficient of the term in the polynomial object with
    * the same power as passed. If power term in polynomial does not exist,
    * returns 0.
    * precondition: power term exists in polynomial object, otherwise returns
    * 0.
    * postcondition: returns a coefficient of the polynomial term with passed
    * power.
    */
    double coefficient( const int power ) const; 

    /** Returns true if the coefficient of the power term in the polynomial
    * object is changed. If coefficient is zero, removes the term and returns
    * true. If the passed power does not exist in the polynomial, inserts the
    * term of the power with passed coefficient and returns true. Returns false
    * if the passed power is less than 0 or if coefficient is 0 when the term
    * does not exist.
    * precondition: passed power is greater than or equal to 0.
    * postcondition: a polynomial with power term removed or changed.
    */
    bool changeCoefficient( const double newCoefficient, const int power );

    /** Adds polynomials together.
    * precondition: another polynomial object.
    * postcondition: returns a new polynomial object with sum of the polynomial
    * objects.
    */
    Polynomial operator+( const Polynomial& p ) const;

    /** Subtracts polynomials together.
    * precondition: another polynomial object.
    * postcondition: returns a new polynomial object with the net sum of the
    * polynomial objects.
    */
    Polynomial operator-( const Polynomial& p ) const;

    /** Compares polynomial objects and checks if they are equal.
    * precondition: another polynomial object.
    * postcondition: returns true if the polynomial objects are equal.
    * Otherwise, returns false.
    */
    bool operator==( const Polynomial& p ) const;

    /** Compares polynomial objects and checks if they are not equal.
    * precondition: another polynomial object.
    * postcondition: returns true if the polynomial objects are not equal.
    * Otherwise, returns false.
    */
    bool operator!=( const Polynomial& p ) const;

    /** Assigns this polynomial object as a copy of another polynomial object.
    * precondition: none.
    * postcondition: returns this polynomial object as a copy of the polynomial
    * p.
    */
    Polynomial& operator=( const Polynomial& p );

    /** Adds polynomial objects together making the result of the operation
    * this polynomial object.
    * precondition: another polynomial object.
    * postcondition: returns this polynomial object as the sum of the
    * polynomial objects.
    */
    Polynomial& operator+=( const Polynomial& p );

    /** Subtracts polynomial objects together making the result of the
    * operation this polynomial object.
    * precondition: another polynomial object.
    * postcondition: returns this polynomial object as the result of the
    * polynomial objects.
    */
    Polynomial& operator-=( const Polynomial& p );

    bool deleteLargestCoeff();


private:
 
    int size;         // # terms in the sparse polynomial
    Term *head;       // a pointer to the doubly-linked circular list of
                    // sparse polynomial

    /** Inserts a new term just before given pos with coeff newCoefficient
    * and power with given power. Returns true if newCoefficient != 0 and
    * power >= 0, false otherwise.
    * precondition: pos is not NULL, newCoefficient != 0, power >= 0.
    * postcondition: returns a boolean if a term was added to the polynomial.
    */
    bool insert( Term* pos, const double newCoefficient, const int power );

    /** Remove a term at given pos. Returns true if term can be removed,
    * false otherwise.
    * precondition: coeff at given pos is 0.0.
    * postcondition: returns a boolean if a term of the polynomial objects
    * was removed.
    */
    bool remove( Term* pos );

};

#endif
