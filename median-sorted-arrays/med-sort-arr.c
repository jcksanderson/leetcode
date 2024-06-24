#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
  int val;
  int val_prev;
  int loc_1 = 0;
  int loc_2 = 0;

  int odd = (nums1Size + nums2Size) % 2 == 1;
  int med_idx = (nums1Size + nums2Size) / 2;

  /* i previously had the first two conditionals checked in a 
  logical or. it worked fine on my computer but leetcode did 
  not like it, so i separated them out. probably an early 
  evaluation issue. */
  for (int i = 0; i <= med_idx; i++) {
    if (loc_2 == nums2Size) {
      val_prev = val;
      val = nums1[loc_1];
      loc_1++;
    } else if (loc_1 == nums1Size) {
      val_prev = val;
      val = nums2[loc_2];
      loc_2++;
    } else if (nums1[loc_1] < nums2[loc_2])  {
      val_prev = val;
      val = nums1[loc_1];
      loc_1++;
    } else {
      val_prev = val;
      val = nums2[loc_2];
      loc_2++;
    }
  }
  if (odd) return val;
  return (val + val_prev) / 2.0;
}

int main() 
{
  int arr1[] = {1, 3};
  int arr2[] = {2};
  double res = findMedianSortedArrays(arr1, 2, arr2, 1);
  printf("res: %f\n", res);
  return 0;
}
