#define _SS_TREE_H
#include <stdio.h>
//malloc
#include <stdlib.h>

#ifndef _SS_STACK_H
#include "stack.h"
#endif

#define STATIC_INLINE static inline

struct TREE {
    struct TREE_NODE *r;
};
struct TREE_NODE {
    struct TREE_NODE *l,*r;
    int value;
};
typedef void (*recurfunc_t)(struct TREE_NODE *r);

//global
struct TREE tree;

STATIC_INLINE int node_insert(struct TREE_NODE *t, struct TREE_NODE *n) {
    if (t->value > n->value) {
        if (!t->l)
            t->l = n;
        else
            node_insert(t->l, n);
    } else if (t->value < n->value) {
        if (!t->r)
            t->r = n;
        else
            node_insert(t->r, n);
    }
    return 0;
}

/*
 * This function inserts value to tree where no same
 * value exists.
 */
STATIC_INLINE int tree_insert(struct TREE *t, int value) {
    struct TREE_NODE *n = malloc(sizeof(struct TREE_NODE));
    n->l = n->r = 0;
    n->value = value;
    if (!t->r)
        t->r = n;
    else {
        node_insert(t->r, n);
    }
    return 0;
}

STATIC_INLINE int create_default_tree() {
    tree_insert(&tree, 5);
    tree_insert(&tree, 15);
    tree_insert(&tree, 65);
    tree_insert(&tree, 35);
    tree_insert(&tree, 75);
    tree_insert(&tree, 4);
    tree_insert(&tree, 2);
    tree_insert(&tree, 3);
    tree_insert(&tree, -1);
    return 0;
}

STATIC_INLINE int __preorder_tree(struct TREE_NODE *r, recurfunc_t f) {
    (*f)(r);
    if (r->l)
        __preorder_tree(r->l, f);
    if (r->r)
        __preorder_tree(r->r, f);
    return 0;
}

STATIC_INLINE int preorder_tree(struct TREE *t, recurfunc_t f) {
    if (t->r)
        __preorder_tree(t->r,f);
    return 0;
}

STATIC_INLINE int __inorder_tree(struct TREE_NODE *r, recurfunc_t f) {
    if (r->l)
        __inorder_tree(r->l, f);
    (*f)(r);
    if (r->r)
        __inorder_tree(r->r, f);
    return 0;
}

STATIC_INLINE int inorder_tree(struct TREE *t, recurfunc_t f) {
    if (t->r)
        __inorder_tree(t->r, f);
    return 0;
}

STATIC_INLINE int __postorder_tree(struct TREE_NODE *r, recurfunc_t f) {
    if (r->l)
        __postorder_tree(r->l, f);
    if (r->r)
        __postorder_tree(r->r, f);
    (*f)(r);
    return 0;
}

STATIC_INLINE int postorder_tree(struct TREE *t, recurfunc_t f) {
    if (t->r)
        __postorder_tree(t->r, f);
    return 0;
}

STATIC_INLINE int preorder_nonrecur(struct TREE *t, recurfunc_t f) {
    struct TREE_NODE *n;
    if (!t->r)
        return 0;
    else {
        push_head(&stack, t->r);
    }
    while(!stack_empty(&stack)) {
        n = pop_head(&stack);
        (*f)(n);
        if (n->r)
            push_head(&stack, n->r);
        if (n->l)
            push_head(&stack, n->l);
    }
    return 0;
}

STATIC_INLINE int inorder_nonrecur(struct TREE *t, recurfunc_t f) {
    struct TREE_NODE *n;
    if (!t->r)
        return 0;
    n = t->r;

    while(1) {
        if (n->l) {
            push_head(&stack,n);
            n = n->l;
        }
        else {
right:
            (*f)(n);
            if (n->r)
                n = n->r;
            else {
                n = pop_head(&stack);
                if (n)
                    goto right;
                else
                    break;
            }
        }
    }
    return 0;
}

STATIC_INLINE int postorder_nonrecur(struct TREE *t, recurfunc_t f) {
    struct TREE_NODE *n;
    if (!t->r)
        return 0;
    n = t->r;
    do {
        while (n) {
            if (n->r)
                push_head(&stack, n->r);
            push_head(&stack, n);
            n = n->l;
        }
        n = pop_head(&stack);
        if (n->r && n->r == peek_head(&stack)) {
            pop_head(&stack);
            push_head(&stack, n);
            n = n->r;
        } else {
            (*f)(n);
            n = NULL;
        }
    } while(!stack_empty(&stack));
    
    return 0;
}

STATIC_INLINE int delete_tree(struct TREE *t) {
    postorder_tree(t, (recurfunc_t)free);
    return 0;
}

STATIC_INLINE void printnode(struct TREE_NODE *r) {
    fprintf(stdout, "%d,", r->value);
    return;
}

STATIC_INLINE int print_pre_tree(struct TREE *t) {
    preorder_tree(t, (recurfunc_t)printnode);
    return 0;
}
