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

template<class T>
class list {

};

void test() {
    __list_iterator<int> a = new __list_node<int>();

}


} /* end of mystl */


#endif