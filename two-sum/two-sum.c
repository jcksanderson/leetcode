#include <stdio.h>
#include <stdlib.h>

// hash function takes in an integer (array item)
// in the hash bin is the index

typedef struct hashed_item {
    int item;
    int index;
    struct hashed_item *next;
} hashed_item;

typedef struct hash_table {
    hashed_item **buckets;
    uint32_t n_buckets;
    uint64_t(*hash)(int);
} hash_table;

hash_table *ht_new(uint32_t n, uint64_t(*h)(int))
{
    hash_table *t = malloc(sizeof(hash_table));
    if (!t) {
        fprintf(stderr, "ht_new malloc failed");
        exit(1);
    }
    t->n_buckets = n;
    t->hash = h;
    t->buckets = calloc(n, sizeof(hashed_item *));
    if (!t->buckets) {
        fprintf(stderr, "ht_new second malloc failed");
        exit(1);
    }
    return t;
}

// returns the *index* associated with an item in the array
int *ht_lookup(hash_table *ht, int item)
{
    uint64_t hash_code = (ht->hash)(item);
    uint32_t bucket_index = hash_code % ht->n_buckets;
    hashed_item *bucket = ht->buckets[bucket_index];

    while (bucket) {
        if (bucket->item == item)
            return &(bucket->index);
        bucket = bucket->next;
    }
    return NULL;
}

// inserts item (and index along with it) into hash table
void ht_insert(hash_table *ht, int item, int index)
{
    uint64_t hash_code = (ht->hash)(item);
    uint32_t bucket_index = hash_code % ht->n_buckets;
    hashed_item *bucket = ht->buckets[bucket_index];
    hashed_item *new_entry = malloc(sizeof(hashed_item));
    new_entry->item = item;
    new_entry->index = index;
    new_entry->next = NULL;

    if (!bucket) {
        ht->buckets[bucket_index] = new_entry;
    } else {
        new_entry->next = bucket;
        ht->buckets[bucket_index] = new_entry;
    }
}

// stolen from stackoverflow
uint64_t hash(int x) {
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int *res = malloc(sizeof(int) * 2);
    *returnSize = 2;
    // declare hash table
    hash_table *table = ht_new(1000, *hash);

    for (int i = 0; i < numsSize; i++) {
        int *lookup = ht_lookup(table, target - nums[i]);
        if (lookup) {
            res[0] = *lookup;
            res[1] = i;
            return res;
        }
        ht_insert(table, nums[i], i);
    }

    return NULL;
}

int main()
{
    return 0;
}
