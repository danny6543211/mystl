#ifndef LIST_HPP
#define LIST_HPP

namespace mystl {

#include <iostream>
#include <initializer_list>
#include <stddef.h>
#include "iterator.hpp"

template<class T>
struct __list_node {
    typedef __list_node<T>* node_pointer;
    node_pointer prev;
    node_pointer next;
    T data;
};

template<class T>
struct __list_iterator {
    typedef __list_iterator<T> iterator;

    // 双向访问迭代器
    typedef mystl::bidirectional_iterator_tag   iterator_category;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef __list_node<T>*                     node_pointer;

    // iterator管理的node指针
    node_pointer node;

    __list_iterator() {}
    __list_iterator(node_pointer x) : node(x) {}
    __list_iterator(const iterator& x) : node(x.node) {}

    bool operator==(const iterator x) { return node == x.node; }
    bool operator!=(const iterator x) { return node != x.node; }
    reference operator*() { return node->data; }

    iterator operator++() {
        node = node->next;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        node = node->next;
        return temp;
    }

    iterator operator--() {
        node = node->prev;
        return *this;
    }

    iterator operator--(int) {
        iterator temp = *this;
        node - node->prev;
        return temp;
    }

};

/*
   双向循环链表实现list
*/

template<class T>
class list {
public:
    typedef T                   value_type;
    typedef T*                  pointer;
    typedef T&                  reference;
    typedef __list_iterator<T>  iterator;
    typedef __list_node<T>      list_node;
    
// 其他容器可以基于list实现，所以使用protected
protected:
    list_node* head;

public:
    list() {}
    list(const std::initializer_list<T>& x) {}
    list(const list<T>& x) {}
    list(const iterator begin, const iterator end) {}
    list(const size_t n, const T& x) {}

    iterator begin() {}
    iterator end() {}
    iterator rbegin() {}
    iterator rend() {}

    size_t size() {}
    bool empty() {}

    reference front() {}
    reference back() {}

    void push_back() {}
    void pop_back() {}

    void push_front() {}
    void pop_front() {}

    iterator insert() {}
    clear() {}
    erase() {}
    remove() {}
};

void test() {
    

}


} /* end of mystl */


#endif