#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <vector>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

class BigFloat;

class BigInt {
public:
    //Constructors
    BigInt(const BigInt& cpySrc);
    BigInt(string strNumber="");
    BigInt(char* strPtr);
    BigInt(vector<char> intPart,int isPlus);
    ~BigInt();

	friend BigFloat;
	
    BigInt AbsoluteNumber();
	BigInt ReverseNumber();
	static BigInt Zero() ;
	
	int IsZero();    
    string toString();
    int compareTo(BigInt other);
//private:
    static const int OneMax = 10;
    int validateNumber(string strNumber);
    int parserNumber(string strNumber);
	//Transformations int<-->char single digit
	inline static int  CharToInt(const char& val) { return (val - '0'); };
	inline static char IntToChar(const int& val) { return (val + '0'); };
	void RemoveStartZero(vector<char> &one);
	void dumpVector(vector<char> one);


    BigInt Add(BigInt one, BigInt two);
    BigInt PlusAdd(BigInt one, BigInt two) ;
    vector<char> IntAdd(vector<char> one, vector<char> two, int& intAdd);
    vector<char> IntAddBigAddSmall(vector<char> one, vector<char> two, int& intAdd);

	BigInt Minus(BigInt one, BigInt two);
	BigInt PlusMinus(BigInt one, BigInt two);
	vector<char> IntMinus(vector<char> one, vector<char> two);
	vector<char> IntMinus(vector<char> one, vector<char> two, int Minus);

	BigInt Multiply(BigInt one, BigInt two);
	vector<char> Multiply(vector<char>oneText, vector<char>twoText);

	BigFloat Division(BigInt one, BigInt two, int precision = 4);
	int      Division(vector<char> one, vector<char> two) ;
	int      CompareList(vector<char> one, vector<char> two);

	//operator overload
	BigInt operator+(const BigInt& two);
	BigInt operator-(const BigInt& two);
	BigInt operator*(const BigInt& two);
	BigFloat operator/(const BigInt& two);
	//suffix ++ --
	// 括号中插入 int 表示后缀
	BigInt& operator++(int);
	BigInt& operator--(int);
	//prefix ++ --
	BigInt& operator++();
	BigInt& operator--();

	//power
	BigInt PowerInt(BigInt value, BigInt intPow);
	BigInt Power(BigInt pow);
	BigInt Power(BigInt value, BigInt pow);
	BigInt Power(int pow);

	BigFloat Power(float pow);
	BigFloat Power(double pow);
	BigFloat Power(BigFloat pow);
	BigFloat Power(BigInt value, BigFloat pow);

	
private:
    int       mIsPlus;
    vector<char> mIntPart;
};
#endif //_BIG_INT_H_
