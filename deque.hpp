#ifndef DEQUE_HPP
#define DEQUE_HPP

namespace mystl {

#include <initializer_list>
#include <cstddef>
#include "iterator.hpp"

template<class T>
struct __deque_iterator : public mystl::iterator<mystl::random_access_iterator_tag, T> {
    typedef __deque_iterator<T>              iterator;
    typedef T                                value_type;
    typedef T*                               pointer;
    typedef T&                               reference;
    typedef T**                              map_pointer;

    // 当前元素
    T* cur;
    // 缓冲区头
    T* first;
    // 缓冲区尾(还没使用)
    T* last;
    // 指向 map
    map_pointer node;

    size_t buffer_size() {
        // 整除返回512
        if (512 % sizeof(T) == 0)
            return 512;
        // 不整除返回512以下的最大数量
        else 
            return (512 / sizeof(T)) * sizeof(T);    
    }

    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first + buffer_size();
    }
    
    reference operator*() { return *cur; }

    iterator operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }

    iterator operator++(int) {
        iterator ret = *this;
        ++(*this);
        return ret;
    }

    iterator operator--() {
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }

    iterator operator--(int) {
        iterator ret = *this;
        --(*this);
        return ret;
    }
    
    iterator operator+=(int n) {
        
    }
    
};


class deque {

};


} /* end of namespace mystl */

#endif