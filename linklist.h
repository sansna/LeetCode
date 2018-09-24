#define _SS_LINKLIST_H
#include <stdio.h>
//malloc
#include <stdlib.h>

#define STATIC_INLINE static inline

struct LinkList {
    struct LinkListNode *r;
    int len;
};
struct LinkListNode {
    struct LinkListNode *next;
    int value;
};

//XXX: global
// if specified static, each file uses its own copy of the global variable;
// if not static, each file uses the same variable.
static struct LinkList ll;

//XXX: always use STATIC_INLINE in header files.
STATIC_INLINE void *linklist_findtail(struct LinkList *l) {
    struct LinkListNode *n;
    if (!l->r) {
        return &(l->r);
    } else {
        n = l->r;
        while (n) {
            if (n->next) n = n->next;
            else return &(n->next);
        }
    }
    return NULL;
}

STATIC_INLINE int linklist_append(int value) {
    struct LinkListNode **t = linklist_findtail(&ll);
    struct LinkListNode *n = malloc(sizeof(struct LinkListNode));
    n->next= NULL;
    n->value = value;
    *t = n;
    ll.len++;
    return 0;
}

STATIC_INLINE int linklist_modify(struct LinkListNode *n, int value) {
    n->value = value;
    return 0;
}

STATIC_INLINE int linklistnode_free(struct LinkListNode *n) {
    if (n->next)
        linklistnode_free(n->next);
    free(n);
    return 0;
}

STATIC_INLINE int linklist_free(struct LinkList *l) {
    if (l->r)
        linklistnode_free(l->r);
    l->len = 0;
    return 0;
}

STATIC_INLINE int linklistnode_print(struct LinkListNode *n) {
    fprintf(stdout, "%d,", n->value);
    if (n->next)
        linklistnode_print(n->next);
    return 0;
}

STATIC_INLINE int linklist_print(struct LinkList *l) {
    if (l->r)
        linklistnode_print(l->r);
    fprintf(stdout, "\b \n");
    return 0;
}

STATIC_INLINE int linklist_reverse(struct LinkList *l) {
    struct LinkListNode *n,*m,*t;
    if (!l->r) {
        return 0;
    }
    n = l->r;
    t = NULL;
    while (n->next) {
        m = n->next;
        n->next = t;
        t = n;
        n = m;
    }
    if (!n->next) {
        n->next = t;
        l->r = n;
    }
    return 0;
}
