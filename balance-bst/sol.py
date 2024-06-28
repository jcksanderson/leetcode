# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
  def collapse_tree(self, root: TreeNode|None, array: List[int]) -> None:
    if root is not None:
      self.collapse_tree(root.left, array)
      array.append(root.val)
      self.collapse_tree(root.right, array)
  
  def insert(self, root: TreeNode, val: int):
    if val > root.val:
      if root.right is None:
        root.right = TreeNode(val, None, None)
      else:
        return self.insert(root.right, val)
    else:
      if root.left is None:
        root.left = TreeNode(val, None, None)
      else:
        return self.insert(root.left, val)

  def array_to_tree(self, root: TreeNode, array: List[int]):
    if len(array) == 0:
      return

    middle = len(array) // 2
    if root.val is None:
      root.val = array[middle]
    else:
      self.insert(root, array[middle])

    self.array_to_tree(root, array[middle + 1:])
    self.array_to_tree(root, array[:middle])

  def balanceBST(self, root: TreeNode) -> TreeNode:
    array = []
    self.collapse_tree(root, array)
    top = TreeNode(None, None, None)
    self.array_to_tree(top, array)
    return top
      
