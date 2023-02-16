#pragma once

// #include "vector.hpp"
#include <vector>

//FIXME: Change to ft::vector when its implemented

namespace ft {

	template<class T, class container = std::vector<T> >
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
			stack&	operator=(const stack& other) { c = other.c; }


			/*lhsccess Functions */
			//top
			reference	top() { return c.back(); }
			const_reference	top() const {return c.back(); }

			//empty
			bool		empty() const { return c.empty(); }
			
			//size
			size_type	size() const { return c.size(); }

			//push
			void		push(const_reference val) { c.push_back(val); }

			//pop
			void		pop(void) { c.pop_back(); }
			
		protected:
			container	c;

			template<class Ty, class contain>
			friend bool	operator==(const ft::stack<Ty,contain>& lhs, const ft::stack<Ty,contain>& rhs);
			template<class Ty, class contain>
			friend bool	operator<(const ft::stack<Ty,contain>& lhs, const ft::stack<Ty,contain>& rhs);
		
	};

	//Non-Member Functions

	/* Operator Overloads */
	template<class Ty, class contain>
	bool	operator==(const stack<Ty, contain>& lhs, const stack<Ty, contain>& rhs) { return lhs.c == rhs.c; }
	template<class Ty, class contain>
	bool	operator!=(const stack<Ty, contain>& lhs, const stack<Ty, contain>& rhs) { return !(lhs == rhs); }
	template<class Ty, class contain>
	bool	operator<(const stack<Ty, contain>& lhs, const stack<Ty, contain>& rhs) { return lhs.c < rhs.c; }
	template<class Ty, class contain>
	bool	operator>(const stack<Ty, contain>& lhs, const stack<Ty, contain>& rhs) { return rhs < lhs; }
	template<class Ty, class contain>
	bool	operator<=(const stack<Ty, contain>& lhs, const stack<Ty, contain>& rhs) { return !(rhs < lhs); }
	template<class Ty, class contain>
	bool	operator>=(const stack<Ty, contain>& lhs, const stack<Ty, contain>& rhs) { return !(lhs < rhs); }

} //namespace ft end