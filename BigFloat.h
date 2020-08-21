#ifndef _BIG_FLOAT_H_
#define _BIG_FLOAT_H_

#include <vector>
#include <string>
#include <regex>
#include <cmath>

using namespace std;
class BigInt;

class BigFloat {
public:
    //Constructors
    BigFloat(const BigFloat& cpySrc);
    BigFloat(string strNumber="");
    BigFloat(char* strPtr);
    BigFloat(vector<char> intPart,vector<char> realPart,int isPlus);
	BigFloat(BigInt bigIntVal);
    ~BigFloat();

	
	friend BigInt;
	
    BigFloat AbsoluteNumber();
	BigFloat ReverseNumber();
	static BigFloat Zero() ;
    //Assignment operators
    //Operations
    //friend BigFloat operator+(const BigFloat& left_, const BigFloat& right_);

	
	int IsZero();    
    string toString();
    int compareTo(BigFloat other);
//private:
    //static const int OneCount=4;
    static const int OneMax = 10;
    int validateNumber(string strNumber);
    int parserNumber(string strNumber);
	//Transformations int<-->char single digit
	inline static int  CharToInt(const char& val) { return (val - '0'); };
	inline static char IntToChar(const int& val) { return (val + '0'); };
	void RemoveStartEndZero();
	void RemoveStartZero(vector<char> &one);
	void dumpVector(vector<char> one);

	int GetPrecision(int value);
	/// <summary>保留小数点后n位</summary>
    void KeepPrecision(int n);

    BigFloat Add(BigFloat one, BigFloat two);
    BigFloat PlusAdd(BigFloat one, BigFloat two) ;
    vector<char> IntAdd(vector<char> one, vector<char> two, int& intAdd);
    vector<char> IntAddBigAddSmall(vector<char> one, vector<char> two, int& intAdd);
    vector<char> DecimalAdd(vector<char> one, vector<char> two, int& intAdd);

	BigFloat Minus(BigFloat one, BigFloat two);
	BigFloat PlusMinus(BigFloat one, BigFloat two);
	vector<char> DecimalMinus(vector<char> one, vector<char> two, int& intMinus);
	vector<char> IntMinus(vector<char> one, vector<char> two);
	vector<char> IntMinus(vector<char> one, vector<char> two, int Minus);

	BigFloat Multiply(BigFloat one, BigFloat two);
	vector<char> Multiply(vector<char>oneText, vector<char>twoText);

	BigFloat Division(BigFloat one, BigFloat two);
	BigFloat Division(BigFloat one, BigFloat two, int precision);
	int      Division(vector<char> one, vector<char> two) ;
	int      CompareList(vector<char> one, vector<char> two);

	//operator overload
	BigFloat operator+(const BigFloat& two);
	BigFloat operator-(const BigFloat& two);
	BigFloat operator*(const BigFloat& two);
	BigFloat operator/(const BigFloat& two);
	//suffix ++ --
	// 括号中插入 int 表示后缀
	BigFloat& operator++(int);
	BigFloat& operator--(int);
	//prefix ++ --
	BigFloat& operator++();
	BigFloat& operator--();

	//power
	BigFloat PowerInt(BigFloat value, BigFloat intPow);
	BigFloat Power(BigFloat value, BigFloat pow, int precision) ;
	BigFloat Power(BigFloat bigNumber, BigFloat pow) ;
	BigFloat Power(BigFloat bigNumber, int pow) ;
	BigFloat Power(BigFloat bigNumber, float pow) ;
	BigFloat Power(BigFloat pow) ;
	BigFloat Power(int pow) ;
	BigFloat Power(float pow) ;
	BigFloat Power(double pow) ;
	
private:
    int       mIsPlus;
    vector<char> mIntPart;
    vector<char> mRealPart;
};
#endif //_BIG_FLOAT_H_
