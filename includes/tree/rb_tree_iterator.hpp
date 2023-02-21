#pragma once

#include "rb_tree_types.hpp"
#include <iterator>



namespace ft {
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
			
			typedef typename node_types<T>::node_pointer	node_pointer;
			typedef typename node_types<T>::end_node_pointer	end_node_pointer;

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
			//can know what each other are
			bool	operator!=(const const_rb_tree_iterator& other) const {
				return !(*this == other);
			}

		protected:
			end_node_pointer	ptr_;
	};

	//tree iterator class definition
	template <typename T, typename Difference_type>
	class rb_tree_iterator : public const_rb_tree_iterator<T, Difference_type> {
		public:

			typedef const_rb_tree_iterator<T,Difference_type> base_type;

			//STL iterator typedefs
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef value_type&						reference;
			typedef value_type*						pointer;
			typedef Difference_type					difference_type;
			
			typedef typename node_types<T>::node_pointer	node_pointer;
			typedef typename node_types<T>::end_node_pointer	end_node_pointer;

			//Constructors & destructor
			rb_tree_iterator() {}
			rb_tree_iterator(node_pointer p) : base_type(p) {}


			node_pointer&	base() { return this->ptr_; }
			const node_pointer&	base() const { return this->ptr_; }

			//Access
			reference	operator*() const { return static_cast<node_pointer>(this->ptr_)->value_; }
			pointer		operator->() const { return std::addressof(operator*()); };

			//Incrementation & decrementation
			rb_tree_iterator&	operator++() {
				//ptr_ = get next pointer
				base_type::operator++();
				return *this;
			}

			rb_tree_iterator	operator++(int) {
				rb_tree_iterator it = *this;
				base_type::operator++();
				return it;
			}

			rb_tree_iterator&	operator--() {
				//ptr_ = get previous pointer
				base_type::operator--();
				return *this;
			}

			rb_tree_iterator	operator--(int) {
				rb_tree_iterator it = *this;
				base_type::operator--();
				return it;
			}

			bool	operator==(const rb_tree_iterator& other) const {
				return base_type::operator==(other);
			}


			//Need to handle comparing cosnt and non-const pointers
			//This is why mik creates types outside of this scope so both const and non const iterators
			//can know what each other is
			bool	operator!=(const rb_tree_iterator& other) const {
				return !(base_type::operator==(other));
			}

	};

	
} //namespace ft
