#define _SS_STACK_H
#include <stdio.h>
#include <stdlib.h>

#define STATIC_INLINE static inline

//root,tail
struct ST_STACK {
    struct STACK_NODE *r,*t;
};
struct STACK_NODE {
    struct STACK_NODE *next;
    void *ptr;
};

static struct ST_STACK stack;

STATIC_INLINE int insert_head(struct ST_STACK *s, void *ptr) {
    struct STACK_NODE *n = malloc(sizeof(struct STACK_NODE));
    n->next = NULL;
    n->ptr = ptr;

    if (!s->r) {
        s->r = s->t = n;
    }
    else {
        n->next = s->r;
        s->r = n;
    }
    return 0;
}

STATIC_INLINE void *pop_head(struct ST_STACK *s) {
    void *ret;
    struct STACK_NODE *n;
    if (!s->r)
        return NULL;
    else {
        n = s->r;
        ret = n->ptr;
        s->r = n->next;
        free(n);
    }
    return ret;
}

STATIC_INLINE void *peek_head(struct ST_STACK *s) {
    return s->r?s->r->ptr:NULL;
}

STATIC_INLINE int push_head(struct ST_STACK *s, void *ptr) {
    return insert_head(s, ptr);
}

STATIC_INLINE int push_tail(struct ST_STACK *s, void *ptr) {
    struct STACK_NODE *n = malloc(sizeof(struct STACK_NODE));
    n->next = NULL;
    n->ptr = ptr;
    if (!s->t) {
        s->r = s->t = n;
    } else {
        s->t->next = n;
        s->t = n;
    }
    return 0;
}

STATIC_INLINE int stack_empty(struct ST_STACK *s) {
    return (!s->r);
}
