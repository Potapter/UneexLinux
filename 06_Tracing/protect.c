#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>


typedef int (*remove_type)(void);

int remove(char *file) {
	if (strstr(file, "PROTECT") == NULL)
		return ((remove_type) dlsym(RTLD_NEXT, "PROTECT"))();
	else
		return 0;
}
