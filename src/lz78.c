#include "strings.h"
#include "lz78.h"
#include <stdlib.h>

void dic_init(Dictionary *dic, int capacity)
{
	dic->capacity = capacity;
	dic->size = 1;
	dic->dic_i = calloc(dic->capacity, sizeof(Dictionary_item));
	dic->dic_i[0].str = calloc(1, sizeof(char));
	//dic->dic_i[0].count = 0;
}

char *swap_str(char *str)
{
	char *tmp = malloc(sizeof(char) * slen(str));
	scpy(tmp, str);
	for (int i = 0; i < slen(str) / 2; i++) {
		char buf = tmp[i];
		tmp[i] = tmp[slen(str) - 1 - i];
		tmp[slen(str) - 1 - i] = buf;
	}
	return tmp;
}

void fill_dic(Dictionary *dic, Code *code)
{
	for (int i = 1; code[i].str != 0; i++) {
		if (i >= dic->capacity) {
			clear_dic(dic);
			//clear_dic_with_min_usige_elem(dic);
			//remove(dic);
		}
		if (code[i].num == 0) {
			dic->dic_i[i].str = calloc(2, sizeof(char));
			//dic->dic_i[i].count = 0;
			char ai[2];
			ai[0] = code[i].str;
			ai[1] = 0;
			scat(dic->dic_i[i].str, ai);
		}
		if (code[i].num != 0) {
			char *buf_str = calloc(256, sizeof(char));
			char tmp_code[2];
			tmp_code[0] = code[i].str;
			tmp_code[1] = 0;
			int k = code[i].num;
			int count = 0;
			while (k != 0) {
				count++;
				char s[2];
				s[0] = code[k].str;
				s[1] = 0;
				scat(buf_str, s);
				k = code[k].num;
			}
			scat(buf_str, tmp_code);
			if (count >= 2) {
				char *mediator = calloc(slen(buf_str) + 1, sizeof(char));
				scat(mediator, buf_str);
				char t[2];
				t[0] = mediator[slen(buf_str) - 1];
				t[1] = '\0';
				mediator[slen(buf_str) - 1] = '\0';
				buf_str = swap_str(mediator);
				scat(buf_str, t);
				free(mediator);
			}
			dic->dic_i[i].str = calloc(slen(buf_str) + 1, sizeof(char));
			//dic->dic_i[i].count = 0;
			scat(dic->dic_i[i].str, buf_str);
			free(buf_str);
		}
		dic->size++;
	}
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
			//dic.dic_i[i].count++;
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
	code[dic.size].str = dic.dic_i[dic.size].str[slen(dic.dic_i[dic.size].str) - 1];
	char *first_substr = calloc(slen(dic.dic_i[dic.size].str) + 1, sizeof(char));
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
			if (dic->size == dic->capacity) {
				clear_dic(dic);
				//clear_dic_with_min_usige_elem(dic);
				//remove(dic);
			}
			dic->dic_i[dic->size].str = calloc(slen(tmp_dic) + 1, sizeof(char));
			//dic->dic_i[dic->size].count = 0;
			scat(dic->dic_i[dic->size].str, tmp_dic);

			add_code(code, *dic);

			dic->size++;
			*tmp_dic = '\0';
		}
	}
	free(tmp_dic);
}

void clear_dic(Dictionary *dic)
{
	for (int i = 1; i < dic->capacity; i++) {
		free(dic->dic_i[i].str);
		dic->dic_i[i].str = NULL;
	}
	dic->size = 1;
}

/*
typedef struct {
	int i;
	int count;
	char *str;
} Array;

void clear_dic_with_min_usige_elem(Dictionary *dic)
{
	Array array[dic->capacity];
	for (int i = 0; i < dic->capacity; i++) {
		array[i].i = i;
		array[i].count = dic->dic_i[i].count;
		array[i].str = calloc(slen(dic->dic_i[i].str), sizeof(char));
		scat(array[i].str, dic->dic_i[i].str);
	}
	for (int i = 0; i < dic->capacity; i++) {
		for (int j = 0; j < dic->capacity; j++) {
			if (array[i].count < array[j].count) {
				Array tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	int sum = 0;
	for (int i = 0 ; i < dic->capacity; i++) {
		sum += array[i].count;
	}
	int avarage = sum / dic->capacity;
	for (int i = 0; i < avarage; i++) {
		array[i].count = 0;
		free(array[i].str);
		array[i].str = NULL;
	}
	for (int i = 0; i < dic->capacity; i++) {
		for (int j = 0; j < dic->capacity; j++) {
			if (array[i].i < array[j].i) {
				Array tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	
	for (int i = 0; i < dic->capacity; i++) {
		//array_copy[i].i = array[i].i;
		dic->dic_i[i].count = array[i].count;
		//array_copy[i].count = array[i].count;
		if (array[i].str != NULL) {
			//array_copy[i].str = calloc(strlen(array[i].str), sizeof(char));
			//strcat(array_copy[i].str, array[i].str);
			dic->dic_i[i].str[0] = '\0';
			scat(dic->dic_i[i].str, array[i].str);
			continue;
		}
		//array_copy[i].str = NULL;
		dic->dic_i[i].str = NULL;
	}

	printf("\nResult !!!:\ni :: count :: str\n");
	for (int i = 0; i < dic->capacity; i++) {
		if (dic->dic_i[i].str != NULL) {
			printf("%d :: %d :: %s\n", i, dic->dic_i[i].count, dic->dic_i[i].str);
			continue;
		}
		printf("%d :: %d :: NULL\n", i, dic->dic_i[i].count);
	}
}
*/