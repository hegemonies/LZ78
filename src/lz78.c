#include "strings.h"
#include "lz78.h"
#include <stdlib.h>

void dic_init(Dictionary *dic)
{
	dic->capacity = 65536;
	dic->size = 1;
	dic->dic_i = calloc(dic->capacity, sizeof(Dictionary_item));
	dic->dic_i[0].str = calloc(1, sizeof(char));
}

void fill_dic(Dictionary *dic, char *name_file)
{
	FILE *in = fopen(name_file, "r");

	char tmp[2];
	char *tmp_dic = calloc(256, sizeof(char));
	while (fread(&tmp, 1, 1, in)) {
		tmp[1] = 0;
		scat(tmp_dic, tmp);
		int tmp_i = find_i(*dic, tmp_dic);
		if (tmp_i == 1) {
			break;
		} else if (!tmp_i) {
			continue;
		} else {
			dic->dic_i[dic->size].str = calloc(slen(tmp_dic), sizeof(char));
			scat(dic->dic_i[dic->size].str, tmp_dic);
			dic->size++;
			*tmp_dic = '\0';
		}
	}
	free(tmp_dic);

	fclose(in);
}

Code *code_init(int size)
{
	Code *code = calloc(size, sizeof(Code));
	code[0].num = 0;
	code[0].str = '\0';
	return code;
}

int find_i(Dictionary dic, char *tmp)
{
	if (!scmp("\n", tmp)) {
		return 1;
	}
	for (int i = 0; i < dic.size; i++) {
		int len = sspn(dic.dic_i[i].str, tmp);
		if (len == slen(tmp)) {
			return 0;
		}
	}
	return -1;
}

void free_all(char *tmp_dic, Dictionary dic)
{
	for (int i = 1; i < dic.capacity; i++) {
		free(dic.dic_i[i].str);
	}
	free(dic.dic_i);
	free(tmp_dic);
}

void add_code(Code *code, Dictionary dic)
{
	if (slen(dic.dic_i[dic.size].str) == 1) {
		code[dic.size].num = 0;
		code[dic.size].str = dic.dic_i[dic.size].str[0];
		return;
	}

	char second_substr = dic.dic_i[dic.size].str[slen(dic.dic_i[dic.size].str) - 1];
	code[dic.size].str = second_substr;
	
	char *first_substr = calloc(slen(dic.dic_i[dic.size].str), sizeof(char));
	scat(first_substr, dic.dic_i[dic.size].str);
	first_substr[slen(dic.dic_i[dic.size].str) - 1] = '\0';

	for (int i = 0; i < dic.size; i++) {
		int len = sspn(dic.dic_i[i].str, first_substr);
		if (len == slen(first_substr)) {
			code[dic.size].num = i;
			break;
		}
	}
	free(first_substr);
}

void compres(Dictionary *dic, Code *code, FILE *in)
{
	char tmp[2];
	char *tmp_dic = calloc(256, sizeof(char));
	while (fread(&tmp, 1, 1, in)) {
		tmp[1] = 0;
		scat(tmp_dic, tmp);
		int tmp_i = find_i(*dic, tmp_dic);
		if (tmp_i == 1) {
			break;
		} else if (!tmp_i) {
			continue;
		} else {
			dic->dic_i[dic->size].str = calloc(slen(tmp_dic), sizeof(char));
			scat(dic->dic_i[dic->size].str, tmp_dic);

			add_code(code, *dic);

			dic->size++;
			*tmp_dic = '\0';
		}
	}
	free(tmp_dic);
}

void clear_dic(Dictionary dic)
{
	for (int i = 1; i < dic.size; i++) {
		dic.dic_i[i].str = 0;
	}
	dic.size = 1;
}