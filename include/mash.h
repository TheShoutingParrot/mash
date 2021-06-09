#ifndef _MASH_H
#define _MASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#define CHARS		64
#define LEN_OF_HASH	64

extern char hashChars[CHARS];

void hashStr(char *str, char *hashStr, uint64_t length);
bool isAllReady(bool *ptr, uint64_t l);
void convertHashNumToChar(uint64_t *hash, char *str);
uint64_t removeUsedChars(char **str, bool *used, uint64_t length);
char *readInput(void);
void die(const char *fmt, ...);

#endif /* #ifndef _MASH_H */
