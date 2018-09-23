#include <stdio.h>
//strlen
#include <string.h>
//malloc
#include <stdlib.h>

#define _IN_
#define _OUT_

int getnext(_IN_ char *p, _OUT_ int **next) {
    int len = strlen(p);
    int i = 0, k = -1;
        
    *next = malloc(sizeof(int)*(len));

    (*next)[0] = -1;
    while (i < len-1) {
        if (k==-1||p[i]==p[k]) {
            (*next)[++i] = ++k;
        } else {
            k = (*next)[k];
        }
    }

    return 0;
}

// suggest using while other than for.
int kmp(_IN_ char *st, _IN_ char *sp, _OUT_ int *start, _OUT_ int *end) {
    int m = strlen(st), n = strlen(sp);
    int i,j;
    int *next = NULL;
    int longest = 0;
    getnext(sp, &next);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; ) {
            if (st[i]!=sp[j]) {
                j = next[j];
                if (j == -1)
                    break;
            } else {
                if (longest < (j+1)) {
                    longest = j+1;
                    *start = i - j;
                    *end = i;
                }
                i++;
                j++;
            }
        }
//        if (j==n)
//            break;
    }
    return longest;
}

int main() {
    int start,end,longest;
    longest = kmp("abcabcde", "bce",&start, &end);
    fprintf(stdout, "L:%d,S:%d,E:%d\n", longest, start, end);
}
