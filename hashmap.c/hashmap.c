#include "hashmap.h"

struct node {
    void* key;
    size_t key_length;
    void* value;
    struct node* next;
};

typedef struct node node_t;

struct hashmap {
    size_t capacity;
    size_t size;
    node_t** array;
    uint64_t (*hash_func)(void* key, size_t key_length);
    int (*comp_func)(void* key1, size_t key_length1, void* key2, size_t key_length2);
};

hashmap_t* hashmap_init(size_t capacity, uint64_t (*hash_func)(void* key, size_t key_length),
                        int (*comp_func)(void* key1, size_t key_length1, void* key2, size_t key_length2)) {
    hashmap_t* hashmap = (hashmap_t*) malloc(sizeof(hashmap_t));
    hashmap->capacity = capacity;
    hashmap->size = 0;
    hashmap->array = (node_t**) malloc(sizeof(node_t*) * capacity);
    for (int i = 0; i < capacity; i++) {
        hashmap->array[i] = NULL;
    }
    hashmap->hash_func = hash_func;
    hashmap->comp_func = comp_func;
    return hashmap;
}

int hashmap_clear(hashmap_t* hashmap) {
    for (int i = 0; i < hashmap->capacity; i++) {
        node_t* current = hashmap->array[i];
        while (current != NULL) {
            node_t* next = current->next;
            free(current);
            current = next;
        }
    }
    return 0;
}

int hashmap_free(hashmap_t* hashmap) {
    free(hashmap->array);
    free(hashmap);
    return 0;
}

int hashmap_set(hashmap_t* hashmap, void* key, size_t key_length, void* value) {
    uint64_t hash_value = hashmap->hash_func(key, key_length);
    size_t index = hash_value % hashmap->capacity;
    if (hashmap->array[index] == NULL) {
        hashmap->array[index] = (node_t*) malloc(sizeof(node_t));
        hashmap->array[index]->key = key;
        hashmap->array[index]->key_length = key_length;
        hashmap->array[index]->value = value;
        hashmap->array[index]->next = NULL;
        hashmap->size++;
        return 0;
    }
    node_t* current = hashmap->array[index];
    while(current != NULL) {
        if (hashmap->comp_func(key, key_length, current->key, current->key_length) == 0) {
            current->key = key;
            current->key_length = key_length;
            current->value = value;
            return 1;
        }
        if (current->next == NULL) {
            break;
        }
        current = current->next;
    }
    current->next = (node_t*) malloc(sizeof(node_t));
    current->next->key = key;
    current->next->key_length = key_length;
    current->next->value = value;
    current->next->next = NULL;
    hashmap->size++;
    return 2;
}

void* hashmap_get(hashmap_t* hashmap, void* key, size_t key_length) {
    uint64_t hash_value = hashmap->hash_func(key, key_length);
    size_t index = hash_value % hashmap->capacity;
    node_t* current = hashmap->array[index];
    while (current != NULL) {
        if (hashmap->comp_func(key, key_length, current->key, current->key_length) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

// TODO: implement it
int hashmap_del(hashmap_t* hashmap, void* key, size_t key_length) {
    uint64_t hash_value = hashmap->hash_func(key, key_length);
    size_t index = hash_value % hashmap->capacity;
    node_t* current = hashmap->array[index];
    if (hashmap->comp_func(key, key_length, current->key, current->key_length) == 0) {
        hashmap->array[index] = current->next;
        free(current);
        hashmap->size--;
        return 1;
    }
    node_t* previous = current;
    current = current->next;
    while (current != NULL) {
        if (hashmap->comp_func(key, key_length, current->key, current->key_length) == 0) {
            previous->next = current->next;
            free(current);
            hashmap->size--;
            return 2;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

size_t hashmap_count(hashmap_t* hashmap) {
    return hashmap->size;
}

