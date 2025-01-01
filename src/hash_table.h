//
// Created by 52768 on 2024/12/27.
//

#ifndef MY_HASH_TABLE_HSAH_TABLE_H
#define MY_HASH_TABLE_HSAH_TABLE_H

#define HT_PRIME_1 1
#define HT_PRIME_2 2
#define HT_INITIAL_BASE_SIZE 51

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int size;
    int count;
    int base_size;
    ht_item **items;
} ht_hash_table;

ht_hash_table * ht_new_hash_table();
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
void ht_del_hash_table(ht_hash_table *ht);

#endif //MY_HASH_TABLE_HSAH_TABLE_H
