#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkList {
	int value;
	struct LinkList *next, *prev;//Sort

};
struct LinkList *head, *head0 = NULL;
int ws;
int cur = 0;

int init() {
	head = malloc(sizeof(struct LinkList)*ws);
	memset(head, 0, sizeof(struct LinkList)*ws);
	return 0;

}

int fini() {
	free(head);
	return 0;

}

int insert(int value) {
	struct LinkList *p, *n, *t;
	p = head[cur].prev;
	n = head[cur].next;
	head[cur].value = value;
	head[cur].prev = head[cur].next = NULL;

	if(ws==1)
		head0 = NULL;

	if (!p) {
		if (!n) {
			;

		} else {
			head0 = n;

		}

	} else {
		if (!n) {
			p->next = NULL;

		} else {
			p->next = n;
			n->prev = p;

		}

	}
	t = head0;
	while(1) {
		if (t && value < t->value && t->next) {
			t = t->next;
			continue;

		}
		if (!head0) {
			head0 = &head[cur];
			break;

		}
		if (value < t->value) {
			if (head0 == t) {
				head[cur].next = t->next;
				head[cur].prev = t;
				t->next = &head[cur];

			} else if (!t->next) {
				t->next = &head[cur];
				head[cur].prev = t;

			}

		} else {
			if (head0 == t) {
				head0 = &head[cur];
				head[cur].next = t;
				t->prev = head0;

			} else if (!t->next) {
				t->next = &head[cur];
				head[cur].prev = t;

			} else {
				head[cur].next = t;
				head[cur].prev = t->prev;
				t->prev->next = &head[cur];
				t->prev = &head[cur];

			}


		}
		break;

	}
	cur++;
	cur %= ws;
	return 0;

}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
	int i = 0;
	int *ret = NULL;
	int count = 0;

	ws = k;
	*returnSize = numsSize - k + 1;
	ret = malloc(sizeof(int)*(numsSize-k+1));

	init();
	for (; i < k; i++) {
		insert(nums[i]);

	}
	ret[count++] = head0->value;
	for (; i < numsSize; i++) {
		insert(nums[i]);
		ret[count++] = head0->value;

	}
	fini();
	return ret;

}

int main() {
	int r = 0;
	int a[3] = {7,2,4};
	int *ret = NULL;
	ret = maxSlidingWindow(a, 3, 2, &r);
	for (; r > 0; r--) {
		fprintf(stdout, "%d,", ret[2-r]);
	}
	fprintf(stdout, "\b \n");
	free(ret);
	return 0;
}
