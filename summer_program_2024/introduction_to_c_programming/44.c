#include <stdio.h>
#define N 1000

int main(void) {
	int arr[N];
	
	int n;
	scanf("%d", &n);
	
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	
	int left = 0, right = n - 1;
	while (left < right) {
		int temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left = left + 1;
		right = right - 1;
	}
	
	for (i = 0; i < n; i++) {
		printf("%d", arr[i]);
		if (i < n - 1) {
			printf(" ");
		}
	}
}
