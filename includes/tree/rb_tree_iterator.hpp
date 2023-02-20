#pragma once


namespace ft {


	//Same as vector, create const interators, then base non-const iterators off of them

	//Iterator setup is completely dependant on how we choose to implement the tree


	//Iterator needs to traverse down left-side of tree, then back up and down each right node

} //namespace ft


/* In order traversal

sub InOrder(TreeNode)
   If LeftPointer(TreeNode) != NULL Then
      InOrder(TreeNode.LeftNode)
   Output(TreeNode.value)
   If RightPointer(TreeNode) != NULL Then
      InOrder(TreeNode.RightNode)
end sub


reverse iterator would be the opposite of this.

In order to use find() we check at each node if the value of the key is greater or less than the current node key.
If value is less, we go left, else we go right
*/