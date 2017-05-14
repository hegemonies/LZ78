#ifndef LZ78_H
#define LZ78_H

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

void code_init(Code *code);

int find_i(const Dictionary *dic, char *tmp);

void free_all(char *tmp_dic, Dictionary dic);

void find_code(Code *code, const Dictionary *dic);

void compres(Dictionary *dic, Code *code, char *file_name);

#endif