#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include <stdint.h>
#include <string.h>

int slen(char *str)
{
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		count++;
	}
	return count++;
}

static char *lt;

char *stok(char *str, const char *delim)
{
	if (str != NULL) {
		lt = str;
	}
	for (int i = 0; lt[i] != 0; i++) {
		for (int j = 0; delim[j] != 0; j++) {
			if (lt[i] == delim[j]) {
				lt[i] = 0;
				str = lt;
				lt = lt + i + 1;
				return str;
			}
		}
	}
	return str;
}

void new_static_char(char *str) {
	lt = str;
}

char *save_static_char(void) {
	return lt;
}

int sspn(char *str, const char *substr)
{
	int count = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] == substr[i]) {
			count++;
		} else {
			return count;
		}
	}
	return count;
}

int scmp(const char *str, const char *strc)
{
	int ncount = 0, pcount = 0;
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] < strc[i]) {
			ncount++;
		} else if (str[i] > strc[i]) {
			pcount++;
		}
	}
	if (ncount < pcount) {
		return pcount;
	} else if (ncount > pcount) {
		return -ncount;
	}
	return 0;
}

char *scpy(char *des, const char *src)
{
	int i;
	for (i = 0; src[i] != 0; i++) {
		des[i] = src[i];
	}
	des[i] = 0;
	return des;
}

char *scat(char *des, char *src)
{
	int j = slen(des);
	for (int i = 0; src[i]; i++) {
		des[j] = src[i];
		j++;
	}
	des[j] = 0;
	return des;
}

char *sstr(char *string1, const char *string2)
{
	char *strptr = string1;
	int j = 0;
	for (int i = 0; string1[i] != 0; i++) {
		if (string2[j] == 0) {
			return strptr;
		}
		if (string1[i] != string2[j]) {
			j = 0;
			continue;
		}
		if (string1[i] == string2[j]) {
			if (j == 0) {
				strptr = string1 + i;
			}
			j++;
		}
	}
	if (string2[j] == 0) {
		return strptr;
	} else {
		return NULL;
	}
}
