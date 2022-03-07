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
                : vectorBegin(0), vectorSize(0), vectorCapacity(0), vectorAlloc(alloc) {

                }

                explicit vector(size_type n, const value_type& val = value_type(),
                                const allocator_type& alloc = allocator_type())
                                : vectorSize(n), vectorCapacity(n), vectorAlloc(alloc) {
                    vectorBegin = vectorAlloc.allocate(n);
                    for (size_type i = 0; i < n; ++i) {
                        vectorAlloc.construct(vectorBegin + i, val);
                    }
                }

                template<class InputIterator>
                        vector(InputIterator first, InputIterator last,
                               const allocator_type& alloc = allocator_type()) : vectorAlloc(alloc) {
                    (void)first;
                    (void)last;
                }

                vector(const vector& other)
                : vectorSize(other.vectorSize), vectorCapacity(other.vectorSize), vectorAlloc(other.vectorAlloc) {
                	vectorBegin = vectorAlloc.allocate(vectorSize);
					for (size_type i = 0; i < vectorSize; ++i) {
						vectorAlloc.construct(vectorBegin + i, other[i]);
					}
                }

                ~vector() {
					for (size_type i = 0; i < vectorSize; ++i) {
						vectorAlloc.destroy(vectorBegin + i);
					}
					vectorAlloc.deallocate(vectorBegin, vectorCapacity);
                }

                vector& operator=(const vector& other) {
                    if (this != &other) {
                        for (size_type i = 0; i < vectorSize; ++i) {
                            vectorAlloc.destroy(vectorBegin + i);
                        }
                        vectorAlloc.deallocate(vectorBegin, vectorCapacity);
                        vectorSize = other.vectorSize;
                        vectorCapacity = other.vectorSize;
                        vectorAlloc = other.vectorAlloc;
                        vectorBegin = vectorAlloc.allocate(vectorCapacity);
                        for (size_type i = 0; i < vectorSize; ++i) {
                            vectorAlloc.construct(vectorBegin + i, other[i]);
                        }
                    }
                    return *this;
                }

//                Capacity
                size_type size() const {
                    return vectorSize;
                }

                size_type max_size() const {
                    return vectorAlloc.max_size();
                }

//                ПРОВЕСТИ РЕФАКТОРИНГ
                void resize(size_type n, value_type val = value_type()) {
                    if (n > vectorCapacity) {
                        if (vectorCapacity == 0 || n > vectorCapacity << 1) {
                            reserve(n);
                        } else {
                            reserve(vectorCapacity << 1);
                        }
                    }
                    try {
                        for (size_type i = vectorSize; i < n; ++i) {
                            vectorAlloc.construct(vectorBegin + i, val);
                            ++vectorSize;
                        }
                    } catch (std::exception& e) {
                        for (size_type i = 0; i < vectorSize; ++i) {
                            vectorAlloc.destroy(vectorBegin + i);
                        }
                        vectorAlloc.deallocate(vectorBegin, vectorCapacity);
                        throw;
                    }
                    if (n < vectorSize) {
                        vectorSize = n;
                    }
                }

                size_type capacity() const {
                    return vectorCapacity;
                }

                bool empty() const {
                    return vectorSize == 0;
                }

                void reserve(size_type n) {
                    if (n > vectorCapacity) {
                        size_type i, j;
                        pointer tmpBegin = vectorAlloc.allocate(n);
                        try {
                            for (i = 0; i < vectorSize; ++i) {
                                vectorAlloc.construct(tmpBegin + i, *(vectorBegin + i));
                            }
                        } catch (std::exception& e) {
                            for (j = 0; j < i; ++j) {
                                vectorAlloc.destroy(tmpBegin + j);
                            }
                            vectorAlloc.deallocate(tmpBegin, n);
                            throw;
                        }
                        for (i = 0; i < vectorSize; ++i) {
                            vectorAlloc.destroy(vectorBegin + i);
                        }
                        vectorAlloc.deallocate(vectorBegin, vectorCapacity);
                        vectorBegin = tmpBegin;
                        vectorCapacity = n;
                    }
                }

//                Element access
                reference operator[](size_type n) {
                    return *(vectorBegin + n);
                }

                const_reference operator[](size_type n) const {
                    return *(vectorBegin + n);
                }

                reference at(size_type n) {
                    if (n >= vectorSize) {
                        throw std::out_of_range("vector");
                    }
                    return *(vectorBegin + n);
                }

                const_reference at(size_type n) const {
                    if (n >= vectorSize) {
                        throw std::out_of_range("vector");
                    }
                    return *(vectorBegin + n);
                }

                reference front() {
                    return *vectorBegin;
                }

                const_reference front() const {
                    return *vectorBegin;
                }

                reference back() {
                    return *(vectorBegin + vectorSize - 1);
                }

                const_reference back() const {
                    return *(vectorBegin + vectorSize - 1);
                }

//                Modifiers
                template<class InputIterator>
                    void assign(InputIterator first, InputIterator last) {
                    (void)first;
                    (void)last;
                }

                void assign(size_type n, const value_type& val) {
                    (void)n;
                    (void)val;
                }

                void push_back(const value_type& val) {
                    if (vectorSize == vectorCapacity) {
                        if (vectorCapacity == 0) {
                            reserve(1);
                        } else {
                            reserve(vectorCapacity << 1);
                        }
                    }
                    vectorAlloc.construct(vectorBegin + vectorSize, val);
                    ++vectorSize;
                }

                void pop_back() {
                    vectorAlloc.destroy(vectorBegin + vectorSize - 1);
                    --vectorSize;
                }

            protected:
                pointer vectorBegin;
                size_type vectorSize, vectorCapacity;
                allocator_type vectorAlloc;

    };
}

#endif //CONTAINERS_VECTOR_HPP
