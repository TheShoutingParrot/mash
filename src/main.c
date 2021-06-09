/* My own hASH: MASH 
 * main.c */

#include "mash.h"

/* These are the chars that are used in the hash string */
char hashChars[CHARS] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'-', '_',
};

int main(int argc, char *argv[]) {
	char *hash, *str;

	if(argc < 2)
		die("Not enough arguments! Must contain a string to hash or just a line (\"-\") to read stdin.");

	if(argc > 2)
		die("Too many arguments! If you have spaces in your string you may have to put the string in quotations.");

	hash = (char *)calloc(LEN_OF_HASH, sizeof(char));

	if(!strcmp(argv[1], "-")) {
		str = readInput();

		hashStr(str, hash, strlen(str));
	}

	else{
		hashStr(argv[1], hash, strlen(argv[1]));
	}

	printf("%s\n", hash);

	return EXIT_SUCCESS;
}
	
void hashStr(char *str, char *hashStr, uint64_t length) {
	uint64_t hash[LEN_OF_HASH], strIndex, prevItem, i, I;
	uint16_t magic;
	bool *strB;

	strB = (bool *)calloc(length, sizeof(bool));

	prevItem = length;
	magic = 1; 

	for(i = 0; i < LEN_OF_HASH; i++) {
		hash[i] = 0;
	}

	for(i = 0; i < length; i++) {
		*(strB + i) = false;
	}

	strIndex = length - 1;

	for(;;) {
		/* Goes throught the input string 5 times and then deletes the chars that have been "handled" */
		for(I = 0; I < 5; I++) {
			for(i = 0; i < LEN_OF_HASH; i++) {
				/* First, selects which character will it be hashing in */
				strIndex = ((strIndex * magic) % length);

				if(prevItem == strIndex) {
					if(strIndex == 0)
						strIndex = length-1;
					strIndex--;
				}

				prevItem = strIndex;

				/* If it has already been "hashed in" then it does a slightly different calculation */
				if(*(strB + strIndex)) {
					hash[i] = ((hash[i] >> (magic % 3)) + (str[strIndex] * magic)) % CHARS;
					
					/* Sets the magic number */
					magic = (length * hash[i] * magic * 3 + str[strIndex]) % 0xFFFF;
				}
			

				else {
					hash[i] = ((((str[strIndex] + strIndex + (length >> 2)) * magic) + str[(strIndex + 1) % length]) + 1) % CHARS;
					magic = (magic * length + hash[i] * (strIndex + 3) + length) % 0xFFFF;

					if(magic == 0) {
						magic = 512;
					}

					*(strB + strIndex) = true;
				}

				if(magic == 0) {
					magic = hash[i]+1;
				}
			} 

			/* Checks if all characters of the input string have been taken into account */
			if(isAllReady(strB, length)) {
				/* If so then the hash algorithm can end */
				goto END_OF_LOOP;
			}

			magic = (magic + 3 * length) % 0xFFFF;
		}
		
		length = removeUsedChars(&str, strB, length);
		strB = (bool *)calloc(length, sizeof(bool));

		magic = (7 * length * magic) % 0xFFFF;
	}

END_OF_LOOP:
	convertHashNumToChar((uint64_t *)&hash, hashStr);
}

/* Converts a number to one of the hash characters */
void convertHashNumToChar(uint64_t *hash, char *str) {
	uint8_t i;

	for(i = 0; i < LEN_OF_HASH; i++) {
		*(str + i) = hashChars[*(hash + i) % CHARS];
	}
}

/* Removes the characters that have been "used" (= the algorithm has gone throught it) */
uint64_t removeUsedChars(char **str, bool *used, uint64_t length) {
	uint64_t i, j;
	char *newStr;

	j = 0;

	newStr = (char *)calloc(length, sizeof(char));
	if(newStr == NULL) {
		die("failed to allocate memory!");
	}

	for(i = 0; i < length; i++) {
		if((!*(used + i))) {
			*(newStr + j++) = *(*str + i);
		}
	}

	newStr = (char *)realloc(newStr, j);
	if(newStr == NULL) {
		die("failed to rellocate memory!");
	}

	*str = newStr;

	return j;
}

