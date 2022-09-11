//
// Created by Reaper Lando on 2/11/22.
//

#ifndef CONTAINERS_SET_HPP
#define CONTAINERS_SET_HPP

#include "../utils/tree.hpp"
#include "../utils/algorithim.hpp"

namespace ft {
	template<class Key, class Compare = std::less<Key>,
	        class Allocator = std::allocator<Key> >
	class set {
	public:
		typedef Key											key_type;
		typedef key_type									value_type;
		typedef Compare										key_compare;
		typedef key_compare									value_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

	private:
		typedef tree<value_type, value_compare, allocator_type>	base;

		base _tree;

	public:
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef typename base::iterator						iterator;
		typedef typename base::iterator						const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		explicit set(const key_compare& comp = key_compare(),
					 const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

		template <class InputIterator>
		set(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp) {
			insetr(first, last);
		}

		set(const set& s) : _tree(s._tree) {}

		~set();

		set& operator=(const set& s) {
			_tree = s._tree;
			return *this;
		}

		iterator begin() {
			return _tree.begin();
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

		bool empty() const {
			return _tree.size() == 0;
		}

		size_type size() const {
			return _tree.size();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		ft::pair<iterator, bool> insert(const value_type& v) {
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

		void swap(set& s) {
			_tree.swap(s._tree);
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

	template <class Key, class Compare, class Allocator>
	bool operator==(const set<Key, Compare, Allocator>& x,
					const set<Key, Compare, Allocator>& y) {
		return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
	}

	template <class Key, class Compare, class Allocator>
	bool operator< (const set<Key, Compare, Allocator>& x,
					const set<Key, Compare, Allocator>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class Compare, class Allocator>
	bool operator!=(const set<Key, Compare, Allocator>& x,
					const set<Key, Compare, Allocator>& y) {
		return !(x == y);
	}

	template <class Key, class Compare, class Allocator>
	bool operator> (const set<Key, Compare, Allocator>& x,
					const set<Key, Compare, Allocator>& y) {
		return y < x;
	}

	template <class Key, class Compare, class Allocator>
	bool operator>=(const set<Key, Compare, Allocator>& x,
					const set<Key, Compare, Allocator>& y) {
		return !(x < y);
	}

	template <class Key, class Compare, class Allocator>
	bool operator<=(const set<Key, Compare, Allocator>& x,
					const set<Key, Compare, Allocator>& y) {
		return !(y < x);
	}

	template <class Key, class Compare, class Allocator>
	void swap(set<Key, Compare, Allocator>& x,
			  set<Key, Compare, Allocator>& y) {
		x.swap(y);
	}
}

#endif //CONTAINERS_SET_HPP
