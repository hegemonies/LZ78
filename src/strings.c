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
	return count;
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

int scmp(char *str, const char *strc)
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

char *scpy(char *des, const char *src)
{
	int i;
	for (i = 0; src[i] != 0; i++) {
		des[i] = src[i];
	}
	des[i] = 0;
	return des;
}