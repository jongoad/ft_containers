#pragma once

//System Includes
#include <iterator>
#include <memory>

namespace ft {

	using std::random_access_iterator_tag;

	//Set up typedefs for iterator_trait conventional names
	template <class Iter>
	struct iterator_traits {
		typedef typename	Iter::value_type			value_type;
		typedef typename	Iter::difference_type		difference_type;
		typedef typename	Iter::iterator_category		iterator_category;
		typedef typename	Iter::pointer				pointer;
		typedef typename	Iter::reference				reference;
	};

	//Non-const iterators
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		
	};
	
	//Const iterators
	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef std::ptrdiff_t				difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;	
	};

	//
	template <class Category, class T, class Distance = std::ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef	Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};


	//Reverse iterators
	template <class Iter>
	class reverse_iterator :
		public iterator	<typename iterator_traits<Iter>::iterator_category,
						 typename iterator_traits<Iter>::value_type,
						 typename iterator_traits<Iter>::difference_type,
						 typename iterator_traits<Iter>::pointer,
						 typename iterator_traits<Iter>::reference> {
		public:
			typedef				Iter									iterator_type;
			typedef typename	iterator_traits<Iter>::value_type		value_type;
			typedef typename	iterator_traits<Iter>::difference_type	difference_type;
			typedef typename	iterator_traits<Iter>::pointer			pointer;
			typedef typename	iterator_traits<Iter>::reference		reference;
		
		protected:
			Iter	current_;

		public:
			reverse_iterator() : current_() {}
			explicit reverse_iterator(iterator_type it) : current_(it) {}

			template <class U>
			reverse_iterator(const reverse_iterator<U>& other) : current_(other.current_) {}

			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U>& other) {
				if (*this != other) {
					current_ = other.current_;
				}
				return *this;
			}

			//Public member functions
			iterator_type base() const { return current_; }


			//Iterator access methods
			reference	operator*() const { Iter tmp = current_; return *(--tmp); }
			pointer		operator->() const { return std::addressof(operator*()); }
			pointer		operator[](difference_type dist) const { return *(*this + dist); }

			//Incrementation and decrementation methods
			reverse_iterator&	operator++() { --current_; return *this; }
			reverse_iterator	operator++(int) { return reverse_iterator(current_--); }
			reverse_iterator&	operator--() { ++current_; return *this; }
			reverse_iterator	operator--(int) { return reverse_iterator(current_++); }

			//Addition and subtraction methods
			reverse_iterator	operator+(difference_type dist) const { return reverse_iterator(current_ - dist); }
			reverse_iterator	operator-(difference_type dist) const { return reverse_iterator(current_ + dist); }
			reverse_iterator&	operator+=(difference_type dist) { current_ -= dist; return *this; }
			reverse_iterator&	operator-=(difference_type dist) { current_ += dist; return *this; }
	};

	//Operator overloads
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return !(lhs == rhs);
	}
	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return rhs < lhs;
	}
	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return !(rhs < lhs);
	}
	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return !(lhs < rhs);
	}
	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type dist, const reverse_iterator<Iter>& it) {
		return reverse_iterator<Iter>(it.base() - dist);
	}

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {
		return lhs.base() - rhs.base();
	}


} //end namespace ft