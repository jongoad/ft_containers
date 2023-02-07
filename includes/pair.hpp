#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

	template<class T1, class T2>
	struct pair {
		//Default constructor
		pair() : first(T1()), second(T2()) {}

		
		pair(T1 a, T2 b) : first(a), second(b) {}

		//Copy constructor
		template<class U, class V>
		pair(const pair<U,V>& other) : first(other.first), second(other.second) {}

		//Const constructor
		pair(const T1& a, const T2& b) : first(a), second(b) {}
		
		//Attributes
		T1	first;
		T2	second;
	};

	/************************/
	/* Non-Member Functions */
	/************************/

	/* make_pair */
	template<class T1, class T2>
	pair<T1, T2>	make_pair(T1 a, T2 b) { return pair<T1, T2>(a, b); }

	/* Operator Overloads */
	
	// ==
	template<class T1, class T2>
	bool	operator==(const pair<T1, T2>& a, const pair<T1, T2>& b) { return (a.first == b.first) && (a.second == b.second); }
	
	// !=
	template<class T1, class T2>
	bool	operator!=(const pair<T1, T2>& a, const pair<T1, T2>& b) { return !(a == b); }

	// <
	template<class T1, class T2>
	bool	operator<(const pair<T1, T2>& a, const pair<T1,T2>& b) { return a.first < b.first ? true : a.second < b.second ? true : false; }
	// >
	template<class T1, class T2>
	bool	operator>(const pair<T1,T2>& a, const pair<T1,T2>& b) { return b < a; }

	// <=
	template<class T1, class T2>
	bool	operator<=(const pair<T1,T2>& a, const pair<T1,T2>& b) { return !(b < a); }

	// >=
	template<class T1, class T2>
	bool	operator>=(const pair<T1, T2>& a, const pair<T1,T2>& b) { return !(a < b); }

}

#endif