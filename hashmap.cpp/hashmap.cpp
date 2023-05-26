#include "hashmap.hpp"

#include <iostream>

template<class K, class V>
struct Node {
    struct Node<K, V> *next;
    bool isNull;
    K key;
    V value;
};

template<class K, class V>
Hashmap<K, V>::Hashmap() {
    Hashmap<K, V>(16);
}

template<class K, class V>
Hashmap<K, V>::Hashmap(int capacity) {
    this->capacity = capacity;
    this->count = 0;
    this->table = new struct Node<K, V>[capacity];
    for (int i = 0; i < capacity; i++) {
        this->table[i].isNull = true;
        this->table[i].next = nullptr;
    }
}

template<class K, class V>
Hashmap<K, V>::~Hashmap() {
    delete[] this->table;
}

template<class K, class V>
int Hashmap<K, V>::getIndex(K key) {
    int hash = std::hash<K>{}(key);
    return (hash % this->capacity + this->capacity) % (this->capacity);
}

template<class K, class V>
int Hashmap<K, V>::put(K key, V value) {
    int index = this->getIndex(key);
    struct Node<K, V> *node = &this->table[index];
    if (node->isNull) {
        node->isNull = false;
        node->key = key;
        node->value = value;
        this->count++;
        return 1;
    }
    struct Node<K, V> *prev = nullptr;
    struct Node<K, V> *curr = node;
    while (curr != nullptr) {
        if (curr->key == key) {
            curr->value = value;
            return 2;
        }
        prev = curr;
        curr = curr->next;
    }
    struct Node<K, V> *newNode = new struct Node<K, V>();
    newNode->isNull = false;
    newNode->key = key;
    newNode->value = value;
    prev->next = newNode;
    this->count++;
    return 3;
}

template<class K, class V>
V Hashmap<K, V>::get(K key) {
    int index = this->getIndex(key);
    struct Node<K, V> *node = &this->table[index];
    if (node->isNull) {
        throw "key not found";
    }
    struct Node<K, V> *curr = node;
    while (curr != nullptr) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    throw "key not found";
}

template<class K, class V>
int Hashmap<K, V>::remove(K key) {
    int index = this->getIndex(key);
    struct Node<K, V> *node = &this->table[index];
    if (node->isNull) {
        return 0;
    }
    struct Node<K, V> *prev = nullptr;
    struct Node<K, V> *curr = node;
    while (curr != nullptr) {
        if (curr->key == key) {
            if (prev == nullptr) {
                this->table[index] = *curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            this->count--;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 2;
}

template<class K, class V>
int Hashmap<K, V>::size() {
    return this->count;
}
