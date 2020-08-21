
#include <iostream>
#include "BigInt.h"
#include "BigFloat.h"

using namespace std;

//copy constructor
BigInt::BigInt(const BigInt& cpySrc)
{
	mIsPlus = cpySrc.mIsPlus;
	mIntPart = cpySrc.mIntPart;
}

BigInt::BigInt(string strNumber)
{
    parserNumber(strNumber);
}

BigInt::BigInt(char* strPtr)
{
    parserNumber(string(strPtr));
}
BigInt::BigInt(vector<char> intPart,int isPlus)
{
    mIsPlus = isPlus;
    for (int i = 0; i < intPart.size(); i++)
        mIntPart.push_back(intPart[i]);
}
BigInt::~BigInt()
{
}

int BigInt::parserNumber(string strNumber)
{
       int haveSym = 0;
		
        if (strNumber[0] == '-') {
            mIsPlus = 0;
            haveSym = 1;
        } else if (strNumber[0] == '+'){
            haveSym = 1;
            mIsPlus = 1;
        }else{
            haveSym = 0;
            mIsPlus = 1;
		}

        int i = 0;
        for (i = haveSym; i < strNumber.length(); i++) {
            mIntPart.push_back(BigInt::CharToInt(strNumber[i]));
        }
        RemoveStartZero(mIntPart);
        if (mIntPart.size() == 0)
            mIntPart.push_back(0);
		return 0;
}
int BigInt::validateNumber(string strNumber)
{
    #if 0
    regex e("[^\\d\\.\\+-]");
    smatch sm; 
    regex_search(strNumber, sm, e); 
    if(sm.size()>0)
        //"含有非法字符"
        return 0;
    }
    smatch sm1;
    regex e("\\d");
    regex_search(strNumber, sm1, e); 
    if(sm1.size()>0)
        //"至少要含有一个数字"
        return 0;
    }
    regex e("[\\+-]");
    smatch sm2;
    regex_search(strNumber, sm2, e,regex_constants::match_not_bol); 
    if(sm2.size()>0)
        //"正负号只能在开头"
        return 0;
    }
    smatch sm3;
    regex e("[\\.]");
    regex_search(strNumber, sm3, e); 
    if(sm3.size()>1)
        //"不能有一个以上的小数点"
        return 0;
    }else if (sm.size() == 1 && (sm3[i]  == strNumber.length() - 1)){
        //小数点不能在开头或最后一位
        return 0;
    }
    smatch sm4;
    regex e("[\\+-]\\.");
    regex_search(strNumber, sm4, e); 
    if(sm4.size()>0)
        //"正负号后不能直接有小数点"
        return 0;
    }
    #endif
    return 1;
}
string BigInt::toString() 
{
   RemoveStartZero(mIntPart);
   string strNumber;
   if(mIsPlus == 0){
   		strNumber += "-";
   }
   for (int i = 0; i < mIntPart.size(); i++) {
	   strNumber += BigInt::IntToChar(mIntPart[i]);
   }
   return strNumber;
}
void BigInt::dumpVector(vector<char> one)
{
	for(int i = 0; i < one.size(); i++){
		cout<<IntToChar(one[i]);
	}
	cout<<endl;
}

int BigInt::compareTo(BigInt other)
{
    if(mIsPlus > 0){
        if(other.mIsPlus<=0){
            return 1;
        }
    }else{
        if(other.mIsPlus>0){
            return -1;
        }
    }
    //same symbol
    int cmpRet = 0;
    if(mIntPart.size()>other.mIntPart.size()){
		if(mIsPlus){
			cmpRet = 1;
		}else{
			cmpRet = -1;
		}
		return cmpRet;
	}else if(mIntPart.size() < other.mIntPart.size()){
		if(mIsPlus){
			cmpRet = -1;
		}else{
			cmpRet = 1;
		}
		return cmpRet;
	}
	
	for (int i = 0; i < mIntPart.size(); i++){
		if(mIntPart[i] > other.mIntPart[i]){
			if(mIsPlus){
				cmpRet = 1;
			}else{
				cmpRet = -1;
			}
			return cmpRet;
		}else if(mIntPart[i] < other.mIntPart[i]){
			if(mIsPlus){
				cmpRet = -1;
			}else{
				cmpRet = 1;
			}
			return cmpRet;
		}
	}
    return cmpRet;
    
}
BigInt BigInt::AbsoluteNumber()
{
    return BigInt(mIntPart,1);
}
BigInt BigInt::ReverseNumber() 
{
	return BigInt(mIntPart, !mIsPlus); 
}
void BigInt::RemoveStartZero(vector<char> &one)
{
	while(one.size()>0){
		if(one[0] == 0){
			one.erase(one.begin());
		}else{
			break;
		}
	}
}

BigInt BigInt::Zero() 
{
		vector<char> intlist;
		intlist.push_back(0);
		return  BigInt(intlist, true);
}
int BigInt::IsZero()
{
	for (int i = 0; i < mIntPart.size(); i++) {
		if (mIntPart[i] != 0)
			return 0;
	}
	return 1;
}

BigInt BigInt::Add(BigInt one, BigInt two) 
{
    BigInt oneAbsolute = one.AbsoluteNumber();
    BigInt twoAbsolute = two.AbsoluteNumber();
    //正数加正数
    if (one.mIsPlus && two.mIsPlus) {
        return PlusAdd(one, two);
    }
        //正数加负数
    else if (one.mIsPlus && !two.mIsPlus) {
       return Minus(oneAbsolute, twoAbsolute);
    }
        //负数加正数
    else if (!one.mIsPlus && two.mIsPlus) {
        return Minus(two, one);
    }
        //负数加负数
    else if (!one.mIsPlus && !two.mIsPlus) {
        BigInt result = PlusAdd(one.AbsoluteNumber(), two.AbsoluteNumber());
        return  BigInt(result.mIntPart, false);
    }
    
}
//两个正数的相加
BigInt BigInt::PlusAdd(BigInt one, BigInt two) 
{
    vector<char> intPart;
    int intAdd = 0;
    intPart = IntAdd(one.mIntPart, two.mIntPart, intAdd);
    return BigInt(intPart, 1);
} 
vector<char> BigInt::IntAdd(vector<char> one, vector<char> two, int& intAdd) 
{
    //RemoveStartZero(one);
    //RemoveStartZero(two);
    if (one.size() >= two.size())
        return IntAddBigAddSmall(one, two, intAdd);
    return IntAddBigAddSmall(two, one, intAdd);
}
/// <summary>整数部分相加，one的长度比two长</summary>
vector<char> BigInt::IntAddBigAddSmall(vector<char> one, vector<char> two, int& intAdd) 
{
    vector<char> result;
    int oneResult = 0;

    for (int i = 0; i < one.size(); i++)
        result.push_back(one[i]);
    
    result[result.size() - 1] += intAdd;

    for (int i = 0; i < result.size(); i++) {
        if (i > two.size() - 1) {
            oneResult = result[result.size() - 1 - i];
        } else {
            oneResult = result[result.size() - 1 - i] + two[two.size() - 1 - i];
        }
        result[result.size() - 1 - i] = oneResult % BigInt::OneMax;
        if (oneResult > BigInt::OneMax - 1) {
            if (i != result.size() - 1) {
                result[result.size() - 2 - i]++;
            } else {
                result.insert( result.begin(),1);
            }
        }
    }
    return result;
}
/// <summary>减</summary>
BigInt BigInt::Minus(BigInt one, BigInt two) 
{
    BigInt oneAbsolute = one.AbsoluteNumber();
    BigInt twoAbsolute = two.AbsoluteNumber();
    //正数减正数
    if (one.mIsPlus && two.mIsPlus) {
        if (oneAbsolute.compareTo(twoAbsolute) == 1)
            return PlusMinus(one, two);
        else if (oneAbsolute.compareTo(twoAbsolute) == -1)
            return PlusMinus(two, one).ReverseNumber();
        else
            return BigInt::Zero();
    }
    //正数减负数
    else if (one.mIsPlus && !two.mIsPlus) {
        return PlusAdd(oneAbsolute, twoAbsolute);
    }
        //负数减正数
    else if (!one.mIsPlus && two.mIsPlus) {
        return PlusAdd(oneAbsolute, twoAbsolute).ReverseNumber();
    }
        //负数减负数
    else if (!one.mIsPlus && !two.mIsPlus) {
        return Add(one, twoAbsolute);
    }
}

/// <summary>两正数相减，并且one大于two</summary>
BigInt BigInt::PlusMinus(BigInt one, BigInt two) {
    int minusInt = 0;
    vector<char> intPart  ;

    intPart = IntMinus(one.mIntPart, two.mIntPart, minusInt);
    return  BigInt(intPart, true);
}

/// <summary>整数部分相减,one所在的数大，two所在的数小</summary>
vector<char> BigInt::IntMinus(vector<char> one, vector<char> two)
{
    return IntMinus(one, two, 0);
}
/// <summary>整数部分相减,one所在的数大，two所在的数小</summary>
vector<char> BigInt::IntMinus(vector<char> one, vector<char> two, int Minus) 
{
    RemoveStartZero(one);
    RemoveStartZero(two);
    vector<char> result;
    int oneResult;
    if (one.size() == 0){
		result.push_back(0);			
        return result;
    }
	
    for (int i = 0; i < one.size(); i++)
        result.push_back(one[i]);
	
    for (int i = 0; i < two.size(); i++) {
        oneResult = result[result.size() - 1 - i] - two[two.size() - 1 - i];
        if (oneResult < 0) {
            result[result.size() - 1 - i] = oneResult + BigInt::OneMax;
            result[result.size() - 2 - i]--;
        } else {
            result[result.size() - 1 - i] = oneResult;
        }
    }
    return result;
}

/// <summary> 乘  </summary>
BigInt BigInt::Multiply(BigInt one, BigInt two) 
{
	vector<char> oneText(one.mIntPart);
	vector<char> twoText(two.mIntPart);
	
	vector<char> resultText = Multiply(oneText, twoText);
    
	return BigInt(resultText,  !(one.mIsPlus ^ two.mIsPlus));
}
vector<char> BigInt::Multiply(vector<char>one, vector<char>two)
{
	//result是用倒序来存储，最后再反序 Yes
	 vector<char> result;
	 //每位数相乘的暂时结果
	 int oneResult = 0;
	 //这个用于进位
	 int AddResult = 0;
	 for (int j = 0; j < two.size(); j++) {
		 for (int i = 0; i < one.size(); i++) {
			 oneResult = one[one.size() - 1 - i] * two[two.size() - 1 - j] + AddResult;
			 AddResult = oneResult / BigInt::OneMax;
	
			 if (result.size() == i + j) {
				 result.push_back(oneResult % BigInt::OneMax);
			 } else {
				 result[i + j] += oneResult % BigInt::OneMax;
				 if (result[i + j] > BigInt::OneMax - 1) {
					 result[i + j] = result[i + j] % BigInt::OneMax;
					 AddResult++;
				 }
			 }
			 if (i == one.size() - 1 && AddResult != 0) {
				 result.push_back(AddResult);
				 AddResult = 0;
			 }
		 }
	 }
	 std::reverse(result.begin(),result.end());
	return result;
}
/// <summary>除</summary>
BigFloat BigInt::Division(BigInt one, BigInt two, int precision) 
{
	vector<char> oneInt(one.mIntPart);
	vector<char> twoText(two.mIntPart);
	RemoveStartZero(twoText);

	vector<char> resultInt;
	vector<char> resultDecimal;

	int index = twoText.size() < oneInt.size() ? twoText.size() - 1 : oneInt.size() - 1;
	vector<char> div(oneInt.begin(), oneInt.begin()+index + 1);
	//正数部分的除法
	int quotient = 0;
	vector<char> quotientVec;
	while (true) {
		quotient = Division(div, twoText);
		resultInt.push_back(quotient);
		quotientVec.clear();
		quotientVec.push_back(quotient);
		vector<char> mulVec =  Multiply(twoText, quotientVec);
		div = IntMinus(div, mulVec, 0);
		//dumpVector(div);
		index++;
		if (index >= oneInt.size() ){
			break;
		}
		div.push_back(oneInt[index]);
	}
	index = 0;
	//小数部分的除法
	while (true) {
		//满足精度后退出
		if (resultDecimal.size() >= precision)
			break;

		div.push_back(0);
		quotient = Division(div, twoText);
		resultDecimal.push_back(quotient);
		
		quotientVec.clear();
		quotientVec.push_back(quotient);
		vector<char> mulVec =  Multiply(twoText, quotientVec);

		div = IntMinus(div, mulVec, 0);
		index++;
	}
	return BigFloat(resultInt, resultDecimal, !(one.mIsPlus ^ two.mIsPlus));
}
/// <summary>两个List int的除法，只进行一次运算one的位数不会大于two</summary>	 
int BigInt::Division(vector<char> one, vector<char> two) 
{
	 RemoveStartZero(one);
	 RemoveStartZero(two);

	 //dumpVector(one);
	 //dumpVector(two);

	 if (two.size() > one.size()) {
		 return 0;
	 }
	 //用于一次除法的数
	 //List<int> divisioned = one.GetRange( 0, two.Count );
	 //int index = two.Count;
	 //while ( true )
	 //{
	 int i = BigInt::OneMax / 2;  //进行试商的数
	 int low = 0;
	 int top = BigInt::OneMax - 1;
	 //结果连1都大了	 
	 vector<char> quotientVec;
	 quotientVec.push_back(1);
	 if (CompareList(Multiply(two,quotientVec), one) == 1) {
		 return 0;
	 }
	 //如果连9都小了
	 quotientVec.clear();
	 quotientVec.push_back(BigInt::OneMax - 1);
	 if (CompareList(Multiply(two, quotientVec), one) == -1) {
		 return BigInt::OneMax - 1;
	 }
	 while (true) {
		 quotientVec.clear();
		 quotientVec.push_back(i);
		 int c = CompareList(Multiply(two,quotientVec), one);
		 //商小了
		 if (c == -1) {
			 low = i;
			 i = (low + top) / 2;  //这里不可能越界
		 }
			 //商大了
		 else if (c == 1) {
			 top = i;
			 i = (low + top) / 2;
		 }
			 //刚好用这个商除法可以除尽
		 else {
			 return i;
		 }
		 //已找到合适的商
		 if (low + 1 == top) {
			 return low;
		 }
	 }
 }
 /// <summary>比较两个用List表示的大小</summary>
int BigInt::CompareList(vector<char> one, vector<char> two)
{
	 RemoveStartZero(one);
	 RemoveStartZero(two);
	 if (one.size() > two.size())
		 return 1;
	 else if (one.size() < two.size())
		 return -1;
	 else {
		 for (int i = 0; i < one.size(); i++) {
			 if (one[i] > two[i])
				 return 1;
			 else if (one[i] < two[i])
				 return -1;
		 }
		 return 0;
	 }

 }

 //operator overload
BigInt BigInt::operator+(const BigInt& two)
{
	return Add(*this,two);
}
BigInt BigInt::operator-(const BigInt& two)
{
	return Minus(*this,two);
}
BigInt BigInt::operator*(const BigInt& two)
{
	return Multiply(*this,two);
}
BigFloat BigInt::operator/(const BigInt& two)
{
	return Division(*this,two);
}
//suffix ++ --
BigInt& BigInt::operator++(int)
{	
	BigInt ret(*this);//拷贝构造函数，构造复制品
	BigInt one("1");
	*this = Add(*this,one);
	return ret;
	//return Add(*this, one);
}
BigInt& BigInt::operator--(int)
{
	BigInt ret(*this);//拷贝构造函数，构造复制品
	BigInt one("1");
	*this = Minus(*this,one);
	return ret;
}
//prefix ++ --
BigInt& BigInt::operator++()
{
	BigInt one("1");
	*this = Add(*this,one);
	return *this;
}
BigInt& BigInt::operator--()
{
	BigInt one("1");
	*this = Minus(*this,one);
	return *this;
}

BigInt BigInt::PowerInt(BigInt value, BigInt intPow)
{
	BigInt resIntPower("1");
	BigInt valZero("0");
	BigInt valOne("1");
	while(intPow.compareTo(valZero)>=1){
		resIntPower = resIntPower*value;
		intPow--;
	}
	return resIntPower;

}
BigInt BigInt::Power(BigInt pow) 
{
	return PowerInt(*this,pow);
}
BigInt BigInt::Power(BigInt value, BigInt pow)
{
	return PowerInt(value,pow);
}
BigInt BigInt::Power(int pow)
{
	BigInt power(to_string(pow));
	RemoveStartZero(power.mIntPart);
	return Power(*this, power);

}
BigFloat BigInt::Power(float pow)
{
	BigFloat power(to_string(pow));
	power.RemoveStartEndZero();
	BigFloat bigVal(*this);
	return bigVal.Power(power);
}
BigFloat BigInt::Power(double pow)
{
	BigFloat power(to_string(pow));
	power.RemoveStartEndZero();
	BigFloat bigVal(*this);
	return bigVal.Power(power);
}
BigFloat BigInt::Power(BigFloat pow)
{
	pow.RemoveStartEndZero();
	BigFloat bigVal(*this);
	return bigVal.Power(pow);
}
BigFloat BigInt::Power(BigInt value, BigFloat pow)
{
	pow.RemoveStartEndZero();
	BigFloat bigVal(value);
	return bigVal.Power(pow);
}
