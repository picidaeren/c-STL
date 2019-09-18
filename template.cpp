#include <iostream>
using  namespace std;
/*模板编程是 STL 的基石，也是 c++11 的核心特性之一。
模板是相对于编译器而言，顾名思义就是向编译器提供一个
处理事务的模板，以后需要处理的东西，如果都是这个事务
类型，那么统统用这个模板处理。
模板的基本语法如下：

template <typename/class T>

template 告诉编译器，接下来是一个模板 ，
typename 和 class 都是关键字，
在这里二者可以互用没有区别。
在< >中 T 叫做模板形参，一旦模板被实例化，
 T 也会变成具体的类型。
*/
/*这是一个模板函数的简单实例，所有模板函数在开始都需要 template 语句，
 * 以告诉编译器这是一个模板和参数等必要信息，当然里面的 T 可以取任意你
 * 喜欢的名字 ，模板参数个数也是任意更换的。 还要提醒的一点是：
 * template <typename T1 ,typename T2 = int>函数模板是支持默认参数的，
 * T1 、T2顺序在默认情况下是可以任意的，不用严格按照从右到左的顺序。*/
template <typename T>
T add(const T a,const T b){
    T c;
    c = a+ b;
    return c;
}

/*c++11 不仅支持对函数的模板化，也支持对类的模板，
 * 下面来看基本的语法是怎样的：*/
template <typename T>
class myClass{
    T a;
public:
    T add(const T val1, const T val2);
};
template <typename T>
T myClass<T>::add(const T val1, const T val2) {
    this.a = val1 + val2;
    return a;
}
/*这是一个简单并且典型的类模板，在程序中给出模板并不能使用它，
 * 还必须实例化，比如：

Myclass<int> A； //用 int 实例化一个类A

Myclass<double> B； //用 double 实例化一个类B

当程序编译到这里时就会按照我们给出的类型，声明两组类和两组类函数。
 注意，在这里我们一定要显式给出类型 T 。类模板不像是函数模板 ，
 函数模板会根据参数推断类型。 当然类模板也支持默认参数，
 但是类模板必须严格从右往左默认化。*/


/*
成员模板
        模板的使用范围是广泛的，不仅可以用作函数模板，类模板，
        还可以用作 class ，struct ，template class 的成员。
        而要实现 STL 这是我们必须掌握和使用的特性。
        我们先看一个简单的例子,用上面的类改编而来：
*/
template <class T>
class Myclass
{
public:
    T a;
    template <typename type_1 , typename type_2>
    type_1 add(const type_1 lva ,const type_2 rva);
};

template <class T>
template <typename type_1,typename type_2>
type_1 Myclass<T>::add(const type_1 lva, const type_2 rva)
{
    a = lva + rva;
    return a;
}
/*
在类的声明中使用了一个嵌套的模板声明。且通过作用域运算符 :: 指出 add
 是类的成员，需要注意的一点，有些编译器不支持模板成员，
 而有些编译器不支持在类外定义。我们默认大家的编译器都支持。
 模板如此强大，甚至允许我们在模板类中再建立模板类：
 */

template <class T>
class Myclass1
{
public:
    T a;
    template <typename type_1 , typename type_2>
    type_1 add(const type_1 lva ,const type_2 rva);

    template <class type_3>
    class Myclass_2;         // 声明放在这里，具体定义放在类外进行。
    Myclass_2<T> C;          // 定义一个Myclass_2 类 A。使用 T 进行实例化
};


template <class T>
template <typename type_1,typename type_2>
type_1 Myclass1<T>::add(const type_1 lva, const type_2 rva) {
    a = lva + rva;
    return a;
}
/*我们知道，在类中定义的静态成员是存储在静态区中，被所有类对象共享，
 * 并不属于某一个类所有，同样的在模板类中的静态成员也不会被复制多份，
 * 而是被同类实例化的类对象共享，比如所有 int 和所有 double 的类对象
 * ，享有相互独立的静态变量。也可以说是编译器生成了
 * int 和 double 两个版本的类定义。
 * */
int main() {

    cout<< add(1,2)<<endl;
    cout<< add(1.5,2.7)<<endl;

    myClass<int> a;

    return 0;
}
