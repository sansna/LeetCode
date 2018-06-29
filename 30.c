#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SMALLOC(x)    \
({                             \
 void *addr;  \
 if ((x) == 0)              \
 addr = 0;                         \
 else addr = malloc(x);           \
 (addr);\
 })

int *findAll(char *s, char *word, int *returnSize) {
	int len = strlen(s);
	int lenw = strlen(word);
	int *ret = SMALLOC(sizeof(int)*(len-lenw));
	int i = 0, j = 0;
	int cur = 0;

	for (; i < len - lenw + 1; i++) {
		if (!strncmp(i+s, word, lenw))
			ret[cur++] = i;


	}
	*returnSize = cur;
	return ret;


}

int maxWords = 0;
int *psize;
int *len;
int l = 0;

int recurFindNext(int **b, int *cur, int loc, int *excl, int *count) {
	int i = 0;
	int j = 0;
	int ret = 0;
	if (loc >= l)
		return 1;
	for (; ; i++) {
OUT:
		if (i >= cur[loc])
			break;
		for (j = 0; j < *count; j++) {
			if (excl[j] == b[loc][i]) {
				i++;
				goto OUT;


			}


		}
		//b[loc][i] is word not included yet.
		excl[(*count)++] = b[loc][i];
		if (*count == maxWords)
			return 0;
		ret = recurFindNext(b,cur,loc+len[b[loc][i]],excl,count);
		if (ret)
			(*count)--;


	}
	if (*count == maxWords)
		return 0;

	return 1;


}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
	int **a = SMALLOC(sizeof(int*)*wordsSize);
	int **b;
	int *cur;
	int i = 0, j = 0;
	int *excl = SMALLOC(sizeof(int)*wordsSize);
	int *count = SMALLOC(sizeof(int));
	int flag = 0;
	int *ret;

	*returnSize = 0;
	l = strlen(s);
	b = SMALLOC(sizeof(int*)*l);
	cur = SMALLOC(sizeof(int)*l);
	maxWords = wordsSize;
	len = SMALLOC(sizeof(int)*wordsSize);
	psize = SMALLOC(sizeof(int)*wordsSize);
	ret = SMALLOC(sizeof(int)*l);
	memset(b,0,sizeof(int*)*l);
	memset(cur,0,sizeof(int)*wordsSize);
	for (; i < wordsSize; i++) {
		len[i] = strlen(words[i]);
		a[i] = findAll(s,words[i],&psize[i]);
		for (j = 0; j < psize[i]; j++) {
			if (!b[a[i][j]])
				b[a[i][j]] = SMALLOC(sizeof(int)*wordsSize);
			b[a[i][j]][cur[a[i][j]]++] = i;//s location a[i][j] contains word i.


		}


	}

	for (i = 0; i < l; i++) {
		if (!cur[i])
			continue;
		*count = 0;
		flag = recurFindNext(b,cur,i,excl,count);
		if (!flag)
			ret[(*returnSize)++] = i;


	}
	free(count);
	free(excl);
	free(psize);
	for (i = 0;i < l; i++) {
		free(b[i]);


	}
	for (i = 0;i < wordsSize; i++) {
		free(a[i]);


	}
	free(b);
	free(a);
	free(len);
	free(cur);
	return ret;


}
int main()
{
	char **c = SMALLOC(sizeof(char*)*2);
	int *ret = NULL;
	int *returnSize = SMALLOC(sizeof(int));
	int i = 0;
	c[0] = "foo";
	c[1] = "bar";
	ret = findSubstring("foobarfoobarfoo",c,2,returnSize);
	for (;i < *returnSize; i++) {
		fprintf(stdout,"%d\n",ret[i]);
	}
	free(ret);
	free(returnSize);
	free(c);

	return 0;
}
