from BigNumber import *
from ctypes import *
# msvcrt = cdll.LoadLibrary("C:\WINDOWS\system32\msvcrt.dll")  # 等同于msvcrt = ctypes.cdll.msvcrt
#msvcrt = cdll.msvcrt      # 导入C动态链接库
def TestBigInt():
    a = BigInt("1")
    b = BigInt("2")
    c = a + b
    print("{} + {} = {}".format(a.toString(),b.toString(),c.toString()))
    
def TestBaseCal1():
    num1 = BigFloat("112233445566778899.02468")
    num2 = BigFloat("123456789.13579")
    r1 = num1 + num2
    r2 = num1 - num2
    r3 = num1 * num2
    r4 = num1 / num2
    print("{} + {} = {}".format(num1.toString(),num2.toString(),r1.toString()))
    print("{} - {} = {}".format(num1.toString(),num2.toString(),r2.toString()))
    print("{} * {} = {}".format(num1.toString(),num2.toString(),r3.toString()))
    print("{} / {} = {}".format(num1.toString(),num2.toString(),r4.toString()))


def TestSqrt():
    num1 = BigFloat("2.1")
    r1 = num1.Power(0.5)
    a1 = BigFloat("2.1")
    a2 = BigFloat("3.2")
    r2 = a1.Power(a1,a2);
    print("sqrt {}   = {}".format(num1.toString(),r1.toString()))
    print("pow {} {}  = {}".format(a1.toString(),a2.toString(),r2.toString()))
    
if __name__ == '__main__':
    TestBaseCal1()
    TestSqrt()
    TestBigInt()
    


