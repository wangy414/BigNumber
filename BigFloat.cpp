
#include <iostream>
#include "BigFloat.h"
#include "BigInt.h"

using namespace std;

//copy constructor
BigFloat::BigFloat(const BigFloat& cpySrc)
{
	mIsPlus = cpySrc.mIsPlus;
	mIntPart = cpySrc.mIntPart;
	mRealPart = cpySrc.mRealPart;
	//copy(cpySrc.mIntPart.begin(),cpySrc.mIntPart.end(),mIntPart.begin());
	//copy(cpySrc.mRealPart.begin(),cpySrc.mRealPart.end(),mRealPart.begin());
}

BigFloat::BigFloat(string strNumber)
{
    //int ret = validateNumber(strNumber);
    parserNumber(strNumber);
    //string strVal = toString();
    //cout<<strVal<<endl;
}

BigFloat::BigFloat(char* strPtr)
{
    parserNumber(string(strPtr));
}
BigFloat::BigFloat(vector<char> intPart,vector<char> realPart,int isPlus)
{
    mIsPlus = isPlus;
    for (int i = 0; i < intPart.size(); i++)
        mIntPart.push_back(intPart[i]);
    
    for (int i = 0; i < realPart.size(); i++)
        mRealPart.push_back(realPart[i]);
}
BigFloat::BigFloat(BigInt bigIntVal)
{
	mIsPlus = bigIntVal.mIsPlus;
	mIntPart = bigIntVal.mIntPart;
}

BigFloat::~BigFloat()
{
}

int BigFloat::parserNumber(string strNumber)
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
        int pointIndex = strNumber.find_first_of('.');
        //有小数点
        if (pointIndex != -1) {
            int i = 0;
            for (i = haveSym; i < pointIndex; i++) {
                mIntPart.push_back(BigFloat::CharToInt(strNumber[i]));
            }
            i = pointIndex + 1;
            while (i < strNumber.length()) {
                mRealPart.push_back(BigFloat::CharToInt(strNumber[i]));
                i ++;
            }

        }
        //没有小数点
        else {
            int i = 0;
            for (i = haveSym; i < strNumber.length(); i++) {
                mIntPart.push_back(BigFloat::CharToInt(strNumber[i]));
            }
        }
        //BigCalculate.RemoveStartZero(mIntPart);
        if (mIntPart.size() == 0)
            mIntPart.push_back(0);

		//cout<<"parserNumber "<<strNumber<< " mIsPlus "<<mIsPlus<<endl;
		return 0;
}
int BigFloat::validateNumber(string strNumber)
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
string BigFloat::toString() 
{
   RemoveStartEndZero();
   string strNumber;
   if(mIsPlus == 0){
   		strNumber += "-";
   }
   for (int i = 0; i < mIntPart.size(); i++) {
	   strNumber += BigFloat::IntToChar(mIntPart[i]);
   }
   if(mRealPart.size()>0){
   	strNumber += ".";
   }
   for (int i = 0; i < mRealPart.size(); i++) {
	   strNumber += BigFloat::IntToChar(mRealPart[i]);
   }
   if(strNumber.length()==0)
	   	strNumber += "0";
   return strNumber;
}
void BigFloat::dumpVector(vector<char> one)
{
	for(int i = 0; i < one.size(); i++){
		cout<<IntToChar(one[i]);
	}
	cout<<endl;
}

int BigFloat::compareTo(BigFloat other)
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
	//int part is equal
	for (int i = 0; i < mRealPart.size(); i++){
		if(mRealPart[i] > other.mRealPart[i]){
			if(mIsPlus){
				cmpRet = 1;
			}else{
				cmpRet = -1;
			}
			return cmpRet;
		}else if(mRealPart[i] < other.mRealPart[i]){
			if(mIsPlus){
				cmpRet = -1;
			}else{
				cmpRet = 1;
			}
			return cmpRet;
		}
	} 
	//real part are also equal
    return cmpRet;
    
}
BigFloat BigFloat::AbsoluteNumber()
{
    return BigFloat(mIntPart,mRealPart,1);
}
BigFloat BigFloat::ReverseNumber() 
{
	return BigFloat(mIntPart, mRealPart, !mIsPlus); 
}
void BigFloat::RemoveStartZero(vector<char> &one)
{
	while(one.size()>0){
		if(one[0] == 0){
			one.erase(one.begin());
		}else{
			break;
		}
	}
}

void BigFloat::RemoveStartEndZero()
{
	//remove start 0
	vector<char>::iterator iter;
	vector<char>::iterator iter2;
	/*for(iter=mIntPart.begin(); iter!=mIntPart.end(); ){
		//cout <<BigFloat::IntToChar(*iter)<<endl;
		 if( *iter == 0){
		 	  //iter2 = iter + 1 ;
			  iter = mIntPart.erase(iter);
	   		  //iter = iter2;
		  }else{
			  break;
		  }
	}
	*/
	while(mIntPart.size()>0){
		if(mIntPart[0] == 0){
			mIntPart.erase(mIntPart.begin());
		}else{
			break;
		}
	}

	if(mIntPart.size()==0){
		mIntPart.push_back(0);
	}
	//remove end 0
	while(mRealPart.size()>0){
		if(mRealPart[mRealPart.size() - 1] == 0){
			mRealPart.erase(mRealPart.begin() + mRealPart.size() - 1);
		}else{
			break;
		}
	}

}

BigFloat BigFloat::Zero() 
{
		vector<char> intlist;
		vector<char> decimallist;
		intlist.push_back(0);
		return  BigFloat(intlist, decimallist, true);
}
int BigFloat::IsZero()
{
	for (int i = 0; i < mIntPart.size(); i++) {
		if (mIntPart[i] != 0)
			return 0;
	}
	for (int i = 0; i < mRealPart.size(); i++) {
		if (mRealPart[i] != 0)
			return 0;
	}

	return 1;
}


/// <summary>加</summary>
BigFloat BigFloat::Add(BigFloat one, BigFloat two) 
{
    BigFloat oneAbsolute = one.AbsoluteNumber();
    BigFloat twoAbsolute = two.AbsoluteNumber();
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
        BigFloat result = PlusAdd(one.AbsoluteNumber(), two.AbsoluteNumber());
        return  BigFloat(result.mIntPart, result.mRealPart, false);
    }
    
}
//两个正数的相加
BigFloat BigFloat::PlusAdd(BigFloat one, BigFloat two) 
{
    vector<char> intPart;
    vector<char> decimalPare;
    int intAdd = 0;

    //将两数的小数部分相加
    if (one.mRealPart.size() >= two.mRealPart.size())
        decimalPare = DecimalAdd(one.mRealPart, two.mRealPart, intAdd);
    else
        decimalPare = DecimalAdd(two.mRealPart, one.mRealPart, intAdd);

    //将两数的正数部分相加
    //if ( one.IntPart.Count >= two.IntPart.Count )
    //    intPart = IntAddBigAddSmall( one.IntPart, two.IntPart, intAdd );
    //else
    //    intPart = IntAddBigAddSmall( two.IntPart, one.IntPart, intAdd );
    intPart = IntAdd(one.mIntPart, two.mIntPart, intAdd);
    return BigFloat(intPart, decimalPare, 1);
} 
vector<char> BigFloat::IntAdd(vector<char> one, vector<char> two, int& intAdd) 
{
    //RemoveStartZero(one);
    //RemoveStartZero(two);
    if (one.size() >= two.size())
        return IntAddBigAddSmall(one, two, intAdd);
    return IntAddBigAddSmall(two, one, intAdd);
}
/// <summary>整数部分相加，one的长度比two长</summary>
vector<char> BigFloat::IntAddBigAddSmall(vector<char> one, vector<char> two, int& intAdd) 
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
        result[result.size() - 1 - i] = oneResult % BigFloat::OneMax;
        if (oneResult > BigFloat::OneMax - 1) {
            if (i != result.size() - 1) {
                result[result.size() - 2 - i]++;
            } else {
                result.insert( result.begin(),1);
            }
        }
    }
    return result;
}

//小数部分相加 ,one的长度比two长
vector<char> BigFloat::DecimalAdd(vector<char> one, vector<char> two, int& intAdd)
{
    vector<char> result;
    int oneResult = 0;
    for (int i = 0; i < one.size(); i++)
        result.push_back(one[i]);

    for (int i = two.size() - 1; i >= 0; i--) {
        oneResult = result[i] + two[i];
        result[i] = (int)(oneResult % BigFloat::OneMax);
        if (oneResult > BigFloat::OneMax - 1) {
            if (i != 0)
                result[i - 1]++;
            else
                //进位到整数部分
                intAdd = 1;
        }
    }
    return result;
}
/// <summary>减</summary>
BigFloat BigFloat::Minus(BigFloat one, BigFloat two) 
{
    BigFloat oneAbsolute = one.AbsoluteNumber();
    BigFloat twoAbsolute = two.AbsoluteNumber();
    //正数减正数
    if (one.mIsPlus && two.mIsPlus) {
        if (oneAbsolute.compareTo(twoAbsolute) == 1)
            return PlusMinus(one, two);
        else if (oneAbsolute.compareTo(twoAbsolute) == -1)
            return PlusMinus(two, one).ReverseNumber();
        else
            return BigFloat::Zero();
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
BigFloat BigFloat::PlusMinus(BigFloat one, BigFloat two) {
    int minusInt = 0;
    vector<char> decimalPart ;
    vector<char> intPart  ;
    decimalPart = DecimalMinus(one.mRealPart, two.mRealPart, minusInt);

    intPart = IntMinus(one.mIntPart, two.mIntPart, minusInt);
    return  BigFloat(intPart, decimalPart, true);
}

//小数部分相减,one所在的数大，two所在的数小
vector<char> BigFloat::DecimalMinus(vector<char> one, vector<char> two, int& intMinus) 
{
    int oneResult = 0;
    vector<char> result;
    for (int i = 0; i < one.size(); i++)
        result.push_back(one[i]);

    //将result的长度和two的长度弄成一样
    if (result.size() < two.size()) {
        for (int i = 0; i < two.size() - one.size(); i++)
			result.push_back(0);
    }
    for (int i = two.size() - 1; i >= 0; i--) {
        oneResult = result[i] - two[i];
        if (oneResult < 0) {

            result[i] = (int)(oneResult + BigFloat::OneMax);
            //下面是找高位借数
            //这里是从正数中借
            if (i == 0)
                intMinus = 1;
            //这里中从小数部分的高一位借
            else
                result[i - 1]--;
        } else {
            result[i] = (int)oneResult;
        }
    }
    return result;
}
/// <summary>整数部分相减,one所在的数大，two所在的数小</summary>
vector<char> BigFloat::IntMinus(vector<char> one, vector<char> two)
{
    return IntMinus(one, two, 0);
}
/// <summary>整数部分相减,one所在的数大，two所在的数小</summary>
vector<char> BigFloat::IntMinus(vector<char> one, vector<char> two, int Minus) 
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
	
    result[result.size() - 1] -= Minus;

    for (int i = 0; i < two.size(); i++) {
        oneResult = result[result.size() - 1 - i] - two[two.size() - 1 - i];
        if (oneResult < 0) {
            result[result.size() - 1 - i] = oneResult + BigFloat::OneMax;
            result[result.size() - 2 - i]--;
        } else {
            result[result.size() - 1 - i] = oneResult;
        }
    }
    return result;
}
//Operations
/*BigFloat BigFloat::operator+(const BigFloat& left_, const BigFloat& right_)
{
    
}*/

/// <summary> 乘  </summary>
BigFloat BigFloat::Multiply(BigFloat one, BigFloat two) 
{
	vector<char> oneText(one.mIntPart);
	vector<char> twoText(two.mIntPart);
	//oneText.extend(one.mRealPart);
	//twoText.extend(two.mRealPart);
	oneText.insert(oneText.end(), one.mRealPart.begin(), one.mRealPart.end());
	twoText.insert(twoText.end(), two.mRealPart.begin(), two.mRealPart.end());
	
	vector<char> resultText = Multiply(oneText, twoText);

	int decimalLength = one.mRealPart.size() + two.mRealPart.size();
	vector<char> intPart(resultText.begin(), resultText.begin() + resultText.size() - decimalLength);
	vector<char> decimalPart( resultText.begin() + resultText.size() - decimalLength, resultText.end());
	return BigFloat(intPart, decimalPart, !(one.mIsPlus ^ two.mIsPlus));
}
vector<char> BigFloat::Multiply(vector<char>one, vector<char>two)
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
			 AddResult = oneResult / BigFloat::OneMax;
	
			 if (result.size() == i + j) {
				 result.push_back(oneResult % BigFloat::OneMax);
			 } else {
				 result[i + j] += oneResult % BigFloat::OneMax;
				 if (result[i + j] > BigFloat::OneMax - 1) {
					 result[i + j] = result[i + j] % BigFloat::OneMax;
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
BigFloat BigFloat::Division(BigFloat one, BigFloat two) 
{
	int precision = one.mRealPart.size() > two.mRealPart.size() ?
		            one.mRealPart.size()  : two.mRealPart.size();
	if(precision <= 4){
		precision = 4;
	}
	return Division(one, two, precision);
}

BigFloat BigFloat::Division(BigFloat one, BigFloat two, int precision) 
{
	vector<char> oneInt(one.mIntPart);
	vector<char> oneDecimal(one.mRealPart) ;

	vector<char> twoText(two.mIntPart);
	twoText.insert(twoText.end(), two.mRealPart.begin(), two.mRealPart.end());
	RemoveStartZero(twoText);
	//将15/2.3 移位为 150/23  //DecimalLength
	for (int i = 0; i < two.mRealPart.size(); i++) {
		if (oneDecimal.size() != 0) {
			oneInt.push_back(oneDecimal[0]);
			oneDecimal.erase(oneDecimal.begin());
		} else {
			oneInt.push_back(0);
		}
	}
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
		if (index >= oneDecimal.size())
			div.push_back(0);
		else {
			div.push_back(oneDecimal[index]);
		}
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
int BigFloat::Division(vector<char> one, vector<char> two) 
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
	 int i = BigFloat::OneMax / 2;  //进行试商的数
	 int low = 0;
	 int top = BigFloat::OneMax - 1;
	 //结果连1都大了	 
	 vector<char> quotientVec;
	 quotientVec.push_back(1);
	 if (CompareList(Multiply(two,quotientVec), one) == 1) {
		 return 0;
	 }
	 //如果连9都小了
	 quotientVec.clear();
	 quotientVec.push_back(BigFloat::OneMax - 1);
	 if (CompareList(Multiply(two, quotientVec), one) == -1) {
		 return BigFloat::OneMax - 1;
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
int BigFloat::CompareList(vector<char> one, vector<char> two)
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

int BigFloat::GetPrecision(int value) {
	 if (value == 0) {
		 RemoveStartZero(mIntPart);
		 if (mIntPart.size() == 1 && mIntPart[0] == 0) {
			 if (mRealPart.size() == 0)
				 return 0;
			 for (int i = 0; i < mRealPart.size(); i++) {
				 if (mRealPart[i] != 0)
					 return i;
			 }
			 return mRealPart.size();
		 }
		 return 0;
	 } else {
		 if (mIntPart.size() == 1 && mIntPart[0] == 1) {
			 if (mRealPart.size() == 0)
				 return 0;
			 for (int i = 0; i < mRealPart.size(); i++) {
				 if (mRealPart[i] != 0)
					 return i;
			 }
			 return mRealPart.size();
		 }
		 return 0;
	 }
 }
 /// <summary>保留小数点后n位</summary>
void BigFloat::KeepPrecision(int n) 
{
	 if (mRealPart.size() > n) {
		 //this.DecimalPart.RemoveRange(n, DecimalPart.Count - n);
		while(mRealPart.size()> n){
			mRealPart.erase(mRealPart.begin() + mRealPart.size() - 1);
		}
	 }
 }

 //operator overload
BigFloat BigFloat::operator+(const BigFloat& two)
{
	return Add(*this,two);
}
BigFloat BigFloat::operator-(const BigFloat& two)
{
	return Minus(*this,two);
}
BigFloat BigFloat::operator*(const BigFloat& two)
{
	return Multiply(*this,two);
}
BigFloat BigFloat::operator/(const BigFloat& two)
{
	return Division(*this,two);
}
//suffix ++ --
BigFloat& BigFloat::operator++(int)
{	
	BigFloat ret(*this);//拷贝构造函数，构造复制品
	BigFloat one("1");
	*this = Add(*this,one);
	return ret;
	//return Add(*this, one);
}
BigFloat& BigFloat::operator--(int)
{
	BigFloat ret(*this);//拷贝构造函数，构造复制品
	BigFloat one("1");
	*this = Minus(*this,one);
	return ret;
}
//prefix ++ --
BigFloat& BigFloat::operator++()
{
	BigFloat one("1");
	*this = Add(*this,one);
	return *this;
}
BigFloat& BigFloat::operator--()
{
	BigFloat one("1");
	*this = Minus(*this,one);
	return *this;
}


