/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

typedef struct ListNode ListNode;

struct ListNode* il_cons(int f, ListNode *r)
{
    ListNode *l = malloc(sizeof(ListNode));
    if (!l) {
        fprintf(stderr, "il_cons malloc failed");
        exit(1);
    }
    l->val = f;
    l->next = r;
    return l;
}

void il_show(ListNode *nums)
{
    if (!nums) {
        printf("nil\n");
    } else {
        printf("%d:", nums->val);
        il_show(nums->next);
    }
}

ListNode *add_two_helper(ListNode *l1, ListNode *l2, int overflow)
{
    if (!l1 && !l2 && overflow == 0) return NULL;
    int total = overflow;
    total += l1 ? l1->val : 0;
    total += l2 ? l2->val : 0;
    
    ListNode *l1_next = l1 ? (l1->next ? l1->next : NULL) : NULL;
    ListNode *l2_next = l2 ? (l2->next ? l2->next : NULL) : NULL;

    if (total < 10) {
        return il_cons(total, add_two_helper(l1_next, l2_next, 0));
    } else {
       return il_cons(total % 10, add_two_helper(l1_next, l2_next, total / 10));
    }
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    return add_two_helper(l1, l2, 0);
}

int main() {
    ListNode *l1 = il_cons(2, il_cons(4, il_cons(7, NULL)));
    ListNode *l2 = il_cons(5, il_cons(4, il_cons(4, NULL)));
    ListNode *res = addTwoNumbers(l1, l2);
    il_show(res);

    ListNode *l3 = il_cons(2, il_cons(4, il_cons(3, NULL)));
    ListNode *l4 = il_cons(5, il_cons(6, il_cons(4, NULL)));
    ListNode *res_2 = addTwoNumbers(l3, l4);
    il_show(res_2);
    return 0;
}
