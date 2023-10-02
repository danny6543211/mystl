#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace mystl {

#include <cstddef>

/*
    input_iterator_tag              输入迭代器
    output_iterator_tag             输出迭代器
    forward_iterator_tag            前向迭代器
    bidirectional_iterator_tag      双向迭代器
    random_access_iterator_tag      随机访问迭代器
*/

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

/*
    迭代器模版，自行设计迭代器需继承此模版选择迭代器类型
*/
template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
    typedef Category  iterator_category;
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
};

/*
    iterator_traits: 萃取器，获取迭代器类型
*/

/*
    萃取自己设计的迭代器类型
*/
template<class Iterator>
struct iterator_traits {
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
};


/*
    萃取普通指针的类型
*/
template<class T>
struct iterator_traits<T*> {
    typedef random_access_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef ptrdiff_t                  difference_type;
    typedef T*                         pointer;
    typedef T&                         reference;
};

// 萃取出任意iterator类型(包括指针)，参数输入迭代器，返回对象通常给编译器作重载标记
template<class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
    return typename iterator_traits<Iterator>::iterator_category();
}

template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first,InputIterator last, input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

template<class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first,RandomAccessIterator last, random_access_iterator_tag) {
    return last - first;
}

// 计算两迭代器距离
template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first,InputIterator last) {
    return __distance(first, last, iterator_category(first));
}

template<class InputIterator, class Distance>
inline void __advence(InputIterator& iter, Distance n, input_iterator_tag) {
    while (n--) { ++iter; }
}

template<class ForwardIterator, class Distance>
inline void __advence(ForwardIterator& iter, Distance n, forward_iterator_tag) {
    __advence(iter, n, input_iterator_tag());
}

template<class BidirectionalIterator, class Distance>
inline void __advence(BidirectionalIterator& iter, Distance n, bidirectional_iterator_tag) {
    if (n >= 0)
        while (n--) { ++iter; }
    else 
        while (n--) { --iter; }
}

template<class RandomAccessIterator, class Distance>
inline void __advence(RandomAccessIterator& iter, Distance n, random_access_iterator_tag) {
    iter += n;
}

// 迭代器前进n步
template<class InputIterator, class Distance = ptrdiff_t>
inline void advence(InputIterator& iter, Distance n) {
    __advence(iter, n, iterator_category(iter));
}

} /* end of mystl */

#endif