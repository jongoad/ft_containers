#pragma once



namespace ft {


	//Enum for node colour
	enum node_colour_t {
		BLACK = true,
		RED = false
	} node_colour_e;


	//end_node
	template <typename T>
	class end_node;

	//node
	template <typename T>
	class node;

	//Node types
	template <typename T>
	struct node_types {
		typedef end_node<T>		end_node_type;
		typedef end_node_type*	end_node_pointer;
		typedef node<T>			node_type;
		typedef node_type*		node_pointer;
	};

	//end_node class definition
	template <typename T>
	class end_node {
		public:
			typedef typename node_types<T>::node_pointer node_pointer;

			//Constructor
			end_node() : left_(NULL) {}
			node_pointer left_;


	};

	//Node class definition
	template <typename T>
	class node : public node_types<T>::end_node_type {
		public:
			//Pointer typedefs
			typedef typename node_types<T>::node_pointer		node_pointer;
			typedef typename node_types<T>::end_node_pointer	end_node_pointer;

			//Constructor
			node() : right_(NULL), parent_(NULL), colour_(RED) {}

			//Methods
			node_pointer	get_parent() { return static_cast<node_pointer>(parent_); }
			void			set_parent(node_pointer ptr) { parent_ = static_cast<end_node_pointer>(ptr); }

			//Data
			node_pointer	right_;
			end_node_pointer	parent_;
			node_colour_t 	colour_;
			T value_;
	};






} //namespace ft