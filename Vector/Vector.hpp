//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft {
    template<class T, class Allocator = std::allocator<T> >
            class vector {
            public:
                typedef T value_type;
                typedef Allocator allocator_type;
                typedef typename allocator_type::size_type size_type;
                typedef typename allocator_type::difference_type difference_type;
                typedef typename allocator_type::reference reference;
                typedef typename allocator_type::const_reference const_reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;

                explicit vector(const allocator_type& alloc = allocator_type())
                : vectorPtr(0), vectorSize(0), vectorCapacity(0), vectorAlloc(alloc) {

                }

                explicit vector(size_type n, const value_type& val = value_type(),
                                 const allocator_type& alloc = allocator_type())
                                 : vectorSize(n), vectorCapacity(n), vectorAlloc(alloc) {
                    vectorPtr = vectorAlloc.allocate(n);
                    for (size_type i = 0; i < n; ++i) {
                        vectorAlloc.construct(vectorPtr + i, val);
                    }
                }

                template<class InputIterator>
                        vector(InputIterator first, InputIterator last,
                                const allocator_type& alloc = allocator_type()) : vectorAlloc(alloc) {
                    (void)first;
                    (void)last;
                }

                vector(const vector& other)
                : vectorPtr(other.vectorPtr), vectorSize(other.vectorSize),
                vectorCapacity(other.vectorCapacity), vectorAlloc(other.vectorAlloc) {

                }

                ~vector() {

                }

                vector& operator=(const vector& other) {
                    vectorPtr = other.vectorPtr;
                    vectorSize = other.vectorSize;
                    vectorCapacity = other.vectorCapacity;
                    vectorAlloc = other.vectorAlloc;
                    return *this;
                }

//                Capacity
                size_type size() const {
                    return vectorSize;
                }

                size_type max_size() const {
                    return vectorAlloc.max_size();
                }

                void resize(size_type n, value_type val = value_type()) {
                    (void)n;
                    (void)val;
                }

                size_type capacity() const {
                    return vectorCapacity;
                }

                bool empty() const {
                    if (vectorSize == 0) {
                        return true;
                    } else {
                        return false;
                    }
                }

                void reserve(size_type n) {
                    if (n > vectorCapacity) {

                    }
                }

//                Element access
                reference operator[](size_type n) {
                    return vectorPtr[n];
                }

                const_reference operator[](size_type n) const {
                    return vectorPtr[n];
                }

                reference at(size_type n) {
                    if (n >= vectorSize) {
                        throw std::out_of_range("...");
                    }
                    return vectorPtr[n];
                }

                const_reference at(size_type n) const {
                    if (n >= vectorSize) {
                        throw std::out_of_range("...");
                    }
                    return vectorPtr[n];
                }

                reference front() {
                    return NULL;
                }

                const_reference front() const {
                    return NULL;
                }

                reference back() {
                    return NULL;
                }

                const_reference back() const {
                    return NULL;
                }

                template<class InputIterator>
                        void assign(InputIterator first, InputIterator last) {

                }

                void assign(size_type n, const value_type& val) {

                }

                void push_back(const value_type& val) {
                     if (vectorSize == vectorCapacity) {
                         resize();
                     }

                }

            protected:
                pointer vectorPtr;
                size_type vectorSize, vectorCapacity;
                allocator_type vectorAlloc;

    };
}

#endif //CONTAINERS_VECTOR_HPP
