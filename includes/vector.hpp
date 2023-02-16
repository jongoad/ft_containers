#pragma once

//System includes
#include <memory>

//Local includes
#include "type_traits.hpp"
#include "iterator.hpp"

//Definitions
#define ft_noexcept throw()

namespace ft {

	//Namespace additions
	using ft::enable_if;
	using ft::is_integral;
	using std::random_access_iterator_tag;

	//vector const_iterator template
	template <class vector> //FIXME: Might need to change this to something like MyVector
	class vector_const_iterator {
		public:
			//Definitions
			typedef				random_access_iterator_tag	iterator_category;
			typedef typename	vector::value_type			value_type;
			typedef	typename	vector::difference_type		distance;
			typedef typename	vector::pointer				pointer;
			typedef const		value_type&					reference;

			//Store pointer
			pointer	ptr_;

			//Constructors & destructor
			vector_const_iterator() : ptr_() {};
			vector_const_iterator(pointer ptr) : ptr_(ptr) {};

			//Iterator access
			reference		operator*() const ft_noexcept { return *ptr_; }													//Dereference (*)
			const pointer	operator->() const ft_noexcept { return ptr_; }													//Pointer access (->)
			reference		operator[](const distance dist) const { return *(ptr_ + dist); }					//Subscript access []

			//Iterator incrementation & decrementation
			vector_const_iterator&	operator++() ft_noexcept {++ptr_; return *this; }										//Pre-increment
			vector_const_iterator	operator++(int) ft_noexcept { vector_const_iterator tmp = *this; ++ptr_; return tmp; }	//Post-increment
			vector_const_iterator&	operator--() ft_noexcept {--ptr_; return *this; }										//Pre-decrement
			vector_const_iterator	operator--(int) ft_noexcept { vector_const_iterator tmp = *this; --ptr_; return tmp; }	//Post-decrement

			//Iterator addition & subtraction
			vector_const_iterator&	operator+=(const distance dist) {
				ptr_ += dist;
				return *this;
			}
			vector_const_iterator& operator+(const distance dist) const {
				vector_const_iterator tmp = *this;
				ptr_ += dist;
				return tmp;
			}
			vector_const_iterator&	operator-=(const distance dist) {
				ptr_ -= dist;
				return *this;
			}
			vector_const_iterator& operator-(const distance dist) const {
				vector_const_iterator tmp = *this;
				ptr_ -= dist;
				return tmp;
			}
	}; //vector_const_iterator end

	//vector_const_iterator operator overloads
	template <class vector>
	bool	operator==(const vector_const_iterator<vector>& lhs, const vector_const_iterator<vector>& rhs) {
		return lhs.ptr_ == rhs.ptr_; 
	}
	template <class vector>
	bool	operator==(const vector_const_iterator<vector>& lhs, const vector_const_iterator<vector>& rhs) {
		return !(lhs == rhs);
	}
	template <class vector>
	bool	operator<(const vector_const_iterator<vector>& lhs, const vector_const_iterator<vector>& rhs) {
		return lhs.ptr_ < rhs.ptr_; 
	}
	template <class vector>
	bool	operator>(const vector_const_iterator<vector>& lhs, const vector_const_iterator<vector>& rhs) {
		return rhs < lhs;
	}
	template <class vector>
	bool	operator<=(const vector_const_iterator<vector>& lhs, const vector_const_iterator<vector>& rhs) {
		return !(rhs < lhs); 
	}
	template <class vector>
	bool	operator>=(const vector_const_iterator<vector>& lhs, const vector_const_iterator<vector>& rhs) {
		return !(lhs < rhs); 
	}

	//vector_iterator class definition
	template <class vector>
	class vector_iterator : public vector_const_iterator<vector> {
		public:
			//Definitions
			typedef vector_const_iterator<vector> base;

			typedef				random_access_iterator_tag	iterator_category;
			typedef typename 	vector::value_type			value_type;
			typedef	typename 	vector::difference_type		distance;
			typedef typename	vector::pointer				pointer;
			typedef const		value_type&					reference;

			//Constructors & destructor
			vector_iterator(pointer ptr) : base(ptr) {};

			//Iterator access
			reference		operator*() const ft_noexcept { return const_cast<reference>(base::operator*()); }				//Dereference (*)
			const pointer	operator->() const ft_noexcept { return this->ptr_; }											//Pointer access (->)
			reference		operator[](const distance dist) const { return const_cast<reference>(base::operator[](dist)); }					//Subscript access []


			//Iterator incrementation & decrementation
			vector_iterator&	operator++() ft_noexcept {base::operator++(); return *this; }										//Pre-increment
			vector_iterator		operator++(int) ft_noexcept { vector_iterator tmp = *this; base::operator++(); return tmp; }	//Post-increment
			vector_iterator&	operator--() ft_noexcept {base::operator--(); return *this; }										//Pre-decrement
			vector_iterator		operator--(int) ft_noexcept { vector_iterator tmp = *this; base::operator--(); return tmp; }	//Post-decrement


			//Iterator addition & subtraction
			vector_iterator&	operator+=(const distance dist) {
				base::operator+=(dist);
				return *this;
			}
			vector_iterator& operator+(const distance dist) {
				vector_iterator tmp = *this;
				base::operator+=(dist);
				return tmp;
			}
			vector_iterator&	operator-=(const distance dist) {
				base::operator-=(dist);
				return *this;
			}
			vector_iterator& operator-(const distance dist) {
				vector_iterator tmp = *this;
				base::operator-=(dist);
				return tmp;
			}
	};


	//vector class template
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			//Typedefs
			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef allocator_type::size_type			size_type;
			typedef allocator_type::difference_type		difference_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef allocator_type::pointer				pointer;
			typedef allocator_type::const_pointer		const_pointer;


			//Iterator typedefs
			typedef vector_iterator<vector<T> > 			iterator;
			typedef vector_const_iterator<vector<T> >		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			
		private:
			allocator_type	alloc_ = NULL;
			pointer			first_ = NULL;
			pointer			last_ = NULL;
			pointer			end_ = NULL;
		public:
			//Constructors & destructor
			vector() ft_noexcept :
				alloc_(Allocator()), first_(alloc_.allocate(0)), last_(first_), end_(first_) {}

			explicit vector(const Allocator& alloc) ft_noexcept :
				alloc_(alloc), first_(alloc_.allocate(0)), last_(first_), end_(first_) {}
				
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
				alloc_(alloc), first_(alloc.allocate(0)), last_(first_), end_(first_) {
					
				}

			template <class input_it>
			vector(input_it first, input_it last, const Allocator& alloc = Allocator());
			vector(const vector& other);
			
		private:
	};
}