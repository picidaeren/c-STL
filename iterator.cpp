#include <iostream>
#include <cstddef>
#include <iostream>
#include "Iterator.h"
#include "Vector.h"
using namespace std;

/*介绍 5 种常见迭代器：
 * 输入、输出迭代器，前向逆向迭代器，双向迭代器和随机迭代器。
 * 主要内容包括各自的构造方法和操作方法。

    1.1 知识点
    输出迭代器
    输入迭代器
    前向迭代器
    双向迭代器
    随机迭代器
    迭代器辅助函数
 */
/*
 * 迭代器（iterator）是一种对象，它能够用来遍历标准模板库容器中的部分或全部元素，
 * 每个迭代器对象代表容器中的确定的地址。迭代器修改了常规指针的接口，
 * 所谓迭代器是一种概念上的抽象：那些行为上像迭代器的东西都可以叫做迭代器。
 * 然而迭代器有很多不同的能力，它可以把抽象容器和通用算法有机的统一起来。
 * 迭代器基本分为五种，输入输出迭代器，前向逆向迭代器，双向迭代器和随机迭代器。

简单概括：迭代器是一种检查容器内元素并遍历元素的可带泛型数据类型。

下面，我们新建头文件Iterator.h是头文件，用来实现我们的迭代器，
 这里的代码需要引用到系统头文件#include <cstddef>，它主要用于定义一些类型。
 接下来我们定义5种迭代器的类型，将其写入Iterator.h文件中：

struct input_iterator_tag{};//返回输入迭代器
struct output_iterator_tag{};//返回输出迭代器
struct forward_iterator_tag :public input_iterator_tag {};//返回前向迭代器
struct bidirectional_iterator_tag :public forward_iterator_tag {};//返回双向迭代器
struct random_access_iterator_tag :public bidirecti

 *
 * */

/* 输入迭代器：
 * 通过对输入迭代器解除引用，它将引用对象，而对象可能位于集合中。通常用于传递地址。*/

template<typename T, typename Distance>
struct input_iterator {
    typedef input_iterator_tag  iterator_category;//返回类型
    typedef T                   value_type;//所指对象类型
    typedef Distance            difference_type;//迭代器间距离类型
    typedef T*                  pointer;//操作结果类型
    typedef T&                  reference;//解引用操作结果类型
};

/* 输出迭代器：
 * 该类迭代器和输入迭代器极其相似，也只能单步向前迭代元素，
 * 不同的是该类迭代器对元素只有写的权力。通常用于返回地址。
 */
struct output_iterator{
    typedef output_iterator_tag  iterator_category;
    typedef void                 value_type;
    typedef void                 difference_type;
    typedef void                 pointer;
    typedef void                 reference;
};


/*
 * 前向迭代器：
 * 可以在一个正确的区间中进行读写操作，它拥有输入迭代器的所有特性，
 * 和输出迭代器的部分特性，以及单步向前迭代元素的能力。通常用于遍历。
 * */

template <class T, class Distance> struct forward_iterator{
    typedef forward_iterator_tag     iterator_category;
    typedef T                        value_type;
    typedef Distance                 difference_type;
    typedef T*                       pointer;
    typedef T&                       reference;
};
/*
 * 双向迭代器：
 * 该类迭代器是在前向迭代器的基础上提供了单步向后迭代元素的能力，前向迭代器的高级版。
 */
template <class T, class Distance> struct bidirectional_iterator{
    typedef bidirectional_iterator_tag    iterator_category;
    typedef T                        value_type;
    typedef Distance                difference_type;
    typedef T*                        pointer;
    typedef T&                        reference;
};

/*
 *
 *
 *
 * 随机迭代器：
 * 该类迭代器能完成上面所有迭代器的工作，它自己独有的特性就是可以像指针那样进行算术计算，
 * 而不是仅仅只有单步向前或向后迭代。
 */
template <class T, class Distance> struct random_access_iterator{
    typedef random_access_iterator_tag    iterator_category;
    typedef T                             value_type;
    typedef Distance                      difference_type;
    typedef T*                            pointer;
    typedef T&                            reference;
};

/*迭代器的实现，我们这里主要会使用到两个函数来辅助完成操作，
 * 分别是 advace 函数和 distance 函数。这两个函数是写到Algorithm.h文件中的。
 * */

//advance 函数: 用于迭代器前移，增加迭代的位置。可用于定向访问到迭代器的某个变量。
template<class InputIterator, class Distance>
void _advance(InputIterator& it, Distance n, input_iterator_tag){
    assert(n >= 0);
    while (n--){//当n大于0，迭代器前移n位
        ++it;
    }
}

void advance(InputIterator& it, Distance n){
    typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
    _advance(it, n, iterator_category());
}

//distance 函数: 用于计算迭代器间距离
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last, input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type dist = 0;//初始化距离
    while (first++ != last){//当首地址不等于尾地址，距离增加
        ++dist;
    }
    return dist;//返回迭代器间距离
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last){
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    return _distance(first, last, iterator_category());
}

int main() {
    mySTL::vector<int> vec;
    for(int i = 0;i < 10;i++)
        vec.push_back(i);

    mySTL::vector<int>::iterator it = vec.begin();
    mySTL::vector<int>::iterator end = vec.end();
    std::cout<<"The value of vector:";
    for(;it != vec.end();it++)
        std::cout<<*it<<" ";
    std::cout<<std::endl;

    //advance使用
    it = vec.begin();
    std::cout<<"After advance 3:";
    mySTL::advance(it,3);
    std::cout << *it << " "<<std::endl;

    //distance使用
    std::cout<<"The distance of position 3 to the end:";
    std::cout<<mySTL::distance(it,end)<<std::endl;

    return 0;


    return 0;
}
