# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
  def collapse_tree(self, node: TreeNode|None) -> List[int]:
    if node.right is None:
      if node.left is None:
        return [node.val]
      return self.collapse_tree(node.left) + [node.val]

    elif node.left is None:
      return [node.val] + self.collapse_tree(node.right)

    return (self.collapse_tree(node.left) + 
            [node.val] + 
            self.collapse_tree(node.right))
   

  def to_gst(self, node: TreeNode|None, arr: list[int]) -> TreeNode:
    if node is None:
      return None
    
    return TreeNode(
      val = sum(arr[arr.index(node.val):]),
      left = self.to_gst(node.left, arr),
      right = self.to_gst(node.right, arr)
    )


  def bstToGst(self, root: TreeNode) -> TreeNode:
    arr = self.collapse_tree(root)
    return self.to_gst(root, arr)

