//
// Created by 52768 on 2025/1/1.
//
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hash_table.h"

void test_ht_insert_and_search() {
    ht_hash_table *ht = ht_new_hash_table();
    ht_insert(ht, "key1", "value1");
    ht_insert(ht, "key2", "value2");
    ht_insert(ht, "key3", "value3");

    assert(strcmp(ht_search(ht, "key1"), "value1") == 0);
    assert(strcmp(ht_search(ht, "key2"), "value2") == 0);
    assert(strcmp(ht_search(ht, "key3"), "value3") == 0);

    ht_del_hash_table(ht);
    printf("test_ht_insert_and_search passed.\n");
}

void test_ht_delete() {
    ht_hash_table *ht = ht_new_hash_table();
    ht_insert(ht, "key1", "value1");
    ht_delete(ht, "key1");

    assert(ht_search(ht, "key1") == NULL);

    ht_del_hash_table(ht);
    printf("test_ht_delete passed.\n");
}

void test_ht_resize() {
    ht_hash_table *ht = ht_new_hash_table();
    for (int i = 0; i < 100; i++) {
        char key[10];
        char value[10];
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        ht_insert(ht, key, value);
    }

    for (int i = 0; i < 100; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        assert(ht_search(ht, key) != NULL);
    }

    ht_del_hash_table(ht);
    printf("test_ht_resize passed.\n");
}

int main() {
    test_ht_insert_and_search();
    test_ht_delete();
    test_ht_resize();
    return 0;
}
