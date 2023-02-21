#pragma once

#include "rb_tree_types.hpp"
#include "rb_tree.hpp"

namespace ft {

	//Check if current node is the left child of parent
	template <typename Node_Pointer>
	bool rb_is_left_child(Node_Pointer ptr) {
		return ptr == ptr->parent_->left_;
	}

	//Get smallest node from current node
	template <typename Node_Pointer>
	Node_Pointer	rb_tree_get_min(Node_Pointer ptr) {
		while (ptr->left_ != NULL)
			ptr = ptr->left_;
		return ptr;
	}

	//Get largest node from current node
	template <typename Node_Pointer>
	Node_Pointer	rb_tree_get_max(Node_Pointer ptr) {
		while (ptr->right_ != NULL)
			ptr = ptr->right_;
		return ptr;
	}

	//Get next iter
	template <typename Node_Pointer>
	Node_Pointer rb_next(Node_Pointer ptr) {
		
		//If not at bottom of tree, get min from current node
		if (ptr->right_ != NULL)
			return rb_tree_get_min(ptr);
		
		//Else go up until no longer left child and return parent
		while (!rb_is_left_child(ptr))
			ptr = ptr->get_parent();
		
		return ptr->get_parent();

	}

	//Get prev iter
	template <typename Node_Pointer>
	Node_Pointer rb_prev(Node_Pointer ptr) {
		//If not at bottom of tree, get max from current node
		if (ptr->left_ != NULL)
			return rb_tree_get_max(ptr);
		
		//Else go up until no longer right child and return parent
		while (rb_is_left_child(ptr))
			ptr = ptr->get_parent();
		
		return ptr->get_parent();
	}


	/*

	Insertion always happens at leaf.
	If root is endnode/NULL then insert at root.

	Cases for Insertion:

	All newly inserted nodes are set to RED unless it is root node, then set to BLACK.



	If Uncle is red:

	1. Change colour of parent and uncle to black
	2. Change colour of grandpa to red. (if grandfather is root, dont change colour)
	3. Move to grandfather and repear steps 1-2 as if grandpa is the new focus node.
	4. Repeat step 3 until top of tree is reached



	If Uncle is black:

	Left Left Case
	1. Right rotation of grandfather
	2. Swap colours of grandfather and parent 

	Left Right Case
	1. Left rotation of parent
	2. Run left left case

	Right Right Case
	1. Left rotation of grandfather
	2. Swap colours of grandfather and parent

	Right Left Case
	1. Right rotate parent
	2. Run right right case
	
	
	*/


	//Rotate tree left
	template <typename Node_Pointer>
	void	rb_rotate_left() {

	}




	//Rotate tree right
	template <typename Node_Pointer>
	void	rb_rotate_right() {

	}

	//Rebalance

	//Handle edge cases








} //namespace ft