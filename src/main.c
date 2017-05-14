#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lz78.h"
#include "coder.h"
#include "strings.h"

int main(void)
{
	FILE *in = fopen("txt/war.txt", "r");

	Dictionary dic;
	dic_init(&dic);

	Code *code = calloc(dic.capacity, sizeof(Code));
	code_init(code);

	char tmp;
	//char *tmp_dic = malloc(sizeof(char) * 256);
	char *tmp_dic = calloc(256, sizeof(char));

	while (fread(&tmp, 1, 1, in)) {
	//printf("start while:\n");
	//printf("tmp : %c\n", tmp);
		strcat(tmp_dic, &tmp);
	//printf("tmp_dic : %s\n", tmp_dic);
		int tmp_i = find_i(dic, tmp_dic);
		if (tmp_i == 1) {
			break;
		}
		if (!tmp_i) {
			continue;
		} else {
		//printf("%s\n", tmp_dic);
			//dic.dic_i[dic.size].str = malloc(sizeof(char) * slen(tmp_dic));
			dic.dic_i[dic.size].str = calloc(slen(tmp_dic), sizeof(char));
			strcat(dic.dic_i[dic.size].str, tmp_dic);

			find_code(code, dic);

			dic.size++;
			*tmp_dic = '\0';
		}
	}
	
	//FILE *out = fopen("total.lz78", "w");
	printf("Dictionary:\n");
	for (int i = 0; i < dic.size; i++) {
		printf("%d, '%s'\n", i, dic.dic_i[i].str);
	}
	
	printf("Code:\n");
	for (int i = 0; i < dic.size; i++) {
		printf("%d, %c\n", code[i].num, code[i].str);
	}
	
	/* нафиг фри
	for (int i = 1; i < dic.size; i++) {
		//free(dic.dic_i[i].str);
		dic.dic_i[i].str = NULL;
	}
	//free(code);
	//code = NULL;
	//dic.dic_i = NULL;
	//tmp_dic = NULL;
	//free(dic.dic_i);
	//free(tmp_dic);
	//free_all(tmp_dic, &dic);
	*/
	fclose(in);
	//fclose(out);
}
