//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include <iostream>
#include "../iterators/iterator.hpp"

namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef std::pair<const Key, T>				value_type;
		typedef size_t								size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		typedef iter<value_type> iterator;
		typedef iter<const value_type> const_iterator;
		typedef reverse_iter<iterator> reverse_iterator;
		typedef reverse_iter<const_iterator> const_reverse_iterator;

		map() {}

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) {}

		map (const map& other) {}

		~map() {}

		map& operator=(const map& other) {}

		iterator begin() {}

		const_iterator begin() const {}

		iterator end() {}

		const_iterator end() const {}

		reverse_iterator rbegin() {}

		const_reverse_iterator rbegin() const {}

		reverse_iterator rend() {}

		const_reverse_iterator rend() const {}

		bool empty() const {}

		size_type size() const {}

		size_type max_size() const {}

		mapped_type& operator[](const key_type& k) {}

		std::pair<iterator,bool> insert(const value_type& val) {}

		iterator insert(iterator position, const value_type& val) {}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {}

		void erase (iterator position) {}

		size_type erase (const key_type& k) {}

		void erase (iterator first, iterator last) {}

		void swap (map& x) {}

		void clear() {}

		key_compare key_comp() const {}

//		value_compare value_comp() const {}

		iterator find(const key_type& k) {}

		const_iterator find(const key_type& k) const {}

		size_type count(const key_type& k) const {}

		iterator lower_bound(const key_type& k) {}

		const_iterator lower_bound(const key_type& k) const {}

		iterator upper_bound(const key_type& k) {}

		const_iterator upper_bound(const key_type& k) const {}

		std::pair<iterator,iterator> equal_range(const key_type& k) {}

		std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {}

		allocator_type get_allocator() const {}
	};
};

#endif //CONTAINERS_MAP_HPP
