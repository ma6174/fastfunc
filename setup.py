#!/usr/bin/env python
# coding=utf-8


from distutils.core import setup, Extension


module1 = Extension('fastfunc', sources=['fastfunc.c'])


setup(
    name='fastfunc',
    version='0.1',
    description='优化部分python模块性能',
    ext_modules=[module1])
