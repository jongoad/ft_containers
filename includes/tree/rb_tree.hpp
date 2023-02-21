#pragma once

#include "../utility.hpp"
#include "rb_tree_types.hpp"
#include "rb_tree_iterator.hpp"
#include "rb_tree_algos.hpp"


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


Important functions to write:
- Get first node
	move left until next node is null
- Get last node
	move right untl next node is null



References:
https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
*/

namespace ft {

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
			typedef rb_tree_iterator<value_type, difference_type>		iterator;
			typedef const_rb_tree_iterator<value_type, difference_type>	const_iterator;


		private:
			//Node types (for internal use only)

			typedef typename node_types<value_type>::end_node_type 				end_node_type;
			typedef typename node_types<value_type>::node_type					node_type;
			typedef typename node_types<value_type>::end_node_pointer 			end_node_pointer;
			typedef typename node_types<value_type>::node_pointer 				node_pointer;
			typedef typename allocator_type::template rebind<node_type>::other	node_allocator;
			
		public:
			//Constructors & destructor
			//Default constructor
			rb_tree(const value_compare& comp)
				: alloc_(node_allocator()),
				  value_alloc_(allocator_type()),
				  comp_(comp),
				  end_node_(),
				  size_(0)
			{
				begin_ = end_node();
			}

			//Copy constructor
			// rb_tree(const rb_tree& other) 
			// 	: 
			// {

			// }

			//Provided allocator constructor
			// rb_tree(const value_compare& comp, const allocator_type& alloc)
			// rb_tree& operator=();
			// ~rb_tree();


			// get_allocator();

			//Element access
			// at();
			// operator[];

			//Iterators
			iterator begin() { return iterator(begin_); }
			const_iterator begin() const { return const_iterator(begin_); }
			iterator end() { return iterator(end_node_); }
			const_iterator end() const { return const_iterator(end_node_); }

			//Capacity
			bool empty() const { return size_ == size_type(0); }

			size_type size() const { return size_; }
			// max_size();

			//Modifiers
			// clear();

			//std::binary_function returning insert
			ft::pair<iterator,bool>	insert(const value_type& value) {
				bool was_inserted = false;
				//The parent node gets set in the find_pos() function
				end_node_pointer parent;
				node_pointer& child = find_pos(parent, value);

				//Find insert position, while also checking if key already exists

				iterator it(child);
				if (child == NULL) {
					it = insert_pos(child, parent, value);
					was_inserted = true;
				}
				return ft::make_pair(it, was_inserted);
			}

			//hint inserter
			// iterator insert(iterator pos, const value_type& value);

			//Inserts value in the position as close as possible to the position just prior to pos. The overload (5) is 
			//equivalent to emplace_hint(hint, std::forward<P>(value)) and only participates in overload resolution if
			//std::is_constructible<value_type, P&&>::value == true.
			


			//Range inserter (does not return whether or not key was already in map)
			// template <class InputIt>
			// iterator insert(InputIt first, InputIt last) {
			
			// }


			// erase();
			// swap();

			//Lookup
			// count();
			template <typename Key>
			iterator find(const Key& key) {
				return find_key<iterator>(key);
			}
			// equal_range();
			// lower_bound();
			// upper_bound();

			//Observers
			value_compare& value_comp() { return comp_; }

			const value_compare& value_comp() const { return comp_; }

		private:
			//Private member functions
			
			//Get the end node
			end_node_pointer end_node() {
				return static_cast<end_node_pointer>(&end_node_);
			}

			end_node_pointer end_node() const {
				return const_cast<end_node_pointer>(&end_node_);
			}

			//Get the root node
			node_pointer root() const {
				return end_node()->left_;
			}

			//Get a pointer to the root node
			node_pointer*	root_ptr() const {
				return &(end_node()->left_);
			}

			//Search for a key
			template <typename Iter, typename Key>
			Iter find_key(const Key& key) const {
				end_node_pointer ptr = search_key(key);
				return ptr == NULL ? Iter(static_cast<node_pointer>(end_node())) : Iter(static_cast<node_pointer>(ptr));
			}

			//Get pointer for key
			template <typename Key>
			end_node_pointer	search_key(const Key& key) const {
				node_pointer ptr = root();
				//Check if key is large or smaller than root key
				while (ptr != NULL) {
					//If key is less than ptr key go left
					if (value_comp()(key, ptr->value_))
						ptr = ptr->left_;
					//If key is greater than ptr key go right
					else if (value_comp()(ptr->value_, key))
						ptr = ptr->right_;
					//Else key is match
					else
						return static_cast<end_node_pointer>(ptr);
				}
				return NULL;
			}

			//Construct a new node
			node_pointer create_node(const value_type& value) {
				node_pointer ptr = alloc_.allocate(1);
				ptr->left_ = NULL;
				ptr->right_ = NULL;
				ptr->parent_ = NULL;
				value_alloc_.construct(&ptr->value_, value);
				return ptr;
			}

			template <typename Key>
			node_pointer& find_pos(end_node_pointer& parent, const Key& key) const {
				node_pointer	current = root();
				node_pointer*	ptr = root_ptr();

				//Check if value is left or right and iterate
				while (current != NULL) {
					if (value_comp()(key, current->value_)) {
						// Where key < value
						if (current->left_ != NULL) {
						ptr = &current->left_;
						current = current->left_;
						}
						else {
							parent = static_cast<end_node_pointer>(current);
							return current->left_;
						}
					}
					else if (value_comp()(current->value_, key)) {
						// Where key > value
						if (current->right_ != NULL) {
							ptr = &current->right_;
							current = current->right_;
						}
						else {
							parent = static_cast<end_node_pointer>(current);
							return current->right_;
						}
					}
					else {
						// Where key == value
						parent = static_cast<end_node_pointer>(current);
						return *ptr;
					}
				}
				parent = static_cast<end_node_pointer>(end_node());
				return parent->left_;
			}
			
			//Insert new node at position
			iterator insert_pos(node_pointer& pos, end_node_pointer parent, const value_type& value) {
				pos = create_node(value);
				pos->parent_ = static_cast<node_pointer>(parent);
				if (begin_->left_ != NULL)
					begin_ = begin_->left_;
				++size_;

				node_pointer ptr = pos;
				//Rebalance
				return iterator(ptr);
			}
			


		private:
			//Data members
			node_allocator		alloc_;
			allocator_type		value_alloc_;
			value_compare		comp_;
			end_node_type		end_node_;
			end_node_pointer	begin_;
			size_type			size_;

		


	}; //rb_tree 
} //namespace ft


/* TO DO:
1. Write iterators
2. Implement all functions called from map
3. Implement RB tree functionality (insertion, deletion, rebalancing) 

*/


//end_node_ is created when the tree object is created
//it points to root (end_node_->left == root_)
//This pointer exists for the lifespan of the tree, and is the main access point for the tree