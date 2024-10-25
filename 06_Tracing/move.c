#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Two args needed!\n");
		exit(1);
	}

	FILE *in_file, *out_file;
	char c;


	if (access(argv[1], F_OK) != 0) {
		fprintf(stderr, "No file %s existed: %s\n", argv[1], strerror(errno));
		exit(errno);
	}
	if (access(argv[1], R_OK) != 0) {
		fprintf(stderr, "File %s has no read permittion: %s", argv[1], strerror(errno));
		exit(errno);
	}

	if (access(argv[2], F_OK) != 0) {
		fprintf(stderr, "No file %s existed: %s\n", argv[2], strerror(errno));
		exit(errno);
	}
	if (access(argv[2], W_OK) != 0) {
		fprintf(stderr, "File %s has no wright permittion: %s", argv[2], strerror(errno));
		exit(errno);
	}

	if (truncate(argv[2], 0) != 0) {
		fprintf(stderr, "Error while truncating %s file: %s", argv[2], strerror(errno));
		exit(errno);
	}

	in_file = fopen(argv[1], "r");
	if (in_file == NULL) {
		fprintf(stderr, "Error while openning %s file: %s\n", argv[1], strerror(errno));
		exit(errno);
	}

	out_file = fopen(argv[2], "w");
	if (out_file == NULL) {
		fprintf(stderr, "Error while openning %s file: %s\n", argv[2], strerror(errno));
		exit(errno);
	}

	while ((c = fgetc(in_file)) != EOF) {
		if (fputc(c, out_file) == EOF) {
			fprintf(stderr, "Can't write symbol to %s file: %s\n", argv[2], strerror(errno));
			fclose(in_file);
			fclose(out_file);
			if (remove(argv[2]) != 0) {
				fprintf(stderr, "Error while removing %s file: %s\n", argv[2], strerror(errno));
				exit(errno);
			}
			exit(errno);
		}
	}

	if (fclose(in_file) != 0) {
		fprintf(stderr, "Error while closing %s file: %s\n", argv[1], strerror(errno));
		exit(errno);
	}
	if (fclose(out_file) != 0) {
		fprintf(stderr, "Error while closing %s file: %s\n", argv[2], strerror(errno));
		exit(errno);
	}


	if (remove(argv[1]) != 0) {
		fprintf(stderr, "Error while removing %s file: %s\n", argv[1], strerror(errno));
		if (remove(argv[2]) != 0) {
			fprintf(stderr, "Error while removing %s file: %s\n", argv[2], strerror(errno));
			exit(errno);
		}
		exit(errno);
	}

	return 0;
}
