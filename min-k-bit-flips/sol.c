#include <stdio.h>
#include <stdlib.h>

void print_arr(int *nums, int size)
{
  for (int i = 0; i < size; i++) {
    fprintf(stderr, "%d:", nums[i]);
  }
  printf("\n");
}

int sum_arr(int *nums, int size)
{
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += nums[i];
  }
  return sum;
}

int minKBitFlips(int* nums, int numsSize, int k)
{
  int flips = 0;

  for (int i = 0; i < numsSize; i++) {
    if (nums[i] == 0) {
      if (i + k > numsSize) return -1;
      for (int j = i; j < i + k; j++) {
        nums[j] = !nums[j];
      }
      printf("flip\n");
      flips++;
      print_arr(nums, numsSize);
      continue;
    }

    if (sum_arr(nums, numsSize) == numsSize) {
      printf("returning positive\n");
      return flips;
    }
    print_arr(nums, numsSize);
  }
  if (sum_arr(nums, numsSize) == numsSize) return flips;
  return -1;
}



int main() {
  // int nums[] = {0,0,0,1,0,1,1,0};
  // int flips = minKBitFlips(nums, 8, 3);
  // printf("Flips: %d\n", flips);
  int nums[] = {0,1,1};
  int flips = minKBitFlips(nums, 3, 1);
  printf("Flips: %d\n", flips);
  return 0;
}
