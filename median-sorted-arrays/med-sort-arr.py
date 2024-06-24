class Solution:
  def merge(self, lst1: List[int], lst2: List[int]) -> List[int]:
    if lst1 == []:
      return lst2
    elif lst2 == []:
      return lst1

    first_1, *rest_1 = lst1
    first_2, *rest_2 = lst2
    if first_1 < first_2:
      return [first_1] + self.merge(rest_1, lst2)
    return [first_2] + self.merge(lst1, rest_2)

  def median(self, lst1: List[int]) -> int:
    if len(lst1) % 2 == 1:
      return lst1[len // 2]
    idx = len / 2
    return (lst1[idx] + lst1[idx + 1]) / 2

  def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
    return median(self.merge(nums1, nums2))
