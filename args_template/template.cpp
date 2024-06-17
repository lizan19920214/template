/**
 * 可变参数模板
 * 一个可变参数模板指的是一个接受可变数目参数的函数模板或类模板，其中可变数目的参数被称为参数包。存在两种参数包：

● 模板参数包：零个或多个模板参数
● 函数参数包：零个或多个函数参数


*/
#include <iostream>
#include <string>
using namespace std;


//展开参数包方式1:递归
//递归终止函数
template<typename T>
void display(const T& t)
{
    cout << "进入普通函数" << t <<endl;
}
//展开函数
template <typename T, typename ... Args>
void display(T t, Args ... args)
{
    //错误的写法：
    //函数模板不能被调用，函数模板需要在编译时根据传入的实参类型进行推演，生成对应的函数，这是在编译时进行的，
    //而if判断是在运行时才走的逻辑，也就是运行时逻辑，所以不能在运行时进行函数模板的调用。
    // if (sizeof .. (args) == 0)
    // {
    //     return;
    // }
    
    cout << "进入模板函数" << t << " size = " << sizeof ... (args) << endl;
    //当...位于args右边的时候，叫做解包
    display(args ...);
}


void test1()
{
    string s1 = "hello";
    display(1);
    display(1, 2.2);
    display(1, 2.2, s1);
}

/**
 * 展开参数包方式2：逗号表达式展开
 * 如下PrintArg1为逗号表达式展开方式：
 * 首先我们不能使用如下样式来展开参数包，因为c++数组只允许一种类型，而参数包可能包含多种类型
 * int arr[] = { args... };
 * 1、逗号表达式会从左到右一次计算各个表达式的值，并将最后一个表达式的值作为返回值返回
 * 2、我们将最后一个表达式设置为整型值，确保逗号表达式返回的是一个整型值
 * 3、将处理参数包的动作封装成一个函数，并将函数调用作为逗号表达式的第一个表达式
 * 如下:
 * 	int arr[] = { (PrintArg(args), 0)... };
 * 注意：
 * 可变参的省略号需要放在逗号表达式的外面，表示需要将逗号表达式展开
 * 代码中的{(PrintArg(args), 0)...}将会展开成{(PrintArg(arg1), 0), (PrintArg(arg2), 0), (PrintArg(arg3), 0), etc...}。
 * 这里我们还是用到了一个c++11的特性——初始化列表{},通过初始化列表来初始化一个变成数组
 * {(printarg(args), 0)...}将会展开成((printarg(arg1),0),(printarg(arg2),0),(printarg(arg3),0), etc... )，
 * 最终会创建一个元素值都为0的数组int arr[sizeof...(Args)]。
 * */

template <typename T>
void PrintArg1(T t)
{
    cout << "1参数是:" <<  t << endl;
}

/**
 * 我们也可以不使用逗号表达式，直接使用
 * 	int arr[] = { PrintArg(args)... };
 * 按照如下进行展开调用
 * 	int arr[] = { printarg(arg1),printarg(arg2),printarg(arg3), etc... };
 * */
template <typename T>
int PrintArg2(const T& t)
{
    cout << "2参数是:" <<  t << endl;
    return 0;
}

//展开函数
template <typename ... Args>
void ShowList(Args ... args)
{
    int arr1[] = {(PrintArg1(args), 0) ...};
    int arr2[] = { PrintArg2(args) ...};
    
    for(auto i : arr1)
    {
        cout << "i1 = " << i << endl;
    }
    for(auto i : arr2)
    {
        cout << "i2 = " << i << endl;
    }

    cout << endl;
}

void test2()
{
    ShowList(1, 2, "hello");
}

int main()
{
    // test1();
    test2();
    return 0;
}