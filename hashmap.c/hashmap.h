#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct hashmap;
typedef struct hashmap hashmap_t;

hashmap_t* hashmap_init(size_t capacity, uint64_t (*hash_func)(void* key, size_t key_length),
                        int (*comp_func)(void* key1, size_t key_length1, void* key2, size_t key_length2));
int hashmap_clear(hashmap_t* hashmap);
int hashmap_free(hashmap_t* hashmap);

int hashmap_set(hashmap_t* hashmap, void* key, size_t key_length, void* value);
void* hashmap_get(hashmap_t* hashmap, void* key, size_t key_length);
int hashmap_del(hashmap_t* hashmap, void* key, size_t key_length);

size_t hashmap_count(hashmap_t* hashmap);

#endif
