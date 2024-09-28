#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds.h"

size_t hash_string(const void *key, size_t size) {
    (void)size;
    char *const *_key = key;
    return fvn1a_hash(*_key, strlen(*_key));
}

int cmp_string(const void *a, const void *b, size_t size) {
    (void)size;
    char *const *_a = a;
    char *const *_b = b;
    return strcmp(*_a, *_b);
}

int main(void) {
    HashMap(const char *, int) map = NULL;
    HashMapDesc desc = hash_map_desc_default(map);
    desc.hash = hash_string;
    desc.cmp = cmp_string;
    hash_map_new(map, desc);

    for (size_t i = 0; i < 64; i++) {
        char *str = malloc(8);
        snprintf(str, 8, "id-%zu", i);
        hash_map_insert(map, str, i);
    }

    for (size_t i = 0; i < 64; i += 2) {
        char str[8];
        snprintf(str, 8, "id-%zu", i);
        HashMapIter i = hash_map_remove(map, str);
        free((void *) map[i].key);
    }

    for (HashMapIter iter = hash_map_iter_new(map);
        hash_map_iter_valid(map, iter);
        iter = hash_map_iter_next(map, iter)) {
        printf("%s: %d\n", map[iter].key, map[iter].value);
        free((void *) map[iter].key);
    }

    hash_map_free(map);

    return 0;
}
