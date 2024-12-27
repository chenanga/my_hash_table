//
// Created by 52768 on 2024/12/27.
//

#ifndef MY_HASH_TABLE_HSAH_TABLE_H
#define MY_HASH_TABLE_HSAH_TABLE_H

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int size;
    int count;
    ht_item **items;
} ht_hash_table;

ht_hash_table * ht_new_hash_table();

void ht_del_hash_table(ht_hash_table *ht);

#endif //MY_HASH_TABLE_HSAH_TABLE_H
