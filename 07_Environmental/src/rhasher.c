#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "rhash.h"

//#include "config.h"

#ifdef READLINE
#include <readline/readline.h>
#endif


int main(int argc, char *argv[]) {
    char *alg, *target, *line;
    unsigned char digest[64];
    char hash[128];
    size_t len;
    int alg_use, print_use, success;

    printf(">>> ");

#ifdef READLINE
    while ((line = readline("")) != NULL) {
#else
    while (getline(&line, &len, stdin) != -1) {
#endif

        alg = strtok(line, " ");
        target = strtok(NULL, " ");

        if (alg == NULL || target == NULL) {
            printf("2 words in input needed!\n");
            printf(">>> ");
            continue;
        }

        if (strcasecmp(alg, "md5") == 0)
            alg_use = RHASH_MD5;
        else if (strcasecmp(alg, "sha1") == 0)
            alg_use = RHASH_MD5;
        else if (strcasecmp(alg, "tth") == 0)
            alg_use = RHASH_MD5;
        else {
            printf("Algorythm not recognized!\n");
            printf(">>> ");
            continue;
        }

        if (islower(alg[0]))
            print_use = RHPR_BASE64;
        else
            print_use = RHPR_HEX;

        if (target[0] == '\"')
            success = rhash_msg(alg_use, target + 1, strlen(target) - 1, digest);
        else
            success = rhash_file(alg_use, target, digest);

        if (success < 0) {
            fprintf(stderr, "Hashing error: %s\n", strerror(errno));
            printf(">>> ");
            continue;
        }

        rhash_print_bytes(hash, digest, rhash_get_digest_size(alg_use), print_use);

        printf("%s\n", hash);
    }

    free(line);

    return 0;
}
