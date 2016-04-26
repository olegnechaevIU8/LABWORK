//#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Rational
{
private:
    int num, den; // den is unsigned
public:
    Rational(int num_, int den_) //Конструктор класса
	{
		this->num = num_; // список инициализаторов
		this->den = den_;
		// проверить на ноль? сократить?
	}
	
	~Rational() {}
	
	//Перегрузка операторов >> и <<
	friend ostream& operator<< (ostream& , Rational const&);
    friend istream& operator>> (istream& , Rational&);
    
	//Перегрузка операторов + и -
	friend Rational const operator+ (Rational const&, Rational const&);
    friend Rational const operator* (Rational const&, Rational const&);   

};
 
int Euclid(int a, int b) 
	{
        while(b) b^=a^=b^=a%=b;
        return a;
    }

Rational const operator+ (Rational const& L, Rational const& R)
{
    int a,b,c;
	a = L.num * R.den + R.num * L.den;
	b = L.den * R.den;
	c = Euclid(a,b); // лучше бы это делал конструктор
	return Rational(a/c, b/c);
}
 
Rational const operator* (Rational const& L, Rational const& R)
{
    int a,b,c;
	a = L.num * R.num;
	b = L.den * R.den;
	c = Euclid(a,b);
	return Rational(a/c, b/c);
}

ostream& operator<<(ostream& ost, Rational const& rat)
{
    return ost << "[" << rat.num << '/' << rat.den << "]";
}
 
istream& operator>>(istream& ist, Rational& r) 
{
	string rational;
	ist >> rational;
	auto d = find(rational.begin(), rational.end(), '/');
	if(rational.front() != '[' || rational.back() != ']' || d == rational.end())
		throw runtime_error("Bad input");
	*d = ' ';
	string tmp(rational.begin()+1, --(rational.end()));
	stringstream ss;
	ss << tmp;
	ss >> r.num >> r.den;
	return ist;
}



int main()
{
    cout << "\n Test1 - rational numbers \n";
	Rational rat1(1,1), rat2(1,1), rat3(1,1);
	cin >> rat1 >> rat2 >> rat3;
	cout << "\nRational N1 : " << rat1 << "\nRational N2 : " << rat2 << "\nRational N3 : " << rat3;
    cout << "\n Rational N1 * Rational N2 = " << rat1*rat2;
	cout << "\n Rational N2 + Rational N3 = " << rat2+rat3;

	cout << "\n Test2 - matrix \n";

   
	system ("pause");
    return 0;
}

