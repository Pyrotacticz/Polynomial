// ----------------------------- polynomial.h ---------------------------------

// James Truong CSS501A

// Created: 11/11/2020

// Last Modified: 11/22/2020

// ----------------------------------------------------------------------------

// This is an implementation file of the polynomial class that represents a
// polynomial function. The polynomial object allows adding and subtracting
// polynomials, equivalence comparison, and outputs as a polynomial function.
// Does not allow multiplication or division of polynomial objects.
//
// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// ----------------------------------------------------------------------------

#include "polynomial.h"

/** Prints the Polynomial object in the form of:
* Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
* where n is the highest degree. If coefficient is negative for a term
* less than Cn * X^n such as Cn-1 * X^n-1, will print
* Cn * x^n - Cn-1 * X^n-1 where Cn-1 is a negative coefficient.
*/
ostream& operator<<(ostream& output, const Polynomial& p)
{
	Term *ptr = p.head->next;
	string sign;
	if (ptr == p.head)
	{
		output << '0';
	}
	else
	{
		for (; ptr != p.head; ptr = ptr->next)
		{
			// front of polynomial is special case.
			if (ptr->prev == p.head)
			{
				if (ptr->coeff == -1)
				{
					output << "-";
				}
				if (ptr->coeff != 1 && ptr->coeff != -1)
				{
					output << ptr->coeff;
				}
				else if (ptr->power == 0)
				{
					output << ((ptr->coeff > 0) ? ptr->coeff : -ptr->coeff);
				}
			}
			else if (ptr->coeff > 1 || ptr->coeff < -1)
			{
				output << ((ptr->coeff > 0) ? ptr->coeff : -ptr->coeff);
			}

			// powers are greater than 1 need to print X^
			if (ptr->power > 1)
			{
				output << "x^" << ptr->power;
			}
			else if (ptr->power == 1)
			{
				output << "x";
			}

			// need addition or subtraction for next term based on next ceoff
			if (ptr->next != p.head)
			{
				sign = ptr->next->coeff >= 1 ? " + " : " - ";
				output << sign;
			}
		}
	}
	return output;
}

/** Initializes a 0-degree 0.0 coefficient polynomial object.
* precondition: none.
* postcondition: an empty polynomial object with a size of 0.
*/
Polynomial::Polynomial() : head(new Term), size(0)
{
	head->coeff = 0.0;
	head->power = 0;
	head->next = head;
	head->prev = head;
}

/** Initializes a polynomial object with values copied from another
* another polynomial object.
* precondition: another polynomial object.
* postcondition: a separate copy of the polynomial object that was passed.
*/
Polynomial::Polynomial(const Polynomial& p) : head(new Term), size(0)
{
	head->coeff = 0.0;
	head->power = 0;
	head->next = head;
	head->prev = head;
	*this = p;
}

/** Deconstructs the polynomial object.
* precondition: none.
* postcondition: a destructed polynomial object.
*/
Polynomial::~Polynomial()
{
	Term *curr = head->next;
	Term *removable = curr;
	while(curr != head)
	{
		curr->coeff = 0.0;
		curr = curr->next;
		remove(removable);
		removable = curr;
	}
	delete curr;
	curr = nullptr;
	removable = nullptr;
}

/** Returns the highest degree of a term in the polynomial object.
* precondition: none.
* postcondition: returns the highest degree of a term in the polynomial.
*/
int Polynomial::degree() const
{

	return head->next->power;
}


/** Returns the coefficient of the term in the polynomial object with
* the same power as passed. If power term in polynomial does not exist,
* returns 0.
* precondition: power term exists in polynomial object, otherwise returns 0.
* postcondition: returns a coefficient of the polynomial term with passed power.
*/
double Polynomial::coefficient(const int power) const
{
	Term *ptr = head->next;
	for (; ptr != head; ptr = ptr->next)
	{
		if (ptr->power == power)
		{
			return ptr->coeff;
		}
	}
	return 0.0;
}

/** Returns true if the coefficient of the power term in the polynomial object
* is changed. If coefficient is zero, removes the term and returns true. If
* the passed power does not exist in the polynomial, inserts the term of the
* power with passed coefficient and returns true. Returns false if the passed
* power is less than 0 or if coefficient is 0 when .
* precondition: passed power is greater than or equal to 0.
* postcondition: a polynomial with power term removed or changed.
*/
bool Polynomial::changeCoefficient(const double newCoefficient, const int power)
{
	Term *curr = head->next;
	if (power >= 0)
	{
		if (curr == head)
		{
			return insert(curr->next, newCoefficient, power);
		}
		for (int i = 1; curr != head; i++, curr = curr->next)
		{
			if (curr->power == power)
			{
				curr->coeff = newCoefficient;
				if (newCoefficient == 0.0)
				{
					return remove(curr);
				}
				return true;
			}
			else if (curr->power < power)
			{
				return insert(curr, newCoefficient, power);
			}
			else if (size == i)
			{
				return insert(curr->next, newCoefficient, power);
			}
		}
	}
	return false;
}

/** Adds polynomials together.
* precondition: another polynomial object.
* postcondition: returns a new polynomial object with sum of the polynomial
* objects.
*/
Polynomial Polynomial::operator+(const Polynomial& p) const
{
	Polynomial sum = Polynomial();
	Term *adding = sum.head->next;
	Term *curr = head->next;
	Term *otherCurr = p.head->next;
	double newCoeff;
	while (curr != head && otherCurr != p.head)
	{
		if (curr->power > otherCurr->power)
		{
			sum.insert(adding->next, curr->coeff, curr->power);
			curr = curr->next;
			adding = adding->next;
		}
		else if (curr->power < otherCurr->power)
		{
			sum.insert(adding->next, otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
			adding = adding->next;
		}
		else
		{
			newCoeff = curr->coeff + otherCurr->coeff;
			sum.insert(adding->next, newCoeff, curr->power);
			curr = curr->next;
			otherCurr = otherCurr->next;
			if (newCoeff != 0.0)
			{
				adding = adding->next;
			}
		}
	}

	// If polynomials are not of equal term size
	if (curr != head)
	{
		while (curr != head)
		{
			sum.insert(adding, curr->coeff, curr->power);
			curr = curr->next;
			adding = adding->next;
		}
	}
	if (otherCurr != p.head)
	{
		while (otherCurr != p.head)
		{
			sum.insert(adding, otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
			adding = adding->next;
		}
	}
	return sum;
}

/** Subtracts polynomials together.
* precondition: another polynomial object.
* postcondition: returns a new polynomial object with the net sum of the
* polynomial objects.
*/
Polynomial Polynomial::operator-(const Polynomial& p) const
{
	Polynomial result = Polynomial();
	Term* build = result.head->next;
	Term* curr = head->next;
	Term* otherCurr = p.head->next;
	double newCoeff;
	while (curr != head && otherCurr != p.head)
	{
		if (curr->power > otherCurr->power)
		{
			result.insert(build->next, curr->coeff, curr->power);
			curr = curr->next;
			build = build->next;
		}
		else if (curr->power < otherCurr->power)
		{
			result.insert(build->next, -otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
			build = build->next;
		}
		else
		{
			newCoeff = curr->coeff - otherCurr->coeff;
			result.insert(build->next, newCoeff, curr->power);
			curr = curr->next;
			otherCurr = otherCurr->next;
			if (newCoeff != 0.0)
			{
				build = build->next;
			}
		}
	}

	// If polynomials are not of equal term size
	if (curr != head)
	{
		while (curr != head)
		{
			result.insert(build, curr->coeff, curr->power);
			curr = curr->next;
			build = build->next;
		}
	}
	if (otherCurr != p.head)
	{
		while (otherCurr != p.head)
		{
			result.insert(build, -otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
			build = build->next;
		}
	}
	return result;
}

/** Compares polynomial objects and checks if they are equal.
* precondition: another polynomial object.
* postcondition: returns true if the polynomial objects are equal. Otherwise,
* returns false.
*/
bool Polynomial::operator==(const Polynomial& p) const
{
	Term* curr = head->next;
	Term* otherCurr = p.head->next;
	if (size != p.size)
	{
		return false;
	}
	while (curr != head)
	{
		if (curr->coeff != otherCurr->coeff || curr->power != otherCurr->power)
		{
			return false;
		}
		curr = curr->next;
		otherCurr = otherCurr->next;
	}
	return true;
}

/** Compares polynomial objects and checks if they are not equal.
* precondition: another polynomial object.
* postcondition: returns true if the polynomial objects are not equal.
* Otherwise, returns false.
*/
bool Polynomial::operator!=(const Polynomial& p) const
{
	Term* curr = head->next;
	Term* otherCurr = p.head->next;
	if (size != p.size)
	{
		return true;
	}
	while (curr != head)
	{
		if (curr->coeff != otherCurr->coeff || curr->power != otherCurr->power)
		{
			return true;
		}
		curr = curr->next;
		otherCurr = otherCurr->next;
	}
	return false;
}

/** Assigns this polynomial object as a copy of another polynomial object.
* precondition: none.
* postcondition: returns this polynomial object as a copy of the polynomial
* p.
*/
Polynomial& Polynomial::operator=(const Polynomial& p)
{
	Term *ptr = head->next;
	Term *removable = ptr;
	Term *otherPtr = p.head->next;

	// deallocate memory first before reassigning
	while (ptr != head)
	{
		ptr->coeff = 0.0;
		ptr = ptr->next;
		remove(removable);
		removable = ptr;
	}

	while (otherPtr != p.head)
	{
		insert(ptr->next, otherPtr->coeff, otherPtr->power);
		otherPtr = otherPtr->next;
		ptr = ptr->next;
	}
	return *this;
}

/** Adds polynomial objects together making the result of the operation
* this polynomial object.
* precondition: another polynomial object.
* postcondition: returns this polynomial object as the sum of the
* polynomial objects.
*/
Polynomial& Polynomial::operator+=(const Polynomial& p)
{
	Term *curr = head->next;
	Term *otherCurr = p.head->next;
	Term *removable = nullptr;
	double sum;
	while (curr != head && otherCurr != p.head)
	{
		if (curr->power < otherCurr->power)
		{
			insert(curr, otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
		}
		else if (curr->power == otherCurr->power)
		{
			sum = curr->coeff + otherCurr->coeff;
			if (sum == 0.0)
			{
				removable = curr;
				removable->coeff = 0.0;
				curr = curr->next;
				remove(removable);
				otherCurr = otherCurr->next;
			}
			else
			{
				changeCoefficient(sum, curr->power);
				curr = curr->next;
				otherCurr = otherCurr->next;
			}
			
		}
		else
		{
			curr = curr->next;
		}
	}
	if (otherCurr != p.head)
	{
		while (otherCurr != p.head)
		{
			insert(curr, otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
			curr = curr->next;
		}
	}
	return *this;
}

/** Subtracts polynomial objects together making the result of the
* operation this polynomial object.
* precondition: another polynomial object.
* postcondition: returns this polynomial object as the result of the
* polynomial objects.
*/
Polynomial& Polynomial::operator-=(const Polynomial& p)
{
	Term *curr = head->next;
	Term *otherCurr = p.head->next;
	Term *removable = nullptr;
	double result;
	while (curr != head && otherCurr != p.head)
	{
		if (curr->power < otherCurr->power)
		{
			insert(curr, -otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
		}
		else if (curr->power == otherCurr->power)
		{
			result = curr->coeff - otherCurr->coeff;
			if (result == 0.0)
			{
				removable = curr;
				removable->coeff = 0.0;
				curr = curr->next;
				otherCurr = otherCurr->next;
				remove(removable);
			}
			else
			{
				changeCoefficient(result, curr->power);
				curr = curr->next;
				otherCurr = otherCurr->next;
			}
		}
		else
		{
			curr = curr->next;
		}
	}
	if (otherCurr != p.head)
	{
		while (otherCurr != p.head)
		{
			insert(curr, -otherCurr->coeff, otherCurr->power);
			otherCurr = otherCurr->next;
			curr = curr->next;
		}
	}
	return *this;
}
bool Polynomial::deleteLargestCoeff()
{
	double maxcoefficient = -INFINITY;
	Term* curr = head->next;
	Term* removable;
	while (curr != head)
	{
		if (curr->coeff > maxcoefficient)
		{
			maxcoefficient = curr->coeff;
		}
		curr = curr->next;
	}
	curr = head->next;
	while (curr != head)
	{
		if (curr->coeff == maxcoefficient)
		{
			removable = curr;
			curr = curr->next;
			remove(removable);
			return true;
		}
		curr = curr->next;
	}
	return false;
}


/** Inserts a new term just before given pos with coeff newCoefficient
* and power with given power. Returns true if newCoefficient != 0 and
* power >= 0, false otherwise.
* precondition: pos is not NULL, newCoefficient != 0, power >= 0.
* postcondition: returns a boolean if a term was added to the polynomial.
*/
bool Polynomial::insert(Term* pos, const double newCoefficient, const int power)
{
	if (newCoefficient != 0.0 && power >= 0)
	{
		Term* addTerm = new Term;
		Term* before = pos->prev;
		addTerm->coeff = newCoefficient;
		addTerm->power = power;
		addTerm->next = pos;
		pos->prev = addTerm;
		addTerm->prev = before;
		before->next = addTerm;
		addTerm = nullptr;
		size++;
		return true;
	}
	return false;
}

/** Remove a term at given pos. Returns true if term can be removed,
* false otherwise.
* precondition: coeff at given pos is 0.0.
* postcondition: returns a boolean if a term of the polynomial objects
* was removed.
*/
bool Polynomial::remove(Term* pos)
{
	if (pos->coeff == 0.0)
	{
		Term* last = pos->prev;
		Term* after = pos->next;
		last->next = after;
		after->prev = last;
		pos->next = nullptr;
		pos->prev = nullptr;
		delete pos;
		pos = nullptr;
		size--;
		return true;
	}
	return false;
}