#include "strings.h"
#include "lz78.h"
#include <stdlib.h>

void dic_init(Dictionary *dic)
{
	dic->capacity = 65536;
	dic->size = 1;
	//dic.dic_i = malloc(sizeof(Dictionary_item) * dic.capacity);
	dic->dic_i = calloc(dic->capacity, sizeof(Dictionary_item));
	//dic.dic_i[0].str = malloc(sizeof(char));
	dic->dic_i[0].str = calloc(1, sizeof(char));
}

void code_init(Code *code)
{
	//Code *code = malloc(sizeof(Code) * dic.capacity);
	//code = calloc(size, sizeof(Code));
	//code[0] = malloc(sizeof(Code));
	code[0].num = 0;
	code[0].str = '\0';
}

int find_i(const Dictionary dic, char *tmp)
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

void find_code(Code *code, const Dictionary dic)
{
	if (slen(dic.dic_i[dic.size].str) == 1) {
		code[dic.size].num = 0;
		code[dic.size].str = dic.dic_i[dic.size].str[0];
		//strcat(code[dic.size].str, dic.dic_i[dic.size]);
		return;
	}
//printf("dic.dic_i[dic.size].str%d\n", dic.dic_i[dic.size].str[slen(dic.dic_i[dic.size].str)]);

	char second_substr = dic.dic_i[dic.size].str[slen(dic.dic_i[dic.size].str) - 1];
	code[dic.size].str = second_substr;
	//strcat(code[dic.size].str, second_substr);

	//char *first_substr = malloc(sizeof(char) * slen(dic.dic_i[dic.size].str));
	char *first_substr = calloc(slen(dic.dic_i[dic.size].str), sizeof(char));
	scat(first_substr, dic.dic_i[dic.size].str);
	first_substr[slen(dic.dic_i[dic.size].str) - 1] = '\0';
//printf("%s\n", first_substr);

	for (int i = 0; i < dic.size; i++) {
		int len = sspn(dic.dic_i[i].str, first_substr);
		if (len == slen(first_substr)) {
			code[dic.size].num = i;
			break;
		}
	}
	//free(first_substr);
}