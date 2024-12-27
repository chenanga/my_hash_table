//
// Created by 52768 on 2024/12/27.
//
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"

//
static ht_item* ht_new_item(const char *k, const char *v)
{
    ht_item *ht_new_item = malloc(sizeof(ht_item));
    ht_new_item->key = strdup(k);
    ht_new_item->value = strdup(v);
    return  ht_new_item;
}

static void ht_del_item(ht_item *i)
{
    free(i->key);
    free(i->value);
    free(i);
}


static int ht_hash(const char* strs, int prime, int num_buckets)
{
    long hash = 0;
    const int len_s = strlen(strs);
    for (int i = 0; i < len_s; ++i) {
        hash += (long)pow(prime, len_s - (i + 1)) * strs[i];
        hash = hash % num_buckets;
    }

    return (int)hash;
}

//
ht_hash_table * ht_new_hash_table()
{
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));

    return ht;
}

void ht_del_hash_table(ht_hash_table *ht)
{
    if (!ht) {
        return;
    }

    for (int i = 0; i < ht->size; ++i) {
        if (ht->items[i]) {
            ht_del_item(ht->items[i]);
        }
    }
    free(ht->items);
    free(ht);

}

