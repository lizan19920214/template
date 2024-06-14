/**
 * g++ -o template template.cpp
 * 一个函数模板就是一个公式，用于生成针对类型的函数版本。模板定义以一个关键字template开始，
 * 后跟一个模板参数列表（逗号分隔的一个或多个模板参数的列表）。
 * 
*/
#include <iostream>
using namespace std;

//比较大小
template<typename T>
int compare(const T& t1, const T& t2)
{
    if (t1 < t2)
    {
        return -1;
    }
    else if (t1 > t2)
    {
        return 1;
    }

    return 0;
}

void CompareValue()
{
    int a = 10;
    int b = 20;
    int c = 20;

    cout << compare(a, b) << endl;
    cout << compare(b, a) << endl;
    cout << compare(b, c) << endl;
}

//函数模板显式实参
/**
 * 由于T1没有任何函数实参可以推断出其类型，因此调用sum必须显式为T1指明模板实参
 * 需要注意的是显式模板实参按从左到右的顺序与对应的模板参数匹配，只有尾部（最右）
 * 参数的显式模板实参才可以忽略，前提是他们可以从函数参数推断出来
*/
template<typename T1, typename T2, typename T3>
T1 sum(const T2& v1, const T3& v2) {return v1 + v2;}

//下面这种是糟糕的设计，需要指定三个模板函数
// template<typename T1, typename T2, typename T3>
// T3 sum(const T1& v1, const T2& v2) {return v1 + v2;}
// auto result = sum<long, int, long>(i, lng);


void SumValue()
{
    int i = 10;
    long lng = 100;
    auto result = sum<long>(i, lng);
    cout << "SumValue " << result << endl;
}

int main()
{
    CompareValue();
    SumValue();
    return 0;
}