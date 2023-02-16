#pragma once

//System includes
#include <memory>
#include <cmath>
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
	bool	operator!=(const vector_const_iterator<vector>& lhs, const vector_const_iterator<vector>& rhs) {
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
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;


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

			//Default constructor
			vector() ft_noexcept :
				alloc_(Allocator()), first_(alloc_.allocate(0)), last_(first_), end_(first_) {}

			//Allocator constructor
			explicit vector(const Allocator& alloc) ft_noexcept :
				alloc_(alloc), first_(alloc_.allocate(0)), last_(first_), end_(first_) {}

			//Size constructor
			explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
				alloc_(alloc), first_(alloc_.allocate(0)), last_(first_), end_(first_) {
				reallocate(count, get_capacity(count), value);
			}


			//Range constructor
			template <class input_it>
			vector(input_it first, enable_if_t<!is_integral<input_it>::value, input_it> last, const Allocator& alloc = Allocator()) :
				alloc_(alloc) {
				first_ = alloc_.allocate(get_capacity(last - first));
				last_ = first_ + (last - first);
				end_ = first_ + get_capacity(last - first);
				std::copy(first, last, iterator(first_));
			}

			//Copy constructor
			vector(const vector& other) : alloc_(other.alloc_) {
				first_ = alloc_.allocate(get_capacity(other.last_ - other.first_));
				last_ = first_ + (other.last_ - other.first_);
				end_ = first_ + get_capacity(other.last_ - other.first_);
				std::copy(other.begin(), other.end(), iterator(first_));
			}

			vector& operator=(const vector& other) {
				if *this == other
					return *this;

				clear();
				reallocate(other.size());
				std::copy(other.begin(), other.end(), iterator(first_));
				return *this;
			}
		

			~vector() ft_noexcept {
				for (size_type i = 0; i < static_cast<size_type>(end_ - last_); ++i)
					alloc_.destroy(first_ + i);
				alloc_.deallocate(first_, last_ - first_);
			}


			void	assign(size_type count, const value_type& value) {
				clear();
				reallocate(count, get_capacity(count), value);
			}

			template <class input_it>
			void assign(input_it first, enable_if_t<!is_integral<input_it>::value, input_it> last) {
				clear();
				reallocate(last - first - 1, get_capacity(last - first - 1));
				for (size_type i = 0; i < static_cast<size_type>(last - first); ++i)
					first_[i] = first[i];
			}


			allocator_type get_allocator() const ft_noexcept { return alloc_; }



			//Access functions

			value_type& at(size_type pos) {
				check_in_range(pos);
				return (*this)[pos];
			}
			value_type&	operator[](size_type pos) { return *(first_ + pos); }
			value_type&	front() { return *(first_); }
			value_type&	back() { return *(last_ - 1); }
			value_type*	data() ft_noexcept { return first_; }

			//Iterator functions
			iterator				begin() ft_noexcept { return iterator(first_); }
			const_iterator			begin() ft_noexcept { return const_iterator(first_); }
			iterator				end() ft_noexcept { return iterator(last + 1); }
			const_iterator			end() ft_noexcept { return const_iterator(last + 1); }
			reverse_iterator		rbegin() ft_noexcept { return reverse_iterator(end_); }
			const_reverse_iterator	rbegin() ft_noexcept { return const_reverse_iterator(end_); }
			reverse_iterator		rend() ft_noexcept { return reverse_iterator(begin_); }
			const_reverse_iterator	rend() ft_noexcept { return const_reverse_iterator(begin_); }


			//Capacity functions

			//Get maximum size of container
			bool		empty() const ft_noexcept { return size() == 0 ? true : false; }
			size_type	size() const ft_noexcept { return last_ - first_; }
			size_type	max_size() const { return alloc_.max_size(); }
			void		reserve(size_type capacity) { if (capacity > size()) reallocate(capacity); }
			size_type	capacity() const ft_noexcept { return end_ - first_; }

		
			//Modifier functions
			void clear() ft_noexcept { reallocate(0); }

			iterator	insert(iterator pos, const value_type* value) {
				difference_type pos_ = pos - first_;
				insert(pos, 1, value);
				return iterator(first_ + pos_);
			}
			iterator	insert(iterator pos, size_type count, const value_type& value) {
				difference_type pos_ = pos - first_;
				reserve(size() + count);

				pointer new_first_ = first_ + pos_;
				pointer new_last_ = last_;

				for (; new_last_ > new_first_; --new_last_) {
					*new_last_ = *(new_last_ + count);
					alloc_.destroy(new_last_);
				}
				for (size_type i = 0; i < count; ++i)
					alloc_.construct(new_first_ + i, value);
				return iterator(first_ + pos_);
			}

			erase();
			push_back();
			pop_back();
			resize();
			swap();





		//Utility functions
		private:


			//Memory management functions

			void	reallocate(size_type size, size_type capacity = 0, value_type value = value_type()) {
				
				//Check to make sure size can fit in max_size()
				if (size > max_size() || capacity > max_size())
					throw(std::length_error(""));
				
				//Allocate new memory and assign value
				pointer new_first_ = alloc_.allocate(size, first_);
				pointer new_last_ = new_first_ + size;
				pointer new_end_ = new_first_ + (capacity > size ? capacity : size);

				//Construct objects and fill with default value
				for (size_type i = 0; i < size; ++i)
					alloc_.construct(new_first_ + i, value);


				//Copy any existing elements to new array
				for (size_type i = 0; i < size && i < size(); ++i)
					new_first_[i] = first_[i]
				
				//Destroy old array
				for(size_type i = 0; i < size(); ++i)
					alloc_.destroy(&first_[i]);

				//Deallocate memory of old array and assign new pointers
				alloc_.deallocate(first_, end_ - first_);
				first_ = new_first_;
				last_ = new_last_;
				end_ = new_end_;
			}
		

			//Get the correct size for allocation
			//FIXME: can return a value greater than max_size()
			size_type	get_capacity(size_type count) {
				size_type n = count;
				if (count == 1)
					return n;
				for (int i = 0; i < sizeof(size_type); i++) {
					n |= n >> 1;
				}
				return n + 1;
			}

			
			void	check_in_range(size_type pos) {
				if (pos >= size() || pos < 0)
					throw std::out_of_range("");
				//Add error messaging?
			}

			
	};

	//Non-member functions

	// swap();
	// operator==();
	// operator!=();
	// operator<();
	// operator>();
	// operator<=();
	// operator>=();


}