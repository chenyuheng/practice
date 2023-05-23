#include "hashmap.h"
#include <string.h>

uint64_t user_hash_func(void* key, size_t key_length) {
    uint64_t hash_value = 0;
    size_t length = strlen((char*) key);
    for (int i = 0; i < length; i++) {
        hash_value += ((char*) key)[i] * i;
    }
    return hash_value;
}

int user_comp_func(void* key1, size_t key_length1, void* key2, size_t key_length2) {
    return strcmp((char*) key1, (char*) key2);
}

int main() {
    hashmap_t* hashmap;
    size_t count;
    char* value;
    int ret;
    
    hashmap = hashmap_init(2, user_hash_func, user_comp_func);
    count = hashmap_count(hashmap);
    printf("count: %zu\n", count);

    ret = hashmap_set(hashmap, "apple", 0, "pingguo");
    printf("set apple pingguo: %d\n", ret);

    ret = hashmap_set(hashmap, "banana", 0, "xiangjiao");
    printf("set banana xiangjiao: %d\n", ret);

    ret = hashmap_set(hashmap, "orange", 0, "chengzi");
    printf("set orange chengzi: %d\n", ret);

    value = (char*) hashmap_get(hashmap, "apple", 0);
    printf("get apple: %s\n", value);

    value = (char*) hashmap_get(hashmap, "banana", 0);
    printf("get banana: %s\n", value);

    value = (char*) hashmap_get(hashmap, "orange", 0);
    printf("get orange: %s\n", value);

    value = (char*) hashmap_get(hashmap, "pear", 0);
    printf("get pear is NULL: %d\n", value == NULL);

    count = hashmap_count(hashmap);
    printf("count: %zu\n", count);

    ret = hashmap_del(hashmap, "orange", 0);
    printf("del orange: %d\n", ret);

    ret = hashmap_del(hashmap, "apple", 0);
    printf("del apple: %d\n", ret);

    value = hashmap_get(hashmap, "apple", 0);
    printf("get apple is NULL: %d\n", value == NULL);

    count = hashmap_count(hashmap);
    printf("count: %zu\n", count);
}
/*
output:
count: 0
set apple pingguo: 0
set banana xiangjiao: 0
set orange chengzi: 2
get apple: pingguo
get banana: xiangjiao
get orange: chengzi
get pear is NULL: 1
count: 3
del orange: 2
del apple: 1
get apple is NULL: 1
count: 1
*/