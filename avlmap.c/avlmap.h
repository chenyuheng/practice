#ifndef AVLMAP_H
#define AVLMAP_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct avlmap;
typedef struct avlmap avlmap_t;

avlmap_t* avlmap_init(int (*comp_func)(void* key1, size_t key_length1, void* key2, size_t key_length2));
int avlmap_clear(avlmap_t* avlmap);
int avlmap_free(avlmap_t* avlmap);

int avlmap_set(avlmap_t* avlmap, void* key, size_t key_length, void* value);
void* avlmap_get(avlmap_t* avlmap, void* key, size_t key_length);
int avlmap_del(avlmap_t* avlmap, void* key, size_t key_length);

size_t avlmap_count(avlmap_t* avlmap);

// used for validation only
void avlmap_preorder(avlmap_t* avlmap);
void avlmap_inorder(avlmap_t* avlmap);

#endif