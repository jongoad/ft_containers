#ifndef STACK_HPP
# define STACK_HPP

#pragma once

// #include "vector.hpp"
#include <vector>

namespace ft {

	template<class T, class container = std::vector<T> >	//FIXME: Change to ft::vector when its implemented
	class stack {
		public:

			//Type definitions
			typedef	container								container_type;
			typedef	typename	container::value_type		value_type;
			typedef	typename	container::size_type		size_type;
			typedef	typename	container::reference		reference;
			typedef typename	container::const_reference	const_reference;


			//Default constructor
			explicit stack(const container& cont = container()) : c(cont) {}
			
			//Copy constructor
			stack(const stack& other) : c(other.c) { }
			
			// Equals operator overload
			stack&	operator=(const stack& rhs) { this.c = rhs.c; }


			/* Access Functions */
			//top
			reference	top() { return c.back(); }
			
			//empty
			bool		empty() { return c.empty(); }
			
			//size
			size_type	size() { return c.size(); }

			//push
			void		push(const_reference val) { c.push_back(val); }

			//pop
			void		pop(void) { c.pop_back(); }
			
		protected:
			container	c;

			template<class T, class contain>
			friend bool	operator==(const stack<class T, class contain>& a, const stack<class T, class contain>& b);
			template<class T, class contain>
			friend bool	operator<(const stack<class T, class contain>& a, const stack<class T, class contain>& b);
		
	};

	//Non-Member Functions

	/* Operator Overloads */
	template<class T, class contain>
	bool	operator==(const stack<class T>& a, const stack<class T>& b) { return a.c == b.c; }
	template<class T, class contain>
	bool	operator!=(const stack<class T>& a, const stack<class T>& b) { return !(a == b); }
	template<class T, class contain>
	bool	operator<(const stack<class T>& a, const stack<class T>& b) { return a.c < b.c; }
	template<class T, class contain>
	bool	operator>(const stack<class T>& a, const stack<class T>& b) { return b < a; }
	template<class T, class contain>
	bool	operator<=(const stack<class T>& a, const stack<class T>& b) { return !(b < a); }
	template<class T, class contain>
	bool	operator>=(const stack<class T>& a, const stack<class T>& b) { return !(a < b); }

}

#endif