#ifndef STRINGS_H
#define STRINGS_H


int slen(char *str);

int sspn(char *str, const char *substr);

int scmp(char *mstr, const char *cpstr);

char *scat(char *des, char *src);

char *sncat(char *des, char *src, int size);

char *scpy(char *des, const char *src);

#endif
