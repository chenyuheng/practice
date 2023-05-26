// define a hashmap class with type template

#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include <tuple>

template<class K, class V> struct Node;

template <typename K, typename V> class Hashmap {
private:
    int capacity;
    int count;
    struct Node<K, V> *table;
    int getIndex(K key);

public:
    Hashmap();
    Hashmap(int capacity);
    ~Hashmap();
    int put(K key, V value);
    V get(K key);
    int remove(K key);
    int size();
};

#endif // HASHMAP_HPP