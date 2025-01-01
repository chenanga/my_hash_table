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


## 哈希

### 哈希函数
使用通用字符串哈希函数，如下伪代码 变量a为大于字母表大小的素数
```c
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i])
    hash = hash % num_buckets
    return hash
```
由于哈希函数将无限数量的输入映射到有限数量的输出。不同的输入键将映射到相同的数组索引，从而导致存储桶冲突。哈希表必须实现某种处理冲突的方法。
### 双重哈希
使用双重哈希开放寻址的方式处理冲突
```c
index = (hash_A(string) + i * hash_B(string)) % num_buckets
// 如果hash_b返回0，会导致陷入死循环
// 因此 i * (hash_B(string)  + 1)
index = (hash_A(string) + i * (hash_B(string) + 1)) % num_buckets
```

从开放地址哈希表中删除比插入或搜索更复杂。我们希望删除的项目可能是冲突链的​​一部分。从表中删除它会破坏该链，并且会使在链尾部找到项目变得不可能。为了解决这个问题，我们不是删除该项目，而是将其标记为已删除。

参考教程: https://github.com/jamesroutley/write-a-hash-table
