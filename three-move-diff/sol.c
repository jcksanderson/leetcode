#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int *)a - *(int *)b );
}

int minDifference(int* nums, int numsSize) {
  if (numsSize <= 4)
    return 0;
  
  qsort(nums, numsSize, sizeof(int), cmpfunc);

  int min = 2147483647;

  for (int i = 0; i < 4; i++) {
    int diff = nums[numsSize - 4 + i] - nums[i];
    if (diff < min) min = diff;
  }
  return min;
}

int main() 
{
  return 0;
}
