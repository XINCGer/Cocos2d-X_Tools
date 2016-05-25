#Lua基础学习
1.数值与类型  
Lua是动态弱类型语言，变量不要类型定义也可以使用。  
nil-->空  boolean-->布尔  number-->数值类型  string-->字符串类型  
userdata--> 自定义类型  function-->函数类型  thread-->线程类型  
table-->表类型。  
Tips:使用type函数可以获得变量的类型，table类似于数组或者容器，它可以存储多个对象，但是表更为灵活。  
表类型实现了一个关联数组，换句话来说，数组可以用任何东西做索引，而不仅限于数字。（nil不能作为表的索引和表的对象）  
同时，表是Lua中唯一的一种数据结构，它可以用来描述原始的数组、符号表、集合、记录、图、树等。因为采用同一种语法，  
开发者可以通过a.name或者a["name"]来访问表中的对象。  

2.Lua关键保留字  
and break do else elseif end false for function if in local nil not or repeat return then true until while  
单行注释： “__”  多行注释： "--[[  --]]"  --[[ print(10)--]]  

3.表达式
Lua的表达式与其他语言类似，lua中比较特别的是，在表达式中可以包含非函数定义和表构造，这正是其两个特殊的数据类型。  
逻辑运算符认为除了nil 和 false 之外，其他数值都是true，这其中也包括了“0”。and,or并不会返回一个真或假的数值，而  
是返回两个操作数变量。 “a and b”如果a为真，则返回b,否则返回a。"a or b"如果a为假，则返回b，否则返回a。not的结果  
只能返回true或者false。  
举例：  
print(4 and 5)-->5   print(nil and 13)-->nil  print(false and 13)-->false  print(4 or 5)-->4  
print(false or 5)-->5  print(not nil)-->true  print(not false)-->true  print(not 0)-->false  
print(not no nil)-->false  
C语言中的三元运算符a?b:c 在lua中实现的方式为(a and b)or c  
在Lua中还有一个特别的构造运算符，其实在其他语言中也存在。它就是大括号表示的"{}"，在C++和Java中被称为数组，而在Lua中则是表类型。  
构造器是创建和初始化表的表达式，开发者使用它可以直接创建空表，也可以初始化表。  
days={"a","b","c"}  
print(days[1]) -->a  
表类型数值下标是从“1”开始计算的，不推荐数组下标从0开始，否则很多标准库不能使用。   

4.语句  
多重赋值：a,b=10,2*x; --等价于 a=10;b=2*x;  
--进行交换变量的值  
x,y = y,x;  
当变量个数

