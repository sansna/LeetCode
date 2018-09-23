#define _SS_HASH_H
#include <stdio.h>
//malloc
#include <stdlib.h>

#define BUCKETS 100

struct HASH {
    char *name;
    struct HASH_NODE *r;
};
struct HASH_NODE {
    struct HASH_LST *p[BUCKETS];
};
struct HASH_LST {
    int key;
    void *value;
    struct HASH_LST *next;
};
