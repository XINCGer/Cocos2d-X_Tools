##Cocos2d-x开发中那些不得不了解的C++11知识
自从Cocos2d-x3.0开始，Cocos2dx就正式的使用了C++11标准.C++11简洁方便的特性使程序的可拓展性和可维护性大大提高，也提高了代码的书写速度。

　　下面我们就来一起学习一下Cocos2d-x开发中那些不得不了解的C++11知识。

 1.初始化列表

　　POD结构或者数组根据成员在结构内定义的顺序，可以使用初始化列表来进行初始化以简化代码。

　　　

struct StructA{
    int a;
    int b;
};

StructA sa={1,2};
　　在C++03中，非POD结构的类或者STL容器并不支持这种简便的写法，而C++11提供了强大的支持。使用std::initializer_list可以让类和普通函数使用初始化列表，并且STL容器也是可以使用初始化列表，代码如下：

复制代码
//类使用初始化列表
class ClassA{
public:
    ClassA(std::initializer_list<int>list){}
};

ClassA a = { 1, 2, 3 };

/*注意！使用std::initializer_list需要先include <initializer_list>头文件*/
复制代码
复制代码
//函数使用初始化列表
void func(std::initializer_list<float>list){
    /*Function Body*/
}

func({1.6f,2.8f});

/*注意！使用std::initializer_list需要先include <initializer_list>头文件*/
复制代码
//STL标准容器使用初始化列表
vector<string> s = {"hello","C++","11"};
　　可以看到在引入了std::initializer_list特性之后，初始化变量的工作简洁了许多，非常方便。

 2.自动类型推导

　　类型推导可以在编译的时候自动来识别对象的类型，从而简化代码，更好的使用模版编程，使用auto关键字即可自动推导类型明确的变量，例如：

　　

    /*自动类型推导*/
    vector<int> v;
    vector<int>::iterator it=v.begin();        //使用类型推导前
    auto it2 = v.begin();                    //使用类型推导后
　　decltype也可以根据已有的对象自动识别类型，但是它和auto的不同之处是：auto是自动推导出表达式右边的类型，而decltype是自动推导出任意一个变量的类型，并且可以用该类型来定义变量，说起来比较难理解，看下面的代码就一目了然了：

　　

    int num;
    decltype(num) b = 5;
 3.自动范围推导

　　在C++11以前，写一个循环语句通常是这样的：

　　

    for (int i = 0; i < 10; i++){            //使用自动范围推导前
        cout << i << endl;
    }
　　而在C++11中，for语句新增了范围迭代的写法，该写法可以简化for循环的代码，“：”符号左边是要编历的元素类型，可以是引用或者const引用类型；而“：”右边是要编历的容器可以是数组或者STL容器等，代码如下：

　　

    int arr []= { 1, 2, 3, 4, 5 };　　　　　　//使用自动范围推导后
    for (int &i : arr){
        cout << i << endl;
    }
  4.智能指针和空指针

　　智能指针是一个类而并非是普通的指针，shared_ptr是一引用计数指针，一个shared_ptr只有在已经没有任何其他shared_ptr指向其原本所指向的对象时，才会销毁该对象。

　　除了shared_ptr之外，还有weak_ptr，但是weak_ptr并不拥有其所指向的对象，因此不影响该对象的销毁与否，也不能对weak_ptr解引用，只能判断该指针是否已经被销毁。下面举个例子说明一下shared_ptr:

　　

复制代码
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

    return 0;
    //p1也被销毁，此时引用计数为0，int所占用的内存被自动回收

    /*注意！使用shared_ptr需要include <memory>*/
复制代码
　　如果将share_ptr定义为类的成员变量，那么此智能指针的retain引用会在该对象被释放的时候才释放。

　　空指针nullptr的存在是为了解决NULL的二义性问题，因为NULL也可以代表0，nullptr的类型为nullptr_t，能隐式转换为任何指针或者是成员指针的类型，也能和它们进行相等或者不等的比较。而nullptr不能隐式转换为整数，也不能和整数做比较。

　　

    void foo(char *);
    void foo(int);
    foo(NULL);        //调用的是void foo(int);
    foo(nullptr);    void foo(char *);
5.Lambda特性

　　lambda表达式是一个非常好的新特性，当你需要在程序中添加一个新的临时函数时，直接使用Lambda函数，会让你感觉到原来写程序还可以这么爽~（类似于Java中的 匿名内部类）。lambda的写法如下：

　　

[函数外部对象参数] (函数参数) -> 返回值类型{ 函数体}
　　(1)[ ]中的函数外部对象参数，允许在函数体内直接调用函数外部的参数；

　　(2)( )中的参数，同正常函数的参数没有什么差异，是每次函数调用时传入的变量；

　　(3)->后面跟着函数返回值的类型；

　　(4){ }里面可以编写逻辑函数，并使用[ ]和( )传入的参数

　　定义在lambda函数相同作用域的参数引用也可以被使用，这种参数集合一般被称为闭包，[ ]中可以填写下面的几种类型的参数，将定义lambda函数作用域内的变量传入函数体中。

　　1.[ ]可以没有任何参数，这种情况下不传入外部参数

　　2.[a,&b]传入变量a的值以及变量b的引用

　　3.[&]以引用的方式传入所有的变量

　　4.[=]以传值的方式传入所有的变量，值不可以被修改

　　5.[&,a]除了a用传值的方式，其他变量都已引用的方式传入

　　6.[=,&a]除了a用引用的方式传入，其他变量都以传值的方式传入

　　下面让我们通过一个例子来了解一下，当在lambda中使用了“=”传入的参数，且对引用参数或者外部参数进行赋值操作之后，会产生意想不到的结果，并且还需注意在使用“&”时需要注意引用对象的生命周期。

　　

复制代码
    /*Lambda表达式*/
    int b, c, d;
    auto func0 = [&]()->void {b = 1; c = 2; d = 3; };
    auto func1 = [=]()->int {return 2 * 3; };
    auto func2 = [=, &b, &c]()->void {++b; c += d + b; };
    auto func3 = [=]()->int {return b + d; };

    func0();    //b,c,d分别为1，2，3
    c=func1();    //c=6
    func2();    //b=2;c=858993456,d=6;
    b = func3();//b=1717986916
    return 0;
复制代码
　　当Lambda被定义在类的成员函数中时，Lambda可以调用该类的private函数；当Lambda调用该类的成员函数时，操作成员变量或者其他成员函数时，需要将this传入，=和&会传入this。

　　使用std::function可以存储Lambda函数，比如可以用function<void()>来存储func0,用function<int()>来存储func1,带有参数的函数可以直接在()内输入参数类型，在使用function时要包含头文件functional。

　　

    #include <functional>
    function<void()> f1 = func0;
    function<int()>f2 = func1;    
　　function还可以用于存放普通函数，静态函数和类的公有成员函数，前两者和lambda的用法一样，直接将函数名赋值给function对象即可（无法识别重载的函数），但类的成员函数需要使用bind来绑定：

　　

    ClassA *obj = new ClassA();
    function<void(int)> f2 = bind(&ClassA::memberFunc1,obj,std::placeholders::_1);
    function<void(int, char)>f3 = bind(&ClassA::memberFunc2,obj,std::placeholders::_2);
　　使用bind函数绑定成员函数和对象指针，使用std::placeholders占位符来表示函数的参数数量，其后缀依次从1~N。

6.显式虚函数重载

　　override可以确保在重写父类的虚函数，调整父类的虚函数时（改名字或者参数），不会忘记调整子类的虚函数。在编译时，编译器会为标记为override的虚函数检查其父类是否有该虚函数：

复制代码
class B{
public:
    virtual void virtuaalFunc(int);
};

class C{
public:
    virtual void virtuaalFunc(int) override;    //显示重写父类虚函数
    virtual void virtuaalFunc(char) override;    //错误
};
复制代码
　　final可以保证子类不能重写函数，不能具有相同签名的函数，或者类不能被继承。（类似于Java中final用法）override和final并不是C++11的关键字，只是在特定的位置才有特殊的含义，在其他地方仍然是当作变量来用的。

 

