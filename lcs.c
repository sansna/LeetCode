#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M(x,y) (tab[(((x)*m)+(y))])

int lcsOn2(char *s1, char *s2) {
    int m = strlen(s1), n = strlen(s2);
    int *tab = malloc(sizeof(int) * m * n);
    int i,j, longest = 0;
    if (m==0||n==0)
        return 0;
    for (i = 0; i < m; i++) {
        M(i,0) = (s1[i]==s2[0]?1:0);
        if (!longest&&M(i,0))
            longest=1;
    }
    for (i = 0; i < n; i++) {
        M(0,i) = (s1[0]==s2[i]?1:0);
        if (!longest&&M(0,i))
            longest=1;
    }
    for (i = 1; i < m; i ++) {
        for (j = 1; j < n; j++) {
            if (s1[i]==s2[j]) {
                M(i,j) = M(i-1,j-1)+1;
                if (longest < M(i,j))
                    longest = M(i,j);
            }
        }
    }
    free(tab);
    return longest;
}

#define M2(x,y) (tab[((x)%2)*m+(y)])
int lcs(char *s1, char *s2) {
    int m = strlen(s1), n = strlen(s2);
    int *tab = malloc(sizeof(int)*m*2);
    int i,j,longest = 0;

    for (i = 0; i < n; i ++) {
        M2(0,i) = s1[0]==s2[i]?1:0;
        if (!longest && M2(0,i))
            longest = 1;
    }
    for (i = 1; i < m; i++) {
        M2(i,0) = s1[i]==s2[0]?1:0;
        if (!longest && M2(i,0))
            longest = 1;
        for (j = 1; j < n; j++) {
            if (s1[i]==s2[j]) {
                M2(i,j) = M2(i-1,j-1) + 1;
                if (longest < M2(i,j))
                    longest = M2(i,j);
            }
        }
    }
    free(tab);
    return longest;
}

int main() {
    char s1[] = "1AB2345CD";
    char s2[] = "12345EF";
    fprintf(stdout,"%d\n",lcs(s1,s2));
    fprintf(stdout,"%d\n",lcsOn2(s1,s2));
    return 0;
}
