// Cocos2d-x中那些常用的C++11新特性
//马三小伙儿 2016.09.16

#include "stdafx.h"
#include <iostream>
#include <initializer_list>
#include <vector>
#include <memory>
#include <functional>
using namespace std;

//类使用初始化列表
class ClassA{
public:
	ClassA(std::initializer_list<int>list){}
};

//函数使用初始化列表
void func(std::initializer_list<float>list){
	/*Function Body*/
}

//标准容器使用初始化列表
vector<string> s = {"hello","C++","11"};



C::C()
{
}

C::~C()
{
}
int _tmain(int argc, _TCHAR* argv[])
{
	/*初始化列表*/
	ClassA a = { 1, 2, 3 };
	func({1.6f,2.8f});

	/*自动类型推导*/
	vector<int> v;
	vector<int>::iterator it=v.begin();		//使用类型推导前
	auto it2 = v.begin();					//使用类型推导后
	int num;
	decltype(num) b = 5;

	/*自动范围推导*/
	for (int i = 0; i < 10; i++){			//使用自动范围推导前
		cout << i << endl;
	}
	int arr []= { 1, 2, 3, 4, 5 };
	for (int &i : arr){
		cout << i << endl;
	}

	/*智能指针和空指针*/
	//智能指针只能被智能指针赋值，不能用shared_ptr<int> pq= new int;
	shared_ptr<int> p1(new int);
	//用{ }进入一个新的作用域
	{
		//新的智能指针指向p1，这是相当于对int内存块的一次retain
		shared_ptr<int> p2 = p1;
		*p2 = 123;
		//p2被销毁，相当于对int内存块的一次release，但是由于p1还指向该内存，引用计数器不为0，因此不会释放
	}

	/*Lambda表达式*/
	int b, c, d;
	auto func0 = [&]()->void {b = 1; c = 2; d = 3; };
	auto func1 = [=]()->int {return 2 * 3; };
	auto func2 = [=, &b, &c]()->void {++b; c += d + b; };
	auto func3 = [=]()->int {return b + d; };

	func0();	//b,c,d分别为1，2，3
	c=func1();	//c=6
	func2();	//b=2;c=858993456,d=6;
	b = func3();//b=1717986916
	
	function<void()> f1 = func0;
	function<int()>f2 = func1;

	ClassA *obj = new ClassA();
	function<void(int)> f2 = bind(&ClassA::memberFunc1,obj,std::placeholders::_1);
	function<void(int, char)>f3 = bind(&ClassA::memberFunc2,obj,std::placeholders::_2);
	return 0;
	//p1也被销毁，此时引用计数为0，int所占用的内存被自动回收

	/*注意！使用shared_ptr需要include <memory>*/
}

