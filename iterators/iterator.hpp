//
// Created by Reaper Lando on 3/18/22.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP

#include <iostream>

namespace ft {
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };
    struct contiguous_iterator_tag: public random_access_iterator_tag { };

    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };
}

#endif //CONTAINERS_ITERATOR_HPP
