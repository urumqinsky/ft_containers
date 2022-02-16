//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include <vector>

namespace ft {
	template<class T, class Container = std::vector<T>>
			class stack {
			public:
				stack(const stack& other) : container(other.container) {

				}

				explicit stack(const container_type& ctnr = container_type()) : container(ctnr) {

				}

				stack& operator=( const stack& other ) {
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

				template <class T, class Container>
						bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
					return 0;
				}

				template <class T, class Container>
						bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
					return 0;
				}

				template <class T, class Container>
						bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
					return 0;
				}

				template <class T, class Container>
						bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
					return 0;
				}

				template <class T, class Container>
						bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
					return 0;
				}

				template <class T, class Container>
						bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
					return 0;
				}

			private:
				Container container;
			};
}

#endif //CONTAINERS_STACK_HPP
