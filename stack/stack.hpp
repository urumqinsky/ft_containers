//
// Created by Said Islamov on 2/11/22.
//

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include "../vector/vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::size_type			size_type;

	protected:
		container_type c;

	public:
		explicit stack(const container_type& c = container_type()) : c(c) {}

		~stack() {}

		stack(const stack& other) : c(other.c) {}

		stack& operator=(const stack& other) {
			if (this != &other) {
				c = other.c;
			}
			return *this;
		}

		bool empty() const {
			return c.empty();
		}

		size_type size() const {
			return c.size();
		}

		reference top() {
			return c.back();
		}

		const_reference top() const {
			return c.back();
		}

		void push(const value_type& x) {
			c.push_back(x);
		}

		void pop() {
			c.pop_back();
		}

		bool eq(const stack<T, Container>& x) const {
			return c == x.c;
		}

		bool lt(const stack<T, Container>& x) const {
			return c < x.c;
		}
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.eq(rhs);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.lt(rhs);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs < rhs);
	}
}

#endif //CONTAINERS_STACK_HPP
