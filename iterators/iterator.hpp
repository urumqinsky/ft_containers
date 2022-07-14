//
// Created by Said Islamov on 3/18/22.
//

#ifndef CONTAINERS_ITERATOR_HPP
#define CONTAINERS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template<class T>
	class iter {
	public:
		typedef T															iterator_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

	private:
		iterator_type i;

	public:
		iter() : i() {}

		explicit iter(iterator_type x) : i(x) {}

		template <class U>
		iter(const iter<U>& x) : i(x.base()) {}

		iterator_type base() const {
			return i;
		}

		reference operator*() const {
			return *i;
		}

		pointer operator->() const {
			return &**i;
		}

		iter& operator++() {
			++i;
			return *this;
		}

		iter operator++(int) {
			iter temp = *this;
			++i;
			return temp;
		}

		iter& operator--() {
			--i;
			return *this;
		}

		iter operator--(int) {
			iter temp = *this;
			--i;
			return temp;
		}

		iter operator+(difference_type n) const {
			return iter(i + n);
		}

		iter& operator+=(difference_type n) {
			i += n;
			return *this;
		}

		iter operator-(difference_type n) {
			return iter(i - n);
		}

		iter& operator-=(difference_type n) {
			i -= n;
			return *this;
		}

		reference operator[](difference_type n) const {
			return i[n];
		}
	};

	template<class Iter1>
	bool operator==(const iter<Iter1>& lhs, const iter<Iter1>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<class Iter1>
	bool operator<(const iter<Iter1>& lhs, const iter<Iter1>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<class Iter1>
	bool operator!=(const iter<Iter1>& lhs, const iter<Iter1>& rhs) {
		return !(lhs == rhs);
	}

	template<class Iter1>
	bool operator>(const iter<Iter1>& lhs, const iter<Iter1>& rhs) {
		return rhs < lhs;
	}

	template<class Iter1>
	bool operator>=(const iter<Iter1>& lhs, const iter<Iter1>& rhs) {
		return !(lhs < rhs);
	}

	template<class Iter1>
	bool operator<=(const iter<Iter1>& lhs, const iter<Iter1>& rhs) {
		return !(rhs < lhs);
	}

	template<class Iter1, class Iter2>
	typename iter<Iter1>::difference_type operator-(const iter<Iter1>& lhs, const iter<Iter2>& rhs) {
		return lhs.base() - rhs.base();
	}

	template<class Iter1>
	iter<Iter1> operator+(typename iter<Iter1>::difference_type n, iter<Iter1> x) {
		x += n;
		return x;
	}
}

#endif //CONTAINERS_ITERATOR_HPP
