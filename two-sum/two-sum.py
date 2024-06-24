class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        map = {}
        for idx, item in enumerate(nums):
            if target - item in map:
                return [map[target-item], idx]
            map[item] = idx
