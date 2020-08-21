#include <iostream>
#include "BigFloat.h"

using namespace std;

void TestBaseCal1() {
	 BigFloat num1("112233445566778899.02468");
	 BigFloat num2 ("123456789.13579");
	 BigFloat r1 = num1 + num2;
	 BigFloat r2 = num1 - num2;
	 BigFloat r3 = num1 * num2;
	 BigFloat r4 = num1 / num2;
	 cout <<num1.toString()<<" + "<<num2.toString()<<" = "<<r1.toString()<< endl;
	 cout <<num1.toString()<<" - "<<num2.toString()<<" = "<<r2.toString()<< endl;
	 cout <<num1.toString()<<" * "<<num2.toString()<<" = "<<r3.toString()<< endl;
	 cout <<num1.toString()<<" / "<<num2.toString()<<" = "<<r4.toString()<< endl;
}
void TestSqrt()
 {
  BigFloat num1 ("2.1");
  BigFloat r1 = num1.Power(0.5);
 
  BigFloat a1 ("2.1");
  BigFloat a2 ("3.2");
  BigFloat r2 = a1.Power(a1,a2);
 
 cout <<"sqrt " << num1.toString() <<" = " + r1.toString()<<endl;
 cout <<"pow "<<  a1.toString() <<  ", " <<  a2.toString() << " = " <<  r2.toString()<<endl;

}

int main()
{
    cout<<"hello"<<endl;
	//BigFloat num1("1");
	//BigFloat num2 ("10");
	//BigFloat r4 = num1 / num2;
	//cout <<num1.toString()<<" / "<<num2.toString()<<" = "<<r4.toString()<< endl;

	//TestBaseCal1();
	TestSqrt();
    return 0;
}
