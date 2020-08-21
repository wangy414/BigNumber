#!/usr/bin/env python

"""
setup.py file for SWIG C\+\+/Python example
"""
from distutils.core import setup, Extension
BigNumber_module = Extension('_BigNumber',
sources=['BigFloat.cpp', 'BigFloatPowerCalc.cpp','BigInt.cpp','BigNumber_wrap.cxx'],
)
setup (name = 'BigNumber',
version = '0.1',
author = "wy",
description = """BigNumber swig C\+\+/Python BigNumber""",
ext_modules = [BigNumber_module],
py_modules = ["BigNumber"],
)