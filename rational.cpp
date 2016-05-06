#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Rational
{
	public:
	int num, den;
	Rational()
	{
		num = 0;
		den = 0;
	}
	
	Rational(int num_, int den_) //Rationalnie chisla
	{
		this->num = num_;
		this->den = den_;
	}

	void print()
	{
		cout << num << "/" << den << " ";
	}

	~Rational() {}

	//Peregruzka operatorov >> i <<
	friend ostream& operator<< (ostream&, Rational const&);
	friend istream& operator>> (istream&, Rational&);

	//Peregruzka operatorov + i -
	friend Rational const operator+ (Rational const&, Rational const&);
	friend Rational const operator* (Rational const&, Rational const&);

};

int Euclid(int a, int b)
{
	while (b) b ^= a ^= b ^= a %= b;
	return a;
}

Rational const operator+ (Rational const& L, Rational const& R)
{
	int a, b, c;
	a = L.num * R.den + R.num * L.den;
	b = L.den * R.den;
	c = Euclid(a, b);
	return Rational(a / c, b / c);
}

Rational const operator* (Rational const& L, Rational const& R)
{
	int a, b, c;
	a = L.num * R.num;
	b = L.den * R.den;
	c = Euclid(a, b);
	return Rational(a / c, b / c);
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
	if (rational.front() != '[' || rational.back() != ']' || d == rational.end())
		throw runtime_error("Bad input");
	*d = ' ';
	string tmp(rational.begin() + 1, --(rational.end()));
	stringstream ss;
	ss << tmp;
	ss >> r.num >> r.den;
	return ist;
}

class matrix {
	Rational** T;
	int M;
	int N;
public:
	matrix(int m, int n) : T(NULL), M(m), N(n)
	{
		T = new Rational*[M];
		for (int i = 0; i < M; i++)
		{
			T[i] = new Rational[N];
			for (int j = 0; j < N; j++)
				T[i][j] = Rational();
		}
	}
	Rational& operator () (int i, int j)
	{
		return T[i][j];
	}

	void print()
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
				T[i][j].print();
			cout << endl;
		}
		cout << endl << endl;
	}
	matrix & operator &()
	{
		matrix U(N, M);

		for (int i = 0; i<N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				U(i, j) = T[j][i];
			}
		}
		return U;
	}
	matrix  operator *(int a)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
				T[i][j].num = T[i][j].num*a;
		}
		matrix U(M, N);

		for (int i = 0; i<M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				U(i, j) = T[i][j];
			}
		}
		return U;
	}
	~matrix()
	{

	}

};


int main()
{
	cout << "\n Test1 - rational numbers \n";
	cout << "\n Vvedite 3 drobi v formate [NUM/DEN] \n";
	Rational rat1(1, 1), rat2(1, 1), rat3(1, 1);
	cin >> rat1 >> rat2 >> rat3;
	cout << "\nRational N1 : " << rat1 << "\nRational N2 : " << rat2 << "\nRational N3 : " << rat3;
	cout << "\n Rational N1 * Rational N2 = " << rat1*rat2;
	cout << "\n Rational N2 + Rational N3 = " << rat2 + rat3;

	cout << "\n Test2 - matrix \n"; 
	int n = 5;
	Rational  *r; r = new Rational[n + 2];
	matrix M(5, 6);

	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			r[i].num = i + 1;
			r[i].den = j + 1;
			M(i, j) = r[i];
		}
	}
	
	cout << "Nachalnaya matrica: \n";
	M.print();
	
	cout << "Umnozhenie na chislo = 5: \n";
	M = M * 5;
	M.print();
	
	cout << "Transponirovanie: \n";
	M = &M;
	M.print();
	
	system("pause");
	return 0;
}

