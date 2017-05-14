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

	char tmp[2];
	char *tmp_dic = calloc(256, sizeof(char));
/*--------------------------COMPRES-----------------------------*/
	while (fread(&tmp, 1, 1, in)) {
		tmp[1] = 0;
		scat(tmp_dic, tmp);
		int tmp_i = find_i(dic, tmp_dic);
		if (tmp_i == 1) {
			break;
		} else if (!tmp_i) {
			continue;
		} else {
			dic.dic_i[dic.size].str = calloc(slen(tmp_dic), sizeof(char));
			strcat(dic.dic_i[dic.size].str, tmp_dic);

			find_code(code, dic);

			dic.size++;
			*tmp_dic = '\0';
		}
	}
/*--------------------DECOMPRES---------------------------------*/
	/*
	Dictionary dic_t;
	dic_init(*dic_t);
	*/



/*---------------------------------------------------------------*/

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
