#include <stdio.h>

/* Given an array of integers nums and an integer limit, return the size of the 
longest non-empty subarray such that the absolute difference between any two 
elements of this subarray is less than or equal to limit. */

int longestSubarray(int* nums, int numsSize, int limit) {
  int max_len = 0;
  int start = 0;
  int pos = 0;

  int min_idx = -1;
  int max_idx = -1;
  int sub_len = 0;

  while (pos < numsSize) {
    for (pos = start; pos < numsSize; pos++) {

      if (min_idx == -1) {
        min_idx = pos;
        max_idx = pos;
      } else if (nums[pos] <= nums[min_idx]) {
        min_idx = pos;
      } else if (nums[pos] >= nums[max_idx]) {
        max_idx = pos;
      }

      if (nums[max_idx] - nums[min_idx] > limit) {
        if (max_idx == pos) {
          start = min_idx + 1;
        } else {
          start = max_idx + 1;
        }
        min_idx = -1;
        max_idx = -1;
        break;
      }
      sub_len++;
    }
    if (sub_len > max_len) max_len = sub_len;
    sub_len = 0;
  }
  return max_len;
}

int main() {
  int my_array[100000] = { 0 };
  for (int i = 0; i < 99998; i++) {
    my_array[i] = 1;
  }
  my_array[99998] = 11;
  my_array[99999] = 12;
  int res = longestSubarray(my_array, 100000, 1);
  printf("Result: %d\n", res);

  int array_2[4] = {8, 2, 4, 7};
  int res_2 = longestSubarray(array_2, 4, 4);
  printf("Second result: %d\n", res_2);
  return 0;
}

// Too slow below!

// int longestSubarray(int* nums, int numsSize, int limit) {
//   int max_len = 0;
//   int start = 0;
//   int end = 0;
//
//   int min = 0;
//   int max = 0;
//
//   while (end < numsSize) {
//     int sub_len = 0;
//     
//     for (int pos = start; pos <= end; pos++) {
//       if (nums[pos] < min || min == 0) min = nums[pos];
//       if (nums[pos] > max) max = nums[pos];
//
//       if (max - min > limit) {
//         start++;
//         min = 0;
//         max = 0;
//         break;
//       }
//       sub_len++;
//     }
//     end++;
//     if (sub_len > max_len) max_len = sub_len;
//   }
//   return max_len;
// }
