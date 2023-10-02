#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace mystl {

#include <iostream>
#include <initializer_list>
#include <stddef.h>
#include "iterator.hpp"


template<class T>
class vector {
public:
    typedef T         value_type;
    typedef T*        pointer;
    typedef T*        iterator;
    typedef T&        reference;
    typedef ptrdiff_t difference_type;
    
private:
    iterator start;
    iterator finish;
    iterator end_of_storage;

public:
    vector() : start(), finish(), end_of_storage() {}
    
    vector(const std::initializer_list<T>& list) {
        size_t len = list.size();
        start = (T*) new T[len];
        finish = start;
        for (auto i = list.begin(); i != list.end(); i++, finish++) {
            *finish = *i;
        }
        end_of_storage = finish;
    }

    // 深拷贝
    vector(const vector<T>& vec) {
        size_t len = vec.size();
        start = (T*) new T[len];        
        for (size_t i = 0; i < len; i++) {
            start[i] = vec[i];
        }        
        finish = start + len;
        end_of_storage = finish;
    }

    vector(iterator first, iterator last) {
        size_t len = mystl::distance(first, last);
        start = (T*) new T[len];
        for (size_t i = 0; i < len; i++) {
            start[i] = first[i];
        }
        finish = start + len;
        end_of_storage = finish;
    }

    ~vector() { ::delete(start); }

    iterator begin() { return start; }
    
    iterator end() { return finish; }

    iterator rbegin() { return finish - 1; }

    iterator rend() { return start + 1; }

    size_t size() const { return mystl::distance(start, finish); }
    
    size_t capacity() {
        return mystl::distance(start, end_of_storage);
    }

    bool empty() {
        return finish == start;
    }

    reference operator[](size_t n) const {
        return *(start + n);
    }

    reference front() { return *(start); }
    reference back() { return *(finish - 1); }

    void push_back(const T& value) {
        mem_check();
        *finish++ = value;
    }

    void pop_back() { --finish; }

    iterator insert(iterator position, const T& value) {
        if (position > finish || position < start)
            throw "iterator out of range";
        size_t offset = position - start;
        mem_check();
        for (size_t i = size(); i != offset; i--) {
            start[i] = start[i - 1];
        }
        start[offset] = value;
        ++finish;
        return start + offset;
    }

    iterator erase(iterator position) {
        if (position > finish-1 || position < start)
            throw "iterator out of range";
        // offset之后全部往前挪一格
        for (auto i = position; i != finish; i++) {
            *i = *(i + 1);   
        }
        --finish;
        return position;
    }

    void clear() {
        // 不释放空间，把size设为0，不考虑析构
        finish = start;
    }

    void swap(vector<T>& vec) {
        // 没法访问vec的空间，留给以后用allocator解决...
    }

private:
    // 内存不够插入新值就扩充空间
    void mem_check() {
        if (finish == end_of_storage) {
            // 新开两倍空间
            T* new_alloc = (T*) new T[size() * 2];
            // 拷贝到新空间
            for (size_t i = 0; i < size(); i++) {
                new_alloc[i] = start[i];
            }
            // 保留旧的长度用以设定新空间的finish
            size_t old_len = size();
            // delete old alloc
            delete start;

            // 因为start换了，所以finish和end_if_storage都得换，因为是顺序存储的
            start = new_alloc;
            finish = start + old_len;
            end_of_storage = start + old_len * 2;
        }
    }

};


}; /* namespace mystl end */


#endif