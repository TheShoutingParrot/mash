#include "mash.h"

/* Checks if every character of the string, that is being hashed, has been processed */
bool isAllReady(bool *ptr, uint64_t l) {
	uint8_t i;

	for(i = 0; i < l; i++) {
		if(!(*(ptr + i)))
			return false;
	}

	return true;
}

char *readInput(void) {
	char *str, ch;
	uint64_t i, j;

	i = 4096;
	j = 0;

	str = (char *)calloc(i, sizeof(char));
	if(str == NULL) {
		die("failed to allocate memory!");
	}

	for(;;) {
		ch = fgetc(stdin);
		*(str + j) = ch;

		j++;

		if(ch == EOF) {
			return str;
		}

		else if(i-1 <= j) {
			i += 4096;
			str = (char *)realloc(str, i);

			if(str == NULL) {
				die("failed to rellocate memory!");
			}
		}
	}

	return NULL;
}

void die(const char *fmt, ...) {
	va_list vargs;

	va_start(vargs, fmt);

	fprintf(stderr, "FATAL: ");
	vfprintf(stderr, fmt, vargs);
	fputc('\n', stderr);

	va_end(vargs);
	
	exit(EXIT_FAILURE);
}

