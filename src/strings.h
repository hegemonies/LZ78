#ifndef STRINGS_H
#define STRINGS_H


int slen(char *str);

char *stok(char *str, const char *delim);

int sspn(char *str, const char *substr);

int scmp(const char *mstr, const char *cpstr);

char *scpy(char *des, const char *src);

char *scat(char *des, char *src);

char *sstr(char *str1,  const char *str2);

void new_static_char(char *str);

char *save_static_char(void);

#endif
