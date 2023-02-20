#pragma once

#include <functional>
#include <memory>

#include "utility.hpp"
#include "tree/rb_tree.hpp"
#include "iterator.hpp"


namespace ft {

	//Compare adapter for rb_tree (compare only keys and not both values in pair)
	template <typename Key, typename T, typename Compare>
	class map_compare_adapter : std::binary_function<Key, Key, bool> {
		
		public:
			//Handle member types from std::binary_function
			typedef value_type first_argument_type;
      	 	typedef value_type second_argument_type;
       		typedef bool result_type;

			//Constructors
			map_compare_adapter() : comp_() {}
			map_compare_adapter(const Compare& c) : comp_(c) {}

			//Getter for comp_
			const Compare& key_comp() const { return comp_; }
			
			//Operator overloads

			//Handle all combinations of T and Key for overloading () operator
			//Do not need an overload for comparing Key with Key as that is what we want compared
			bool operator()(const T& first, const T& second) const {
				return key_comp()(first.first, second.first);
			}

			bool operator()(const Key& first, const T& second) const {
				return key_comp()(first, second.first);
			}

			bool operator()(const T& first, const Key& second) const {
				return key_comp()(first.first, second);
			}

			//Swap overload
			void	swap(map_compare_adapter& other) {
				std::swap(comp_, other.comp_);
			}


		protected:
			Compare comp_;
	};



	//map class definition
	template <typename Key, typename T, typename Compare = std::less<Key>,
		typename Allocator = std::allocator<pair<const Key, T> > >
	class map {
		//STL container typedefs
		public:
			typedef Key											key_type;
			typedef T											stored_type;
			typedef pair<const key_type,stored_type>			value_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;			
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

		private:
			typedef map_compare_adapter<key_type, value_type, key_compare>	adapted_compare;
			typedef rb_tree<value_type, adapted_compare, allocator_type>	base;
	
		//Iterator typedefs
		public:
			typedef typename base::iterator 				iterator;
			typedef typename base::const_iterator			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		//value_compare function object definition
		public:
			class value_compare : std::binary_function<value_type, value_type, bool> {
				friend class map;
				
				//Handle member types from std::binary_function
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				typedef bool result_type;

				public:
					bool	operator()(const value_type& first, const value_type& second) const {
						return comp_(first.first, second.first);
					}


				protected:
					value_compare(const key_compare& c) : comp_(c);
					key_compare comp_;
			};

		public:
			//Constructors & destructors
			map() : rb_tree_(adapted_compare()) {}

			explicit map(const key_compare& comp, allocator_type& alloc = allocator_type()) : rb_tree_(adapted_compare(comp), alloc) {}

			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
				: rb_tree_(adapted_compare(comp), alloc) {
				insert(first, last);
			}

			map(const map& other) : rb_tree_(other.rb_tree_) {}
			~map() {}


			const map& operator=(const map& other) {
				rb_tree_ = other.rb_tree_;
				return *this;
			}

			allocator_type get_allocator() const { return rb_tree_.get_alloctor(); }


			//Element access
			T& at(const key_type& key) {
				iterator it = find(key);
				if (it == end())
					throw std::out_of_range("Key not found");
				return it->second;
			}

			const T& at(const key_type& key) const {
				const_iterator it = find(key);
				if (it == end())
					throw std::out_of_range("Key not found");
				return (it->second);

			}

			//Why is mik inserting here?
			T& operator[](const key_type& key) {
				
			}  

			//Iterators
			iterator	begin() { return rb_tree_.begin(); }
			const_iterator	begin() const { return rb_tree_.begin(); };

			iterator	end() { return rb_tree_.end(); }
			const_iterator	end() const { return rb_tree_.end(); }

			reverse_iterator	rbegin() { return rb_tree_.end(); }
			const_reverse_iterator	rbegin() const { return rb_tree_.rbegin(); }

			reverse_iterator	rend() {return rb_tree_.rend(); } 
			const_reverse_iterator	rend() const { return rb_tree_.rend(); }

			//Capacity
			bool	empty() const { return rb_tree_.empty(); }
			size_type	size() const { return rb_tree_.size(); }
			size_type	max_size() const { return rb_tree_.max_size(); }

			//Modifiers
			void	clear() { rb_tree_.clear(); }

			template <typename InputIt>
			void insert(InputIt first, InputIt last) { rb_tree_.insert(first, last); }
			void erase(iterator pos) { rb_tree_.erase(pos); }
			void erase(const key_type& key) { rb_tree_.erase(key); }
			void erase(iterator first, iterator last) ( rb_tree_.erase(first, last); )


			void	swap(map& other) { rb_tree_.swap(other.rb_tree_); }

			//Lookup
			size_type	count(const key_type& key) const { return rb_tree_.count(key); }
			itertor	find(const key_type& key) { return rb_tree_.find(key); }

			pair<iterator, iterator>	equal_range(const key_type& key) {
				return rb_tree_.equal_range(key);
			}
			pair<const_iterator, const_iterator>	equal_range(const key_type& key) const {
				return rb_tree_.equal_range(key);
			}

			iterator	lower_bound(const key_type& key) {
				return rb_tree_.lower_bound(key);
			}
			const_iterator	lower_bound(const key_type& key) const {
				return rb_tree_.lower_bound(key);
			};

			iterator	upper_bound(const key_type& key) {
				return rb_tree_.upper_bound(key);
			}
			const_iterator	upper_bound(const key_type& key) const {
				return rb_tree_.upper_bound(key);
			}

			//Observers
			key_compare key_comp() const {
				return rb_tree_.value_comp().key_comp();
			}

			value_compare value_comp() const {
				return value_compare(rb_tree_.value_comp().key_comp());
			}



		private:
			base	rb_tree_;
	};

	//Non-member functions:

	// operator==();
	// operator!=();
	// operator<();
	// operator>();
	// operator<=();
	// operator>=();

	// ft::swap();

}; //namespace ft end