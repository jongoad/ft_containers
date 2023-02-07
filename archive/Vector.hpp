#ifndef VECTOR_HPP
# define VECTOR_HPP

#pragma once

#include <memory>

#include "FT.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class Vector {
	public:

		/**************************************/
		/* 		  Iterator Subclass           */
		/**************************************/
		class VectorIterator {
			public:
			/* Constructors & Destructor */
			VectorIterator() {_ptr = NULL}
			~VectorIterator() {}

			/****************************/
			/*    Operator Overloads    */
			/****************************/

			/* Assignement */
			VectorIterator& operator=(const VectorIterator& other);
			VectorIterator& operator+=(const VectorIterator& other);
			VectorIterator& operator-=(const VectorIterator& other);
			
			/* Comparison */

			//Need to deal with both const and non const pointers
			bool	operator==(const VectorIterator& rhs)	(return(_ptr == rhs.getPtr()));
			bool	operator!=(const VectorIterator& rhs)	(return(_ptr != rhs.getPtr()));
			bool	operator>(const VectorIterator& rhs)	(return(_ptr > rhs.getPtr()));
			bool	operator>=(const VectorIterator& rhs)	(return(_ptr >= rhs.getPtr()));
			bool	operator<(const VectorIterator& rhs)	(return(_ptr < rhs.getPtr()));
			bool	operator<=(const VectorIterator& rhs)	(return(_ptr >= rhs.getPtr()));

			/* Incrementation */
			/* Pre */
			VectorIterator&	operator++(void);
			VectorIterator&	operator--(void);

			/* Post */
			VectorIterator	operator++(T);
			VectorIterator	operator--(T);

	
			private:
				T*	_ptr;
		};

		/* Type Definition */
		typedef	alloc	allocator_type;


		typedef VectorIterator	it;
		

		/* Constructors & Destructor */
		Vector();
		Vector(const Vector &other);
		~Vector();

		/* Assignemnt Operator Overload */
		Vector&	operator=(const Vector& other);


		/* Iterators */
		it	begin(void) {
			return (it(_data));
		}

		it	end(void) {
			return (it(_data +_size));
		}

		/* Const Iterators */
		

		/* Size & Capacity */



		/* Member Access */









		



	private:
		allocator_type 	_alloc;
		T*				_data;
		size_t			_size;
		uint32_t		_capacity;
};

}
#endif





/*
	Vector growth:

	The size of a vector grows logarithmically.

		1, 2, 4,8, 16, 32, 64, 128 etc.

	When a vector is created, its size will be whatever size in that growth chain that it currently fits into best.

	If an element is inserted into a vector and is not at the end, every other element affected will be shifted and copied
	to a new location

	Vector can use an array

*/
/*

Template:
	template < class T, class Alloc = allocator<T> > class vector; // generic template
Member types:

	value_type
	allocator_type
	reference
	const_reference
	pointer
	const_pointer
	iterator
	const_iterator
	reverse_iterator
	const_reverse_iterator
	difference_type
	size_type

Member Functions:

	constructor
	destructor
	operator=

	Iterator functions:
		begin
		end
		rbegin
		rend
		cbegin
		cend
		crbegin
		crend

	Capacity functions:
		size
		max_size
		resize
		capacity
		empty
		reserve
		shrink_to_fit

	Element access functions:
		operator[]
		at
		front
		back
		data
	
	Modifier functions:
		assign
		push_back
		pop_back
		insert
		erase
		swap
		clear
		emplace
		emplace_back

	Allocator functions:
		get_allocator
	
	Non-member function overloads:
		all relational operators (==, <, >, !=, <=, >=)
		swap

		Relational operator templates:
		
		template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

*/