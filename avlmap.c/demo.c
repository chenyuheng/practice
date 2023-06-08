#include "avlmap.h"
#include <string.h>

int str_cmp(void* s1, size_t l1, void* s2, size_t l2) {
    return strcmp(s1, s2);
}

int main() {
    avlmap_t* map = avlmap_init(str_cmp);
    printf("set apple pingguo: %d\n", avlmap_set(map, "apple", 0, "pingguo"));
    avlmap_preorder(map);
    avlmap_inorder(map);
    printf("set banana xiangjiao: %d\n", avlmap_set(map, "banana", 0, "xiangjiao"));
    avlmap_preorder(map);
    avlmap_inorder(map);
    printf("set cherry yingtao: %d\n", avlmap_set(map, "cherry", 0, "yingtao"));
    avlmap_preorder(map);
    avlmap_inorder(map);
    printf("set orange juzi: %d\n", avlmap_set(map, "orange", 0, "juzi"));
    avlmap_preorder(map);
    avlmap_inorder(map);
    printf("set pear li: %d\n", avlmap_set(map, "pear", 0, "li"));
    avlmap_preorder(map);
    avlmap_inorder(map);
    printf("count: %d\n", avlmap_count(map));
    printf("get apple: %s\n", (char*)avlmap_get(map, "apple", 0));
    printf("get banana: %s\n", (char*)avlmap_get(map, "banana", 0));
    printf("get cherry: %s\n", (char*)avlmap_get(map, "cherry", 0));
    printf("get orange: %s\n", (char*)avlmap_get(map, "orange", 0));
    printf("get pear: %s\n", (char*)avlmap_get(map, "pear", 0));
    printf("get watermelon: %s\n", (char*)avlmap_get(map, "watermelon", 0));
}
