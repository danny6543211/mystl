#ifndef DEQUE_HPP
#define DEQUE_HPP

namespace mystl {

#include <initializer_list>
#include <cstddef>
#include "iterator.hpp"

#define BUFFER_MAX_BYTE 8

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
        return BUFFER_MAX_BYTE / sizeof(T);    
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
        // 以first为基准的偏移
        int offset = n + (cur - first);
        // 还在同个缓冲区
        if (offset >= 0 && offset < buffer_size()) {
            cur += n;
        }
        else {
            // 节点偏移多少个节点
            int node_offset = n > 0 ? offset / buffer_size() 
            // 前面+1是因为 offset == -buffer_size()还在同个缓冲区，不用偏移
            // 后面-1因为 offset < 0 至少偏移一个节点
            : (offset + 1) / buffer_size() - 1;
            set_node(node + node_offset);
            // cur偏移
            cur = first + (int)(offset > 0 ? offset % buffer_size() 
            : (-offset) % buffer_size());

        }
        return *this; 
    }

    iterator operator+(int n) {
        iterator temp = *this;
        return temp += n;
    }

    iterator operator-=(int n) {
        return *this += -n;
    }

    iterator operator-(int n) {
        iterator temp = *this;
        return temp -= n;
    }
    
    reference operator[](int n) {
        return *((*this) + n);
    }

    bool operator==(const iterator& x) {
        return cur == x.cur;
    }

    bool operator!=(const iterator& x) {
        return cur != x.cur;
    }
    
};

template<class T>
class deque {

};


} /* end of namespace mystl */

#endif