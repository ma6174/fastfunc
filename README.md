# fastfunc

python某些模块效率较低，可能会成为整个程序的瓶颈，
用C重写某些模块可以大大提高程序执行效率。
本类库目前实现了两个功能：

- url unquote 解码
- url get参数转字典

后续遇到性能问题会不断添加


### 安装：

```shell
git clone git@github.com:ma6174/fastfunc.git
cd fastfunc
sudo python setup.py install
```

### 使用：

```python
>>> import fastfunc
>>> fastfunc.parseurl("a=1&bb=22&ccc=333")
{'a': '1', 'ccc': '333', 'bb': '22'}
>>> fastfunc.unquote("name%20%3D%20%7Ea%2B3")
'name = ~a+3'
>>> 
```
