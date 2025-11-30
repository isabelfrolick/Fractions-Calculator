/*
 *Isabel Frolick
 
 * fraction.cpp
 */




#include <iostream>

#include "fraction.h"

using namespace std;

//constructors- default, one integer, two integers

Fraction::Fraction(): myNumerator(0), myDenominator(1){ }

Fraction::Fraction(const int numerator): myNumerator(numerator), myDenominator(1){}

Fraction::Fraction(const int numerator, const int denominator): myNumerator(numerator), myDenominator(denominator){
		simplify(myNumerator, myDenominator);

}



//accessor methods

int Fraction::numerator() const { return myNumerator; }

int Fraction::denominator() const {return myDenominator; }


//simplify() call to check fraction is mathematically possible,
// and normalized recursively using its greatest common divisor

void Fraction::simplify(int num, int denom){

	if(denom == 0){					//if denominator is zero- throw exception
		throw FractionException();
	}

	if(num%denom != 0){				//if fraction can be normalized, call gcd()
		gcd(num, denom);
	}

	if(num > 0 && denom < 0){		//if the denominator is negative and numerator is positive
		num = -num;					//make the numerator positive instead of denominator
		denom = abs(denom);
	}

	myNumerator = num/gcd(num, denom);			//set attributes to the num parameter / by the value returned by gcd()
	myDenominator = denom/ gcd(num, denom);		//to normalize the fractions

}

//gcd() method to get the greatest common divisor of the fraction recursively to normalize

int Fraction::gcd(int num, int denom) {
	int n, m, modulus;


	num = abs(num);			//set both inputs to their absolute values
	denom = abs(denom);

	n = num;
	m = denom;

	while(n%m != 0){		//while the modulus can be reduced, reduce it
		modulus = n%m;
		n = m;
		m = modulus; //when n%m is zero, m is the greatest common divisor btwn the numerator and divisor
	}

	return m;	//return greatest common divisor
}



//addition operator for adding 2 fraction objects

Fraction Fraction::operator+(const Fraction &obj) {
	int num, denom;

	num = myNumerator*(obj.denominator()) + myDenominator*(obj.numerator()); //fraction on LHS is going to have myNumerator and myDenominator (the priavte attributes) as its attributes

	denom = myDenominator*(obj.denominator());

	return Fraction(num, denom); //returns fraction type

}


//addition operator for adding an integer (on LHS) and Fraction type

Fraction operator+(const int number, const Fraction &obj) {

	Fraction myfraction(number, 1); //set the denom to 1 to use LHS integer as fraction

	int num = myfraction.numerator()*obj.denominator() + myfraction.denominator()*obj.numerator();
	int denom = myfraction.denominator()*obj.denominator();

	myfraction.gcd(num, denom); //normalize the fraction being returned
	return Fraction(num, denom); 	//return fraction

}

//subtraction operator for adding 2 fraction objects

Fraction Fraction::operator-(const Fraction &obj){

	int num, denom;
	num = myNumerator*(obj.denominator()) - myDenominator*(obj.numerator()); //LHS fraction values are stored in attributes
	denom = myDenominator*(obj.denominator());

	gcd(num, denom); //normalize the fraction being returned (can just  call method bc this operator function is in Function class)
	return Fraction(num, denom); //return fraction

}

//subtraction operator for subtracting an integer (on RHS) from Fraction type
	Fraction operator-(const Fraction &obj, const int number){

		Fraction myfraction(number, 1); //'cast' integer as a fraction by giving a denominator of 1

		int num = obj.numerator()*myfraction.denominator() - obj.denominator()*myfraction.numerator();
		int denom = obj.denominator()*myfraction.denominator();

		myfraction.gcd(num, denom); //bc this is a friend function, call simplify() method (of Fraction class) using
											//an object of the class

		return Fraction(num, denom);	//return normalized fraction

}


//subtraction operator for subtracting a Fraction type (on RHS) from integer
Fraction operator-(const int number, const Fraction &obj){
			Fraction myfraction(number, 1);

			int num = myfraction.numerator()*obj.denominator() - myfraction.denominator()*obj.numerator();
			int denom = myfraction.denominator()*obj.denominator();

			myfraction.gcd(num, denom);
			return Fraction(num, denom);
		}


//multiplication operator for 2 fraction type objects
Fraction Fraction::operator*(const Fraction& obj){
	int num, denom;

	num = myNumerator*obj.numerator();
	denom = myDenominator*obj.denominator();


	return Fraction(num, denom);
}


//division operator for 2 fraction type objects
Fraction Fraction::operator/(const Fraction& obj){
	int num, denom;

	num = myNumerator*obj.denominator();
	denom = myDenominator*obj.numerator();
	gcd(num, denom);

	return Fraction(num, denom);

}

//unary negation

Fraction Fraction::operator-() const{
	int num = myNumerator;
	num = -num;

	return Fraction(num, myDenominator); //denominator will never be negated

}


//post increment- takes in integer parameter
Fraction Fraction::operator++(int){

	int initialNum = myNumerator; //save the initial state of the attributes
	int initialDenom = myDenominator;

	 myNumerator = myNumerator + myDenominator; //update the attributes


	return Fraction(initialNum, initialDenom); //return the saved states

}


//pre-increment
Fraction& Fraction::operator++(){
	myNumerator = myNumerator + myDenominator; //increments fraction

	return *this;	//a hidden argument to nonstatic member functions
					//local variable, a pointer to attributes myNumerator/ myDenominator
}

//Addition assignment function for 2 fraction type objects
Fraction& Fraction::operator+=(const Fraction &obj){

	int num, denom;

	num = myNumerator*(obj.denominator()) + myDenominator*(obj.numerator()); //do fraction addition
	denom = myDenominator*(obj.denominator());

	myNumerator = num; //update attributes
	myDenominator = denom;

	simplify(myNumerator, myDenominator); //normalize fractions

	return *this; //return pointer to attributes
}


//Comparison equality
bool Fraction::operator==(const Fraction& obj) const{
	//check if LHS is equal to RHS
	if(myNumerator == obj.numerator() && myDenominator == obj.denominator() ){
		return true;
	}
	else{
		return false;
	}
}

//Comparison inequality
bool Fraction::operator!=(const Fraction& obj) const{
	if(myNumerator != obj.numerator() || myDenominator != obj.denominator() ){
		return true;
	}
	else{
		return false;
	}
}


//Comparison- LHS is greater than RHS
bool Fraction::operator>(const Fraction& obj) const{
	//if LHS denominator is larger than RHS, LHS is definitely larger
	if(myDenominator > obj.denominator()){
		return true;
	}
	//if denominators are same and LHS numerator is larger, LHS is greater
	else if(myDenominator == obj.denominator() && myNumerator > obj.numerator()){
		return true;
	}
	else{
		return false;
	}
}

//Comparison- LHS is greater or equal to the RHS
bool Fraction::operator>=(const Fraction& obj) const{
	//first check if equal
	if(myNumerator == obj.numerator() && myDenominator == obj.denominator() ){
		return true;
	}
	//if not equal, check if LHS is grater than RHS
	else if(myDenominator > obj.denominator()){
		return true;
	}
	else if(myDenominator == obj.denominator() && myNumerator > obj.numerator()){
		return true;
	}
	else{
		return false;
	}
}


//Comparison- LHS less than RHS
bool Fraction::operator<(const Fraction& obj) const{
	if(myDenominator < obj.denominator()){
		return true;
	}
	else if(myDenominator == obj.denominator() && myNumerator < obj.numerator()){
		return true;
	}
	else{
		return false;
	}
}

//LHS fraction is less than or equal to the RHS
bool Fraction::operator<=(const Fraction& obj) const{
	if(myNumerator == obj.numerator() && myDenominator == obj.denominator() ){
		return true;
	}
	else if(myDenominator < obj.denominator()){
		return true;
	}
	else if(myDenominator == obj.denominator() && myNumerator < obj.numerator()){
		return true;
	}
	else{
		return false;
	}
}

//Comparison: Fraction& type on LHS and integer on the RHS
//greater than
bool operator>(const Fraction& obj, const int number){
	Fraction myFraction(number, 1); //create a fraction type with the integer parameter as numerator for comparison

	if(obj.denominator() > myFraction.denominator()){
		return true;
	}

	else if(myFraction.denominator() == obj.denominator() && myFraction.numerator() > obj.numerator()){
		return true;
	}
	else{
		return false;
	}

}

//Comparison: integer on the LHS and Fraction& type on RHS
//less than comparison
bool operator<(const int number, const Fraction& obj){
	Fraction myFraction(number, 1);

	if(obj.denominator() > myFraction.denominator()){
		return true;
	}

	else if(myFraction.denominator() == obj.denominator() && myFraction.numerator() > obj.numerator()){
		return true;
	}
	else{
		return false;
	}

}



//Getting user input
istream& operator>>(istream &in, Fraction& obj){

	obj.myNumerator = 1; //initialize the numerator and denominator to 1
	obj.myDenominator = 1; // to clear the previous inputs for continual functionality

	in >> obj.myNumerator; //get the numerator to initialize
	int nextPos = in.peek(); //get the next input from the user
								//to check if user has inputed whole number or fraction

	if(in && nextPos == '/'){	//if the next input is '/' then user has entered fraction
		in.get();				//use get() to extract the slash from the stream
		in >> obj.myDenominator;	//the next input after the slash is extracted is the denominator

		if(obj.myDenominator == 0){		//check if the denominator inputted is 0, throw
			throw FractionException();
		}

	}

	return in;

}




//Output to the console

ostream& operator<<(ostream& out, const Fraction& obj){
	out << obj.numerator() << "/" << obj.denominator();
	return out;
}
