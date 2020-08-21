#include "BigFloat.h"
#include <iostream>
using namespace std;

/// <summary>计算value^pow</summary>
BigFloat BigFloat::PowerInt(BigFloat value, BigFloat intPow) 
{
	BigFloat resIntPower("1");
	BigFloat valZero("0");
	BigFloat valOne("1");
	//cout<<"PowerInt "<<intPow.toString()<<endl;
	while(intPow.compareTo(valZero)>=1){
		resIntPower = resIntPower*value;
		//intPow = intPow - valOne;
		intPow--;
		//cout<<"PowerInt "<<intPow.toString()<<endl;
	}
	return resIntPower;
}


BigFloat BigFloat::Power(BigFloat value, BigFloat pow, int precision) 
{
	if (pow.mRealPart.size() != 0 && !value.mIsPlus)  { //第一个条件是小数次幂，第二个条件是负数
		//throw new ExpressionException("只有正数才有小数次幂");
		cout <<"error 1 "<<endl;
		return BigFloat("");
	}
	//calc int power
	int i = 0;
	BigFloat resIntPower("1");
	BigFloat valZero("0");
	if(pow.mIntPart.size()>0){
		BigFloat intPower(pow.mIntPart,vector<char>(),1);
		resIntPower = PowerInt(value,intPower);
		//cout<<resIntPower.toString()<<endl;
	}
	//calc real power newton interation
	BigFloat resRealPower("1");
	BigFloat valOne("1");
	BigFloat x0("1");
	BigFloat x("1");
	if(pow.mRealPart.size()>0){
		string val="1";
		string strPrecision="0.";

		for(int i = 0; i < pow.mRealPart.size(); i++){
			val.append("0");
			strPrecision.append("0");
		}
		strPrecision[strPrecision.length()]='1';
		
		BigFloat bigPrec(strPrecision.c_str());
		
		BigFloat denominator(val.c_str()); 
		BigFloat denominatorLess1 = denominator - valOne; 
		BigFloat numerator(pow.mRealPart,vector<char>(),1);
		//cout<<"denominator " << denominator.toString()<<endl;
		//cout<<"denominatorLess1 " << denominatorLess1.toString()<<endl;
		//cout<<"numerator " << numerator.toString()<<endl;
		//cout<<"bigPrec " << bigPrec.toString()<<endl;
		
		BigFloat valA = PowerInt(value,numerator);
		//cout<<"valA " << valA.toString()<<endl;
		//newton method
		BigFloat x0PowerLess1 = PowerInt(x0,denominatorLess1);
		//cout<<"x0PowerLess1 " << x0PowerLess1.toString()<<endl;

		//BigFloat x0Power = x0PowerLess1*x0;
		//cout<<"x0Power " << x0Power.toString()<<endl;
		
		x = x0;
		//cout<<"x0 " << x.toString()<<endl;
		x = x0/denominator;
		//cout<<"x2 " << x.toString()<<endl;
		x = x + valA/x0PowerLess1/denominator;
		//cout<<"x1 " << x.toString()<<endl;
		//cout<<"x0 " << x0.toString()<<endl;
		x.KeepPrecision(4);
		while((x-x0).AbsoluteNumber().compareTo(bigPrec) > 0){
			//cout<<"x " << x.toString()<<endl;
			//cout<<"x0 " << x0.toString()<<endl;

			x0 = x;
			x0PowerLess1 = PowerInt(x0,denominatorLess1);
			x = x0 - x0/denominator + valA/denominator/x0PowerLess1;
			x.KeepPrecision(4);
		}
		
	}
	//cout<<resIntPower.toString()<<endl;
	//cout<<x.toString()<<endl;
	return resIntPower*x;
}

BigFloat BigFloat::Power(BigFloat bigNumber, BigFloat pow) 
{
	return Power(bigNumber, pow, bigNumber.mRealPart.size() + 1);
}
BigFloat BigFloat::Power(BigFloat bigNumber, int pow) 
{
	BigFloat power(to_string(pow));
	power.RemoveStartEndZero();
	return Power(bigNumber, power);
}
BigFloat BigFloat::Power(BigFloat bigNumber, float pow) 
{
	BigFloat power(to_string(pow));
	power.RemoveStartEndZero();
	return Power(bigNumber, power);
}
BigFloat BigFloat::Power(BigFloat pow)
{
	return Power(*this, pow);
}

BigFloat BigFloat::Power(int pow)
{
	BigFloat power(to_string(pow));
	power.RemoveStartEndZero();
	return Power(*this, power);
}
BigFloat BigFloat::Power(float pow)
{
	BigFloat power(to_string(pow));
	power.RemoveStartEndZero();
	return Power(*this, power);
}
BigFloat BigFloat::Power(double pow)
{
	BigFloat power(to_string(pow));
	power.RemoveStartEndZero();
	return Power(*this, power);
}

