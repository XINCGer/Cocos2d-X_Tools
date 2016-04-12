#Coco2dx常见问题及解决方案：

##说明
>* `无法解析的外部符号（或命令）`   
(1) 头文件声明了函数，但是在CPP文件中却没有实现该函数，并且在程序中的某个位置调用了这个函数。  
(2) 没有添加链接库，比如Extensions或者CocoStudio库等等  

>* `C++lambda表达式`   
C++的lamdba表达式和Java的匿名内部类很相似，它是一个匿名内部函数，一个最简单的lamdba函数如下：\[] () {}    
它只有三对符号和一个分号，分别得作用是：
* []符号，表示要开始一个lamdba函数;  
* ()符号，里面填写函数的参数;  
* {}符号，和所有的{}作用一样，用来包括函数体的内容;  
在[]符号里面加入指定的符号就能指定变量捕获模式，常见的变量捕获模式如下：  
* []不截取任何变量
* [&]截取外部作用域中的所有变量，并作为引用在lamdba函数中使用，可以简单的理解为只要变量没有被释放，  
那么在lamdba函数中都可以使用，但是局部变量不可以使用，因为局部变量会被释放;  
* [=]截取外部作用域中的所有变量，并复制一份在lamdba函数中使用，即使外部变量的值改变了，但是在lamdba  
函数执行的时候，依旧是复制时的值;  
* [=,&hehe]和[=]功能一样，但是对hehe变量使用引用，（也就是[&]的方式）;  
* [hehe]和[=]功能一样，但是只针对hehe变量，其他变量忽略;  

>* `调用可变参数函数时，总是莫名报错`  
Sequence::create(actionBy,actionByBack,NULL);  
Sequence的create函数的参数是可变参数，也就是说，我们可以给create()函数传入3个参数，  
也可以传入5个参数，这都是可变的。但是，不管我们传入多少个参数，都不要忘了，最后一  
个参数必须为NULL，否则我们会被莫名的函数报错所困扰。 

>* `如何同一时间，生成不同的随机数`  
IOS : arc4random()%100  
Android:srand(time(NULL));   random();  
```c++```
#include <random>
std::uniform_int_distribution<unsigned> u(1,1000);
std::default_random_engine e;
e.seed((unsigned)time(NULL));
int random_number = u(e);
```
>* `如何在一定范围内，产生K数量不同的随机数`
在网上能找到几种实现方法，这里只记录下认为比较高效的做法
用数组 A[] 存放x到y的数值，然后在(x,y)产生第一个随机数H做为下标，    从数组A中取出A[H]，然后将数组最后个元素赋值给A[H]，再重新在（x,y-1）产生，如些循环
具体代码实现
```c++```
int quantity = 12;
    int start = 0;
    int end = 36;
    int total = abs(end - start);
    if (quantity >total) {
        CCLog("随机数错误");
    }
    int sequence[total];  //存放随机数的数组
    int output[quantity]; //最终生成的不重复一系列随机数
    
    //将sequence 初始化
    for (int i = 0; i < total; i++) {
        sequence[i] = start+i;
    }
    
    //随机数种子
    cc_timeval psv;
    CCTime::gettimeofdayCocos2d(&psv, NULL);
    unsigned long int seed = psv.tv_sec*1000 + psv.tv_usec/1000;
    srand(seed);
    
    for (int i = 0; i < quantity; i++) {
        int num = this->random(0, end - 1);//在指定范围下产生随机数
        output[i] = sequence[num];//将产生的随机数存储
        sequence[num] = sequence[end-1];//将最后个下标的值填充到随机产生的下标中
        end--;//在指定范围 向前移
    }
```


