/**
 * 类模板
 * 函数模板建议用 typename 描述通用数据类型，类模板建议用 class。
 * 类模板的语法：
 * template <class 类型参数名>
 * class 类模板名
 * {
 *     // 类模板的具体实现
 * }
 * 
 * 与函数模板的区别：
 * 1、类模板一般情况下无法自动类型推导的调用方式
 * 2、类模板在模板参数列表中可以有默认参数
 * template<class T = 数据类型>
 * 3、类模板在有默认参数类型的时候，可以发生隐式类型转换
 * 
 * 与其他类相同，我们既可以在类模板内部也可以在类模板外部为其定义成员函数，且定义在类模板内的成员函数
 * 被隐式声明为内联函数。但定义在类模板外部的成员函数必须以关键字template开始，后接类模板参数列表
 * template <typename T>
 * ret-type Foo<T>::member-name(parm-list)
*/

//以栈的实现为例
#include <iostream>
using namespace std;

class Item;

template<class T>
class Stack
{
public:
    Stack(int size) : stackSize(size), top(0)
    {
        items = new T[size];
    }

    ~Stack()
    {
        delete[] items;
    }

    //判断是否为空
    const bool isEmpty()
    {
        return top == 0;
    }

    //判断是否满栈
    const bool isFull()
    {
        return top == stackSize;
    }

    //入栈
    bool push(const T& item)
    {
        if (isFull())
        {
            return false;
        }

        items[top++] = item;
        return true;
    }

    //出栈
    T pop()
    {
        T t = items[--top];
        return t;
    }

private:
    T* items; //栈数组
    int stackSize; //栈大小
    int top; //栈顶指针

};

class Item
{
public:
    Item()
    {
    }

    void SetId(int id)
    {
        m_id = id;
        cout << " Item: " << m_id << endl;
    }

    void print()
    {
        cout << " print: " << m_id << endl;
    }
    
private:
    int m_id;
};

template<class T1, class T2>
class Pair
{
public:
    //关键字
    T1 key;
    //值
    T2 value;
    Pair(T1 k, T2 v) : key(k), value(v){}
    bool operator < (const Pair<T1, T2>& p) const;
};

//类模板成员函数类外实现的固定格式
// template<模板参数...>
//返回值 模板名<模板参数...>::成员函数名(形参列表)
template<class T1, class T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2>& p) const
{
    cout << "my value:" << this->value << " other value:" << p.value << endl;
    return this->value < p.value;
}

int main()
{
    Stack<Item> stack(10);
    for (int i = 0; i < 10; i++)
    {
        Item item;
        item.SetId(i + 1);
        stack.push(item);
    }

    while (!stack.isEmpty())
    {
        Item item = stack.pop();
        item.print();
    }

    cout << endl;

    Pair<string, int> student1("Tom", 20);
    Pair<string, int> student2("Jack", 18);
    Pair<string, int> student3("jeff", 22);
    cout << student1.key << " " << student1.value << endl;
    cout << student2.key << " " << student2.value << endl;
    cout << student3.key << " " << student3.value << endl;


    bool result = student1 < student2;
    cout << result << endl;

    result = student1 < student3;
    cout << result << endl;


    return 0;
}