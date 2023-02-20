#pragma once

#include "../utility.hpp"

/* Properties

1. Every node is either red or black
2. All NULL leaf nodes are considered black
3. A red node cannot have a red child
4. Every path from a give node to any of its descendant
	nodes goes through the same number of black nodes
*/

// #define LEFT 0
// #define RIGHT 1
// #define left child[LEFT]
// #define right child[RIGHT]

// enum colour_t {
// 	BLACK = 0, 
// 	RED = 1
// } colour_e;


// //Node object
// template <class T>
// struct rb_node {
// 	rb_node*		parent;
// 	rb_node*		child[2];

// 	std::pair<T,T2> 
// 	T				data;
// 	enum colour_e	colour;


// };

// //Tree object
// template <class T>
// struct rb_tree {
// 	rb_node<T>* root;
// };


namespace ft {

	template <typename T, typename Compare, typename Allocator>
	class rb_tree {
		public:
			typedef T											value_type;
			typedef Compare										value_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef value_type& 								reference;
			typedef const value_type&							const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			// iterator;
			// const_iterator;
			


			//Constructors & destructor
			rb_tree();



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
}; //namespace ft end


/* TO DO:
1. Write iterators
2. Implement all functions called from map
3. Implement RB tree functionality (insertion, deletion, rebalancing) 

*/