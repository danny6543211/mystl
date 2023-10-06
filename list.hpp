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
    T data;
    node_pointer prev;
    node_pointer next;
    __list_node() : data(), prev(), next() {}
    __list_node(T data, node_pointer prev, node_pointer next) 
    : data(data), prev(prev), next(next) {}
};

template<class T>
struct __list_iterator : public mystl::iterator<mystl::bidirectional_iterator_tag, T> {
    typedef __list_iterator<T> iterator;
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
    list() {
        // 头结点不存数据
        head = new list_node;
        head->next = head;
        head->prev = head;
    }    

    list(const std::initializer_list<T>& x) : list() {
        list_node *p = head;
        for (auto i = x.begin(); i != x.end(); i++) {
            p->next = new list_node(*i, p, nullptr);
            p = p->next;
        }
        p->next = head;
        head->prev = p;
    }

    list(const list<T>& x) : list(x.begin(), x.end()) {}
 
    list(const iterator begin, const iterator end) : list() {
        list_node *p = head;
        for (iterator i = begin;i != end; i++) {
            p->next = new list_node(*i, p, nullptr);
            p = p->next;
        }
        // 头尾接起来
        p->next = head;
        head->prev = p;
    }

    list(const size_t n, const T& x) : list() {
        list_node *p = head;
        for (size_t i = 0; i < n; i++) {
            p->next = new list_node(x, p, nullptr);
            p = p->next;
        }
        p->next = head;
        head->prev = p;
    }

    iterator begin() { return head->next; }
    iterator end() { return head; }
    iterator rbegin() { return head->prev; }
    iterator rend() { return head; }

    size_t size() {
        return mystl::distance(begin(), end());
    }

    bool empty() { return size() == 0; }

    reference front() const { return head->next->data; }
    reference back() const { return head->prev->data; }

    void push_back(const T& x) {
        list_node* new_node = new list_node(x, head->prev, head);
        head->prev->next = new_node;
        head->prev = new_node;        
    }

    void pop_back() {
        list_node* temp = head->prev;
        head->prev = head->prev->prev;
        head->prev->next = head;
        delete(temp);
    }

    void push_front(const T& x) {
        list_node* new_node = new list_node(x, head, head->next);
        head->next->next->prev = new_node;
        head->next = new_node;
    }
    
    void pop_front() {
        list_node* temp = head->next;
        head->next = head->next->next;
        head->next->prev = head;
        delete(temp);
    }

    iterator insert(iterator pos, const T& x) {
        list_node* new_node = new list_node(x, pos.node->prev, pos.node);
        pos.node->next->prev = new_node;
        pos.node->prev->next = new_node;
        return pos;
    }

    void clear() {
        
    }
    
    iterator erase(iterator pos) {
        if (pos.node == head)
            return iterator(nullptr);
        iterator ret(pos.node->next);
        list_node* temp = pos.node;
        pos.node->prev->next = pos.node->next;
        pos.node->next->prev = pos.node->prev;
        delete(temp);
        return ret;
    }
    
    void remove() {} 

    static void test() {
        list<int> a = {1,2,3,4};

        for (auto i = a.begin(); i != a.end(); i++) {
            std::cout << *i;
        }    
    }
};



} /* end of mystl */


#endif