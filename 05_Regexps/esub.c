
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGR 10
#define MAXLINKS 100

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Three parameters are needed!\n");
		exit(1);
	}

	regex_t regex;
	regmatch_t bags[MAXGR];
	size_t error_buffer_size = MAXGR * MAXLINKS;
	char error_buffer[MAXGR * MAXLINKS];
	int status = 0, bags_n = 0, bags_b, bags_e;

	status = regcomp(&regex, argv[1], REG_EXTENDED);
	if (status != 0) {
		regerror(status, &regex, error_buffer, error_buffer_size);
		printf("Error in regcomp, status %s\n", error_buffer);
		exit(1);
	}

	status = regexec(&regex, argv[3], MAXGR, bags, 0);
	if (status != 0) {
		regerror(status, &regex, error_buffer, error_buffer_size);
		printf("Error in regexec, status %s\n", error_buffer);
		exit(1);
	}

	for (int i = 1; i < MAXGR && bags[i].rm_so >= 0; i++, bags_n++) {}

	for (int i = 0; i < strlen(argv[2]); ++i) {
		if (argv[2][i] == '\\' && (i + 1) < strlen(argv[2]) && '0' < argv[2][i + 1] && argv[2][i + 1] <= '9' && argv[2][i + 1] - '0' > bags_n) {
			printf("Error, invalid bag number!\n");
			return 0;
		}
	}

	bags_b = bags[1].rm_so;
	bags_e = bags[bags_n].rm_eo;

	printf("%.*s", bags_b, argv[3]);

	for (int i = 0; i < strlen(argv[2]); ++i) {
		if (argv[2][i] != '\\' || i + 1 > strlen(argv[2]))
			printf("%c", argv[2][i]);
		else {
			if (argv[2][i + 1] == '\\') {
				printf("\\");
			} else if ('0' < argv[2][i + 1] && argv[2][i + 1] <= '9') {
				int n = argv[2][i + 1] - '0';
				printf("%.*s", bags[n].rm_eo - bags[n].rm_so, &argv[3][bags[n].rm_so]);
			} else {
				printf("%c", argv[2][i + 1]);
			}
			i++;
		}
	}

	printf("%.*s\n", (int) strlen(argv[3]) - bags_e, argv[3] + bags_e);

	regfree(&regex);
	return 0;
}
