# c 语言从 0 实现 hash table 

## api
search(a, k): return the value v associated with key k from the associative array a, or NULL if the key does not exist.
insert(a, k, v): store the pair k:v in the associative array a.
delete(a, k): delete the k:v pair associated with k, or do nothing if k does not exist.

## Terminology
Associative array: 也称为map, 实现上述api的抽象数据结构
Hash table: 使用哈希函数的关联数组的快速映射

## code structure
```
.
├── build
└── src
    ├── hash_table.c
    ├── hash_table.h
    ├── prime.c
    └── prime.h
```


参考教程: https://github.com/jamesroutley/write-a-hash-table
