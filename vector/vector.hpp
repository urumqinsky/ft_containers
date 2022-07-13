//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <iostream>
#include "../iterators/iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/algorithim.hpp"

namespace ft {
	template<class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T											value_type;
		typedef Alloc									allocator_type;
		typedef typename std::size_t						size_type;
		typedef typename std::ptrdiff_t						difference_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef iter<pointer> iterator;
		typedef iter<const_pointer> const_iterator;
		typedef reverse_iter<iterator> reverse_iterator;
		typedef reverse_iter<const_iterator> const_reverse_iterator;

		explicit vector(const allocator_type& alloc = allocator_type())
				: vectorBegin(0), vectorSize(0), vectorCapacity(0), vectorAlloc(alloc) {}

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
			clear();
			vectorAlloc.deallocate(vectorBegin, vectorCapacity);
		}

		vector& operator=(const vector& other) {
			if (this != &other) {
				clear();
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
//				Iterator
		iterator begin() {
			return iterator(vectorBegin);
		}

		const_iterator begin() const {
			return const_iterator(vectorBegin);
		}

		iterator end() {
			return iterator(vectorBegin + vectorSize);
		}

		const_iterator end() const {
			return const_iterator(vectorBegin + vectorSize);
		}

//				Capacity
		size_type size() const {
			return vectorSize;
		}

		size_type max_size() const {
			return vectorAlloc.max_size();
		}

//				ПРОВЕСТИ РЕФАКТОРИНГ
		void resize(size_type n, value_type val = value_type()) {
			if (n > vectorCapacity) {
				if (vectorCapacity == 0 || n > vectorCapacity << 1) {
					reserve(n);
				} else {
					reserve(vectorCapacity << 1);
				}
			}
			for (size_type i = n; i < vectorSize; ++i) {
				vectorAlloc.destroy(vectorBegin + i);
			}
			for (size_type i = vectorSize; i < n; ++i) {
				vectorAlloc.construct(vectorBegin + i, val);
				++vectorSize;
			}
			vectorSize = n;
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

//				Element access
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

//				Modifiers
		template<class InputIterator>
		typename enable_if<!is_integral<InputIterator>::value, void>::type
		assign(InputIterator first, InputIterator last) {
			difference_type ptrdiff = last - first;
			if (first > last) {
				throw std::length_error("vector");
			}
			clear();
			if (ptrdiff > static_cast<difference_type>(vectorCapacity)) {
				vectorAlloc.deallocate(vectorBegin, vectorCapacity);
				vectorBegin = vectorAlloc.allocate(ptrdiff);
				vectorCapacity = ptrdiff;
			}
			for (int i = 0; first != last; i++) {
				vectorAlloc.construct(vectorBegin + i, *first);
				first++;
			}
			vectorSize = ptrdiff;
		}

		void assign(size_type n, const value_type& val) {
			clear();
			if (n > vectorCapacity) {
				vectorAlloc.deallocate(vectorBegin, vectorCapacity);
				vectorBegin = vectorAlloc.allocate(n);
				vectorCapacity = n;
			}
			for (size_type i = 0; i < n; ++i) {
				vectorAlloc.construct(vectorBegin + i, val);
			}
			vectorSize = n;
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
			if (vectorSize > 0) {
				vectorAlloc.destroy(vectorBegin + vectorSize - 1);
				vectorSize--;
			}
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position;
			(void)val;
		}

		void insert(iterator position, size_type n, const value_type& val) {
			(void)position;
			(void)n;
			(void)val;
		}

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last) {
			(void)position;
			(void)first;
			(void)last;
		}

		iterator erase(iterator position) {
			(void)position;
		}

		iterator erase(iterator first, iterator last) {
			(void)first;
			(void)last;
		}

		void swap(vector& x) {
			std::swap(vectorBegin, x.vectorBegin);
			std::swap(vectorSize, x.vectorSize);
			std::swap(vectorCapacity, x.vectorCapacity);
			std::swap(vectorAlloc, x.vectorAlloc);
		}

		void clear() {
			for (size_type i = 0; i < vectorSize; ++i) {
				vectorAlloc.destroy(vectorBegin + i);
			}
			vectorSize = 0;
		}

	protected:
		pointer vectorBegin;
		size_type vectorSize, vectorCapacity;
		allocator_type vectorAlloc;

	};

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return lexicographical_compare(lhs.begin(), rhs.begin(), lhs.end(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}
}

#endif //CONTAINERS_VECTOR_HPP
