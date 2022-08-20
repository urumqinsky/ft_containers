//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include "../utils/tree.hpp"

namespace ft {
	template<class Key, class T, class Compare = std::less<Key>,
	        class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::reference			const_reference;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
			friend class map;
		protected :
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

		typedef tree<value_type, value_compare, allocator_type>	base;

		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef typename base::iterator						iterator;
		typedef typename base::const_iterator				const_iterator;
		typedef typename base::reverse_iterator				reverse_iterator;
		typedef typename base::const_reverse_iterator		const_reverse_iterator;

	private:
		base _tree;

	public:

		map() : _tree() {}

		explicit map(const key_compare& comp = key_compare(), const allocator_type& a = allocator_type()) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) {}

		map(const map& m) {}

		~map() {}

		map& operator=(const map& m) {
			if (this != &m) {
				_tree.clear();
				_tree.value_comp() = m._tree.value_comp();
				_tree.copy_assign_alloc(m._tree);
				insert(m.begin(), m.end());
			}
			return *this;
		}

		iterator begin() {
			return _tree.begin;
		}

		const_iterator begin() const {
			return _tree.begin();
		}

		iterator end() {
			return _tree.end();
		}

		const_iterator end() const {
			return _tree.end();
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

		bool empty() const {
			return _tree.size() == 0;
		}

		size_type size() const {
			return _tree.size();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		mapped_type& operator[](const key_type& k) {}

		std::pair<iterator, bool> insert(const value_type& v) {
			return _tree.insert(v);
		}

		iterator insert(iterator position, const value_type& v) {
			return _tree.insert(position, v);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			return _tree.insert(first, last);
		}

		void erase(iterator position) {
			_tree.erase(position);
		}

		size_type erase(const key_type& k) {
			return _tree.erase(k);
		}

		void erase(iterator first, iterator last) {
			_tree.erase(first, last);
		}

		void clear() {
			_tree.clear();
		}

		void swap(map& m) {
			_tree.swap(m._tree);
		}

		allocator_type get_allocator() const {
			return allocator_type(_tree._alloc());
		}

		key_compare key_comp() const {
			return _tree.value_comp().key_comp();
		}

		value_compare value_comp() const {
			return value_compare(_tree.value_comp().key_comp());
		}

		iterator find(const key_type& k) {
			return _tree.find(k);
		}

		const_iterator find(const key_type& k) const {
			return _tree.find(k);
		}

		size_type count(const key_type& k) const {
			return _tree.count(k);
		}

		iterator lower_bound(const key_type& k) {
			return _tree.lower_bound(k);
		}

		const_iterator lower_bound(const key_type& k) const {
			return _tree.lower_bound(k);
		}

		iterator upper_bound(const key_type& k) {
			return _tree.upper_bound(k);
		}

		const_iterator upper_bound(const key_type& k) const {
			return _tree.upper_bound(k);
		}

		pair<iterator, iterator> equal_range(const key_type& k) {
			return _tree.equal_range(k);
		}

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
			return _tree.equal_range(k);
		}
	};
}

#endif //CONTAINERS_MAP_HPP
