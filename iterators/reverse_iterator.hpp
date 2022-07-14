//
// Created by Said Islamov on 14.07.2022.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template<class T>
	class reverse_iterator : public iterator<
			typename iterator_traits<T>::iterator_category,
			typename iterator_traits<T>::value_type,
			typename iterator_traits<T>::difference_type,
			typename iterator_traits<T>::pointer,
			typename iterator_traits<T>::reference> {
	public:
		typedef T															iterator_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

	protected:
		iterator_type current;

	public:
		reverse_iterator() : current() {}

		explicit reverse_iterator(iterator_type x) : current(x) {}

		template<class U>
		reverse_iterator(const reverse_iterator<U>& x) : current(x.base()) {}

		iterator_type base() const {
			return current;
		}

		reference operator*() const {
			iterator_type tmp = current;
			return *--tmp;
		}

		pointer operator->() const {
			return _VSTD::addressof(operator*());
		}

		reverse_iterator& operator++() {
			--current;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			--current;
			return tmp;
		}

		reverse_iterator& operator--() {
			++current;
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			++current;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(current - n);
		}

		reverse_iterator& operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(current + n);
		}

		reverse_iterator& operator-=(difference_type n) {
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template<class Iter>
	bool operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iter>
	bool operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<class Iter>
	bool operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class Iter>
	bool operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<class Iter>
	bool operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<class Iter>
	bool operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs) {
		return lhs.base() >= rhs.base();
	}
}

#endif //CONTAINERS_REVERSE_ITERATOR_HPP
