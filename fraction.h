/*
 *Isabel Frolick
 * fraction_18ijzf.h
 */




#ifndef FRACTION_H_
#define FRACTION_H_


#pragma once

#include <iostream>
#include <string>


using namespace std;


class Fraction{

public:
	//constructors
	Fraction();
	Fraction(const int numerator);
	Fraction(const int numerator, const int denominator);

	//copy constructor
	//Fraction(Fraction &copy);


	//accessors
	int numerator() const;
	int denominator() const;

	//binary arthmetic operators
	Fraction operator+(const Fraction &obj);
	friend Fraction operator+(const int number, const Fraction &obj);
	Fraction operator-(const Fraction &obj);
	friend Fraction operator-(const Fraction &obj, const int number);
	friend Fraction operator-(const int number, const Fraction &obj);
	Fraction operator*(const Fraction& obj);
	Fraction operator/(const Fraction& obj);
	Fraction& operator+=(const Fraction &obj);


	//Unary operator
	Fraction operator-() const;
	Fraction operator++(int);
	Fraction& operator++();

	//Comparison operators
	bool operator==(const Fraction& obj) const;
	bool operator!=(const Fraction& obj) const;
	bool operator>(const Fraction& obj) const;
	bool operator>=(const Fraction& obj) const;
	bool operator<(const Fraction& obj) const;
	bool operator<=(const Fraction& obj) const;
	friend bool operator>(const Fraction& obj, const int number);
	friend bool operator<(const int number, const Fraction& obj);

	//Stream operators
	friend ostream &operator<<(ostream& out, const Fraction& obj);
	friend istream &operator>>(istream& in, Fraction& obj);

private:
	int myNumerator;
	int myDenominator;
	//helper functions
	int gcd(int num, int denom);
	void simplify(int num, int denom);

};

class FractionException : public std :: exception{
public:
	const char* what() const noexcept{
	return "ERROR: illegal denominator found.";
	}



};



#endif
