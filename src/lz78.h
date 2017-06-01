#ifndef LZ78_H
#define LZ78_H
#include <stdio.h>

typedef struct {
	int num;
	char str;
} Code;

typedef struct {
	char *str;
	//int count;
} Dictionary_item;

typedef struct {
	Dictionary_item *dic_i;
	int size;
	int capacity;
} Dictionary;

void dic_init(Dictionary *dic, int capacity);

char *swap_str(char *str);

void fill_dic(Dictionary *dic, Code *code);

Code *code_init(int size);

int find_i(Dictionary dic, char *tmp);

void free_all(char *tmp_dic, Dictionary dic);

void add_code(Code *code, Dictionary dic);

void compres(Dictionary *dic, Code *code, FILE *in);

void clear_dic(Dictionary *dic);

//void clear_dic_with_min_usige_elem(Dictionary *dic);

#endif