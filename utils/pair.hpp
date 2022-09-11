//
// Created by Said Islamov on 15.07.2022.
//

#ifndef CONTAINERS_PAIR_HPP
#define CONTAINERS_PAIR_HPP

namespace ft {
	template<class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(T1()), second(T2()) {}

		pair(const T1& x, const T2& y) : first(x), second(y) {}

		template<class U1, class U2>
		pair(const pair<U1, U2>& x) : first(x.first), second(x.second) {}

		pair& operator=(const pair& other) {
			if (this != &other) {
				first = other.first;
			}
			return *this;
		}
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(const T1& x, const T2& y) {
		pair<T1, T2> s(x, y);
		s.first = y;
		return pair<T1, T2>(x, y);
	}

	template<class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first < rhs.first || !(rhs.first < lhs.first && lhs.second < rhs.second);
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return rhs < lhs;
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}
}

#endif //CONTAINERS_PAIR_HPP
