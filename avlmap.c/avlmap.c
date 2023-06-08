#include "avlmap.h"

typedef struct node {
    void* key;
    size_t key_length;
    void* value;
    struct node* left;
    struct node* right;
    int height;
} node_t;

struct avlmap {
    node_t* root;
    size_t count;
    int (*comp_func)(void* key1, size_t key_length1, void* key2, size_t key_length2);
};

avlmap_t* avlmap_init(int (*comp_func)(void* key1, size_t key_length1, void* key2, size_t key_length2)) {
    avlmap_t* avlmap = (avlmap_t*)malloc(sizeof(avlmap_t));
    if (avlmap == NULL) {
        return NULL;
    }
    avlmap->root = NULL;
    avlmap->count = 0;
    avlmap->comp_func = comp_func;
    return avlmap;
}

int avlmap_clear_node(node_t* node) {
    if (node == NULL) {
        return 0;
    }
    avlmap_clear_node(node->left);
    avlmap_clear_node(node->right);
    free(node);
    return 0;
}

int avlmap_clear(avlmap_t* avlmap) {
    avlmap_clear_node(avlmap->root);
    avlmap->root = NULL;
}

int avlmap_free(avlmap_t* avlmap) {
    avlmap_clear(avlmap);
    free(avlmap);
    return 0;
}

node_t* new_node(void* key, size_t key_length, void* value, int height) {
    node_t* nn = (node_t*)malloc(sizeof(node_t));
    nn->key = key;
    nn->key_length = key_length;
    nn->value = value;
    nn->height = height;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
}

int get_height(node_t* root) {
    return root == NULL ? 0 : root->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

/*
  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
*/
node_t* left_rotate(node_t* z) {
    node_t* y = z->right;
    z->right = y->left;
    y->left = z;
    return y;
}

/*
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
*/
node_t* right_rotate(node_t* z) {
    node_t* y = z->left;
    z->left = y->right;
    y->right = z;
    return y;
}


node_t* avlmap_insert(avlmap_t* avlmap, node_t* root, void* key, size_t key_length, void* value) {
    if (root == NULL) {
        avlmap->count++;
        return new_node(key, key_length, value, 1);
    }
    int comp = avlmap->comp_func(key, key_length, root->key, root->key_length);
    if (comp == 0) {
        root->value = value;
        return root;
    }
    if (comp < 0) {
        root->left = avlmap_insert(avlmap, root->left, key, key_length, value);
    } else {
        root->right = avlmap_insert(avlmap, root->right, key, key_length, value);
    }
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int factor = get_height(root->left) - get_height(root->right);
    // Left-Left Case
    if (factor > 1 && avlmap->comp_func(key, key_length, root->left->key, root->left->key_length) < 0) {
        return right_rotate(root);
    }
    
    // Left-Right Case
    if (factor > 1 && avlmap->comp_func(key, key_length, root->left->key, root->left->key_length) > 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right-Right Case
    if (factor < -1 && avlmap->comp_func(key, key_length, root->right->key, root->right->key_length) > 0) {
        return left_rotate(root);
    }

    // Right-Left Case
    if (factor < -1 && avlmap->comp_func(key, key_length, root->right->key, root->right->key_length) < 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

int avlmap_set(avlmap_t* avlmap, void* key, size_t key_length, void* value) {
    if (avlmap == NULL || key == NULL) {
        return -1;
    }
    avlmap->root = avlmap_insert(avlmap, avlmap->root, key, key_length, value);
    return 0;
}

void* avlmap_get(avlmap_t* avlmap, void* key, size_t key_length) {
    if (avlmap == NULL || key == NULL) {
        return NULL;
    }
    node_t* curr = avlmap->root;
    while (curr != NULL) {
        int comp = avlmap->comp_func(key, key_length, curr->key, curr->key_length);
        if (comp == 0) {
            return curr->value;
        }
        if (comp < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}

int avlmap_del(avlmap_t* avlmap, void* key, size_t key_length) {
    // TODO
}

size_t avlmap_count(avlmap_t* avlmap) {
    return avlmap->count;
}

// below functions are used for validation only
void node_preorder(node_t* root) {
    if (root == NULL) return;
    printf(" %s: %s,", (char*)root->key, (char*)root->value);
    node_preorder(root->left);
    node_preorder(root->right);
}
void avlmap_preorder(avlmap_t* avlmap) {
    printf("preorder: [");
    node_preorder(avlmap->root);
    printf(" ]\n");
}
void node_inorder(node_t* root) {
    if (root == NULL) return;
    node_inorder(root->left);
    printf(" %s: %s,", (char*)root->key, (char*)root->value);
    node_inorder(root->right);
}
void avlmap_inorder(avlmap_t* avlmap) {
    printf("inorder: [");
    node_inorder(avlmap->root);
    printf(" ]\n");
}