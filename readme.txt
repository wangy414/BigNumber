在做生态数据分析时，遇到超大矩阵。需要求解各个属性的相关性系数。
由于矩阵太大，在求解矩阵均值时，数据过大超出了数据的表示范围，
导致无法正常求解。

    参照相关解决方案实现了基于字符串方式表示浮点数和整数的方法，
实现数的相关数算运算。
1、C++支持编译
支持cmake和VC++编译
1.1 在linux下面，使用cmake进行编译
1.2 在windows下，在vcbuild下面打开BigNumber.vcxproj
用vs2015进行编译

2 python支持
需要安装swigwin-4.0.2

使用swig进行python的包装
swig -python -c++ BigNumber.i
使用python setup.py进行编译
python setup.py build_ext --inplace

使用进行测试验证python接口
python test.py
