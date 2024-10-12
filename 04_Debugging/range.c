#include <stdio.h>

void range(int m, int n, int s) {
	for (int i = m; i < n; i += s) {
		printf("%d\n", i);
	}
}

int main(int argc, char **argv) {
	switch(argc) {
		case 1:
			printf("Usage: same as range() in Python3\n");
			break;
		case 2:
			range(0, atoi(argv[1]), 1);
			break;
		case 3:
			range(atoi(argv[1]), atoi(argv[2]), 1);
			break;
		case 4:
			range(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
			break;
		default:
			printf("Error: invalid number of arguments\n");
			exit(0);
	}

	return 0;
}
