#ifndef DEQUE_HPP
#define DEQUE_HPP

namespace mystl {

#include <initializer_list>
#include <cstddef>
#include "iterator.hpp"

template<class T>
struct __deque_iterator : public mystl::iterator<mystl::random_access_iterator_tag, T> {
    
};


class deque {

};


} /* end of namespace mystl */

#endif