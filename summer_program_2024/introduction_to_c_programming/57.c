#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 2000
#define L_ACC 51
#define L_PWD 2001

struct wifi {
	char account[L_ACC];
	char password[L_PWD];
	int ss;
};

int findWifi(struct wifi *, int const, char *);

int main() {
	int n;
	scanf("%d", &n);

	struct wifi *wifiArr = malloc(sizeof(struct wifi) * n);
	
	int i;
	for (i = 0; i < n; i++) {
		scanf("%s %s %d", wifiArr[i].account, wifiArr[i].password, &wifiArr[i].ss);
	}
	
	int q;
	scanf("%d", &q);
	
	char acc[L_ACC];
	int index;
	for (i = 0; i < q; i++) {
		scanf("%s", acc);
		index = findWifi(wifiArr, n, acc);
		if (index == -1) {
			puts("not found");
		}
		else {
			printf("%s ", wifiArr[index].password);
			printf("%d\n", wifiArr[index].ss);
		}
	}
	
	free(wifiArr);
	
	return 0;
}

int findWifi(struct wifi *list, int const LIST_N, char *acc) {
	int i;
	for (i = 0; i < LIST_N; i++) {
		if (strcmp(acc, list[i].account) == 0) {
			return i;
		}
	}
	return -1;
}
