#ifndef LZ78_H
#define LZ78_H
#include <stdio.h>

typedef struct {
	int num;
	char str;
} Code;

typedef struct {
	char *str;
	//int count = 0;
} Dictionary_item;

typedef struct {
	Dictionary_item *dic_i;
	int size;
	int capacity;
} Dictionary;

void dic_init(Dictionary *dic);

void fill_dic(Dictionary *dic, char *name_file);

Code *code_init(int size);

int find_i(Dictionary dic, char *tmp);

void free_all(char *tmp_dic, Dictionary dic);

void add_code(Code *code, Dictionary dic);

void compres(Dictionary *dic, Code *code, FILE *in);

#endif