#include <stdio.h>
#include <string.h>
#include <math.h>

// int lengthOfLongestSubstring(char* s) {
// 	int len = strlen(s);
// 	int maxlen = 0;
// 
// 	for (int end = 0; end < len; end++) {
// 		for (int start = 0; start <= end; start++) {
// 			int sub_len = 0;
// 			unsigned char seen[256] = {0};
// 
// 			for (int pos = start; pos <= end; pos++) {
// 				if (seen[(int)s[pos]]) break;
// 				sub_len++;
// 				seen[(int)s[pos]]++;
// 			}
// 			if (sub_len > maxlen) maxlen = sub_len;
// 		}
// 	}
// 	return maxlen;
// }


int lengthOfLongestSubstring(char *s)
{
	int max_len = 0;
	int start = 0;
	int end = 0;
	int str_len = strlen(s);
	while (end < str_len) {
		int sub_len = 0;
		unsigned char seen[256] = {0};

		for (int pos = start; pos <= end; pos++) {
			if (seen[(int)s[pos]]) {
				start++;
				break;
			}
			sub_len++;
			seen[(int)s[pos]]++;
		}
		end++;
		if (sub_len > max_len) max_len = sub_len;
	}
	return max_len;
}

int main()
{
	int length = lengthOfLongestSubstring("abcabcbb");
	printf("Length: %d\n", length);

	int length_2 = lengthOfLongestSubstring("bbbbb");
	printf("Length 2: %d\n", length_2);

	int length_3 = lengthOfLongestSubstring("pwwkew");
	printf("Length 3: %d\n", length_3);
	return 0;
}
