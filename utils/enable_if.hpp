//
// Created by Said Islamov on 12.07.2022.
//

#ifndef CONTAINERS_ENABLE_IF_HPP
#define CONTAINERS_ENABLE_IF_HPP

#include <type_traits>

namespace ft {
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator T() const {
			return v;
		}
	};

	template<typename T>
	struct is_integral : public integral_constant<bool, false> {};

	template<>
	struct is_integral<bool> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<char> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<char16_t> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<char32_t> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<wchar_t> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<signed char> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<short int> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<int> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<long int> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<long long int> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<unsigned char> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<unsigned short int> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<unsigned int> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<unsigned long int> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<unsigned long long int> : public integral_constant<bool, true> {};
}

#endif //CONTAINERS_ENABLE_IF_HPP
