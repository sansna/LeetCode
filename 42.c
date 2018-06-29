#include <stdio.h>
int trap(int* height, int heightSize) {
	int top = 0;
	int i = 0, j = 0;
	int left = -1, right = 0;
	int ret = 0;
	int curlm = 0, currm = 0;
	for (; i < heightSize; i++) {
		if (top < height[i]) {
			top = height[i];
			currm = i;

		}


	}
	for (i = 0; i < heightSize; i++) {
		if (height[i] > 0) {
			left = i;
			break;

		}

	}
	for (i = heightSize - 1; i >= 0; i--) {
		if (height[i] > 0) {
			right = i;
			break;

		}

	}
	for (i = left + 1;i < right; i++) {
		curlm = height[i - 1] > height[curlm]?i-1:curlm;
		if (i > currm) {
			currm = 0;
			for (j = i + 1;j <= right; j++) {
				currm = (height[j] > height[currm]||currm==0)?j:currm;

			}

		}
		for (j = top - 1; j >= 0; j--) {
			if (height[i] > j)
				continue;
			if (height[currm] > j && height[curlm] > j) {
				ret+=(j - height[i] + 1);
				break;

			}

		}

	}
	return ret;

}
int main()
{
	int a[12] = {0,1,0,2,1,0,1,3,2,1,2,1};
	fprintf(stdout,"%d\n",trap(a,12));
	return 0;
}
