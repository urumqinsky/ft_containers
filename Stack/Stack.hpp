//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include <vector>

namespace ft {
	template<class T, class Container = std::vector<T> >
	class stack {
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
		typedef typename Container::size_t			size_type;

	protected:
		Container container;

	public:
		explicit stack(const container_type& ctnr = container_type()) : container(ctnr) {}

		virtual ~stack() {}

		stack(const stack& other) : container(other.container) {}

		stack& operator=(const stack& other) {
			container = other.container;
			return *this;
		}

		bool empty() const {
			return container.empty();
		}

		size_type size() const {
			return container.size();
		}

		value_type& top() {
			return container.back();
		}

		const value_type& top() const {
			return container.back();
		}

		void push(const value_type& val) {
			container.push_back(val);
		}

		void pop() {
			container.pop_back();
		}

		template <class T2, class Container2>
		friend bool operator==(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
			return lhs.container == rhs.container;
		}

		template <class T2, class Container2>
		friend bool operator!=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
			return lhs.container != rhs.container;
		}

		template <class T2, class Container2>
		friend bool operator<(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
			return lhs.container < rhs.container;
		}

		template <class T2, class Container2>
		friend bool operator<=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
			return lhs.container <= rhs.container;
		}

		template <class T2, class Container2>
		friend bool operator>(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
			return lhs.container > rhs.container;
		}

		template <class T2, class Container2>
		friend bool operator>=(const stack<T2, Container2>& lhs, const stack<T2, Container2>& rhs) {
			return lhs.container >= rhs.container;
		}
	};
}

#endif //CONTAINERS_STACK_HPP
