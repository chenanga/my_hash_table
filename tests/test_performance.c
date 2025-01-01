//
// Created by 52768 on 2025/1/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_table.h"

void performance_test() {
    const int num_items = 100000;
    ht_hash_table *ht = ht_new_hash_table();

    // 插入测试
    clock_t start_insert = clock();
    for (int i = 0; i < num_items; i++) {
        char key[20];
        char value[20];
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        ht_insert(ht, key, value);
    }
    clock_t end_insert = clock();
    double insert_time = (double)(end_insert - start_insert) / CLOCKS_PER_SEC;
    printf("Insertion of %d items took %f seconds.\n", num_items, insert_time);

    // 查找测试
    clock_t start_search = clock();
    for (int i = 0; i < num_items; i++) {
        char key[20];
        sprintf(key, "key%d", i);
        char *value = ht_search(ht, key);
        if (value == NULL) {
            printf("Error: Missing key %s\n", key);
        }
    }
    clock_t end_search = clock();
    double search_time = (double)(end_search - start_search) / CLOCKS_PER_SEC;
    printf("Search of %d items took %f seconds.\n", num_items, search_time);

    ht_del_hash_table(ht);
}

int main() {
    performance_test();
    return 0;
}
