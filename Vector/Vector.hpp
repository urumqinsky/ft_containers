//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

namespace ft {
    template<class T, class Alloc = std::allocator<T> >
    class vector {
    private:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef size_t size_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
    };
}

#endif //CONTAINERS_VECTOR_HPP
