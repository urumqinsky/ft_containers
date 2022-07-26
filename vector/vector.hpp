//
// Created by Said Islamov on 2/11/22.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <iostream>
#include "../iterators/iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/algorithim.hpp"

namespace ft {
	template<class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename std::size_t						size_type;
		typedef typename std::ptrdiff_t						difference_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef iter<pointer> iterator;
		typedef iter<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	protected:
		pointer vectorBegin;
		size_type vectorSize, vectorCapacity;
		allocator_type vectorAlloc;

	public:
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
			   const allocator_type& alloc = allocator_type(),
			   typename enable_if<!is_integral<InputIterator>::value>::type* = NULL)
			   : vectorBegin(0), vectorSize(last - first), vectorCapacity(last - first), vectorAlloc(alloc) {
			if (first > last) {
				throw std::length_error("vector");
			}
			vectorBegin = vectorAlloc.allocate(vectorSize);
			for (size_type i = 0; first < last; ++i) {
				vectorAlloc.construct(vectorBegin + i, *first);
				first++;
			}
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

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
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
			if (vectorCapacity < n) {
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
			if (max_size() < n) {
				throw std::length_error("vector");
			} else if (vectorCapacity < n) {
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
			if (vectorSize <= n) {
				throw std::out_of_range("vector");
			}
			return *(vectorBegin + n);
		}

		const_reference at(size_type n) const {
			if (vectorSize <= n) {
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
			size_type diff = last - first;
			if (first > last) {
				throw std::length_error("vector");
			}
			clear();
			if (vectorCapacity < diff) {
				vectorAlloc.deallocate(vectorBegin, vectorCapacity);
				vectorBegin = vectorAlloc.allocate(diff);
				vectorCapacity = diff;
			}
			for (size_type i = 0; first < last; i++) {
				vectorAlloc.construct(vectorBegin + i, *first);
				first++;
			}
			vectorSize = diff;
		}

		void assign(size_type n, const value_type& val) {
			clear();
			if (vectorCapacity < n) {
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
			(void)val;
			if (n != 0) {
				if (max_size() - vectorSize < n) {
					throw std::length_error("vector");
				} else if (vectorCapacity < vectorSize + n) {
					size_type tmpCap = vectorCapacity;
					tmpCap = max_size() - tmpCap / 2 < tmpCap ? 0 : tmpCap + tmpCap / 2;
					if (tmpCap < vectorSize + n) {
						tmpCap = vectorSize + n;
					}
					pointer tmpBegin = vectorAlloc.allocate(tmpCap);
				}
			}
		}

		template<class InputIterator>
		typename enable_if<!is_integral<InputIterator>::value>::type
		insert(iterator position, InputIterator first, InputIterator last) {
			(void)position;
			(void)first;
			(void)last;
		}

		iterator erase(iterator position) {
			erase(position, position + 1);
		}

		iterator erase(iterator first, iterator last) {
			size_type diff = end() - last;
			pointer tmp = vectorAlloc.allocate(diff);
			for (size_type i = 0; i < diff; ++i) {
				vectorAlloc.construct(tmp + i, *(last + i));
			}
			for (size_type i = first - begin(); i < size(); ++i) {
				vectorAlloc.destroy(vectorBegin + i);
			}
			size_type j = diff;
			for (size_type i = first - begin(); i < j; ++i) {
				vectorAlloc.construct(vectorBegin + i, *(tmp++));
			}
			return iterator(vectorBegin);
		}

		void swap(vector& other) {
			if (vectorAlloc == other.vectorAlloc) {
				std::swap(vectorBegin, other.vectorBegin);
				std::swap(vectorSize, other.vectorSize);
				std::swap(vectorCapacity, other.vectorCapacity);
			} else {
				vector tmp = *this;
				*this = other;
				other = tmp;
			}
		}

		void clear() {
			for (size_type i = 0; i < vectorSize; ++i) {
				vectorAlloc.destroy(vectorBegin + i);
			}
			vectorSize = 0;
		}
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

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& lhs, vector<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif //CONTAINERS_VECTOR_HPP
