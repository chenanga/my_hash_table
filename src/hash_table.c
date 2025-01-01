//
// Created by 52768 on 2024/12/27.
//
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

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

static int ht_get_hash(const char* strs, int num_buckets, const int attempt)
{
    const int hash_a = ht_hash(strs, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(strs, HT_PRIME_2, num_buckets);

    return (hash_a + attempt * (hash_b + 1)) % num_buckets;
}

static ht_hash_table * ht_new_sized_hash_table(const int base_size)
{
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));

    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}


//
ht_hash_table * ht_new_hash_table()
{
    return ht_new_sized_hash_table(HT_INITIAL_BASE_SIZE);
}

// 这里为了确保resize后原先的ht_hash_table指针仍然可用，需要把新的hash table中的相关元素替代过来
// 调整hash表的容量为指定值
static void ht_resize(ht_hash_table *ht, const int base_size)
{
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }

    ht_hash_table *new_ht = ht_new_sized_hash_table(base_size);
    for (int i = 0; i < ht->size; ++i) {
        if (ht->items[i] == NULL || ht->items[i] == &HT_DELETED_ITEM) {
            continue;
        }
        ht_insert(new_ht, ht->items[i]->key, ht->items[i]->value);
    }

    ht->size = new_ht->size;
    ht->base_size = new_ht->base_size;

    ht_item **tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;
    ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table *ht)
{
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void ht_resize_down(ht_hash_table *ht)
{
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
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

void ht_insert(ht_hash_table* ht, const char* key, const char* value)
{
    if (ht == NULL) {
        return;
    }
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    ht_item *it = ht_new_item(key, value);
    int attempt = 0;
    int index = ht_get_hash(key, ht->size, attempt++);
    while (ht->items[index] && ht->items[index] != &HT_DELETED_ITEM) {

        // 插入重复key会删除之前的item, 但是每次都判断会影响性能
        if (strcmp(ht->items[index]->key, key) == 0) {
            ht_del_item(ht->items[index]);
            ht->items[index] = it;
            return;
        }

        index = ht_get_hash(key, ht->size, attempt++);
    }
    ht->items[index] = it;
    ht->count++;
    return;
}

char* ht_search(ht_hash_table* ht, const char* key)
{
    int attempt = 0;
    int index = ht_get_hash(key, ht->size, attempt++);
    while (ht->items[index] && ht->items[index] != &HT_DELETED_ITEM && strcmp(ht->items[index]->key, key) != 0) {
        index = ht_get_hash(key, ht->size, attempt++);
    }

    if (ht->items[index]) {
        return ht->items[index]->value;
    }
    return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key)
{
    int attempt = 0;
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    int index = ht_get_hash(key, ht->size, attempt++);

    while (ht->items[index]) {
        if (ht->items[index] == &HT_DELETED_ITEM) {
            continue;
        }
        if (strcmp(ht->items[index]->key, key) == 0) {
            ht_del_item(ht->items[index]);
            ht->count --;
            ht->items[index] = &HT_DELETED_ITEM;
        }
        index = ht_get_hash(key, ht->size, attempt++);
    }

    return;
}

