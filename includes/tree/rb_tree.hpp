#pragma once

#include "../utility.hpp"

/* Properties

1. Every node is either red or black
2. The root node is black (should be)
2. All NULL leaf nodes are considered black
3. A red node cannot have a red child
4. Every path from a given node to any of its descendant
	nodes goes through the same number of black nodes


When searching for a key, if it is not present, we will end up at a NULL (black) leaf node

Rebalancing is done using either left or right rotatation, and recolour.

If the parent of a node is NULL it is the root node

References:
https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
*/

#include <iterator>


namespace ft {

	enum node_colour_t {
		BLACK = true,
		RED = false
	} node_colour_e;


	//Node class definition
	template <typename T>
	class node {
		public:
			typedef node<T>		node_type;
			typedef node_type*	node_pointer;

			//Replace int with proper pointer type
			node_pointer left;
			node_pointer right;
			node_pointer parent;
			node_colour_e colour;
			T value;
	};

	//Const tree iterator class definition
	template<typename T, typename Difference_type>
	class const_rb_tree_iterator {

		public:
			//STL iterator typedefs
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef const value_type&				reference;
			typedef const value_type*				pointer;
			typedef Difference_type					difference_type;
			
			typedef typename node<t>::node_pointer	node_pointer;

			//Constructors & destructor
			const_rb_tree_iterator() : ptr_(NULL) {}
			const_rb_tree_iterator(node_pointer p) : ptr_(p) {}


			node_pointer&	base() { return ptr_; }
			const node_pointer&	base() const { return ptr_; }

			//Access
			reference	operator*() const { return ptr_->value; }
			pointer		operator->() const { return std::addressof(operator*()); };

			//Incrementation & decrementation
			const_rb_tree_iterator&	operator++() {
				//ptr_ = get next pointer
				return *this;
			}

			const_rb_tree_iterator	operator++(int) {
				const_rb_tree_iterator it = *this;
				++(*this);
				return it;
			}

			const_rb_tree_iterator&	operator--() {
				//ptr_ = get previous pointer
				return *this;
			}

			const_rb_tree_iterator	operator--(int) {
				const_rb_tree_iterator it = *this;
				--(*this);
				return it;
			}

			bool	operator==(const const_rb_tree_iterator& other) const {
				return ptr_ == other.ptr_;
			}


			//Need to handle comparing cosnt and non-const pointers
			//This is why mik creates types outside of this scope so both const and non const iterators
			//can know what each other is
			bool	operator!=(const const_rb_tree_iterator& other) const {
				return !(*this == other);
			}

		private:
			node_pointer	ptr_;
	};

	//tree iterator class definition
	template <typename T, typename Difference_type>
	class rb_tree_iterator : public const_rb_tree_iterator<T, Difference_type> {
		public:

			typedef const_rb_tree_iterator<T,Difference_type> base;

			//STL iterator typedefs
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef value_type&						reference;
			typedef value_type*						pointer;
			typedef Difference_type					difference_type;
			
			typedef typename node<t>::node_pointer	node_pointer;

			//Constructors & destructor
			rb_tree_iterator() : base::ptr_(NULL) {}
			rb_tree_iterator(node_pointer p) : base::ptr_(p) {}


			node_pointer&	base() { return base::ptr_; }
			const node_pointer&	base() const { return base::ptr_; }

			//Access
			reference	operator*() const { return base::ptr_->value; }
			pointer		operator->() const { return std::addressof(operator*()); };

			//Incrementation & decrementation
			rb_tree_iterator&	operator++() {
				//ptr_ = get next pointer
				base::operator++();
				return *this;
			}

			rb_tree_iterator	operator++(int) {
				rb_tree_iterator it = *this;
				base::operator++();
				return it;
			}

			rb_tree_iterator&	operator--() {
				//ptr_ = get previous pointer
				base::operator--();
				return *this;
			}

			rb_tree_iterator	operator--(int) {
				rb_tree_iterator it = *this;
				base::operator--();
				return it;
			}

			bool	operator==(const rb_tree_iterator& other) const {
				return base::operator==(other);
			}


			//Need to handle comparing cosnt and non-const pointers
			//This is why mik creates types outside of this scope so both const and non const iterators
			//can know what each other is
			bool	operator!=(const rb_tree_iterator& other) const {
				return !(base::operator==(other));
			}

	};






	template <typename T, typename Compare, typename Allocator>
	class rb_tree {
		public:
			//STL type definitions
			typedef T											value_type;
			typedef Compare										value_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef value_type& 								reference;
			typedef const value_type&							const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			//Iterator definitions
			// typedef iterator;
			// typedef const_iterator;

		

			//Constructors & destructor
			rb_tree(const value_compare& comp) {}
			rb_tree(const rb_tree& other) {}


			rb_tree& operator=();

			~rb_tree();


			get_allocator();

			//Element access
			at();
			operator[];

			//Iterators
			begin();
			end();
			rbegin();
			rend();

			//Capacity
			empty();
			size();
			max_size();

			//Modifiers
			clear();
			insert();
			//Before attempting to insert, check if key already exists

			erase();
			swap();

			//Lookup
			count();
			find();
			equal_range();
			lower_bound();
			upper_bound();

			//Observers
			key_comp();
			value_comp();


		private:

			size_type size_;
	};
} //namespace ft


/* TO DO:
1. Write iterators
2. Implement all functions called from map
3. Implement RB tree functionality (insertion, deletion, rebalancing) 

*/