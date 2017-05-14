#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lz78.h"
#include "coder.h"
#include "strings.h"

void print_dic_and_code(Dictionary dic, Code *code)
{
	printf("Dictionary:\n");
	for (int i = 0; i < dic.size; i++) {
		printf("%d, '%s'\n", i, dic.dic_i[i].str);
	}
	
	printf("Code:\n");
	for (int i = 0; i < dic.size; i++) {
		printf("%d, %c\n", code[i].num, code[i].str);
	}
}

int main(void)
{
	FILE *in = fopen("txt/war.txt", "r");

/*--------------------------CREATE TO DICTIONARY----------------*/
	Dictionary dic;
	dic_init(&dic);
/*--------------------------CREATE TO CODE----------------------*/
	Code *code = calloc(dic.capacity, sizeof(Code));
	code_init(code);

/*--------------------------COMPRES-----------------------------*/
	compres(&dic, code, in);
/*--------------------------DECOMPRES---------------------------*/
	Dictionary dic_t;
	dic_init(&dic_t);
	for (int i = 0; code[i].str; i++) {// TODOOOOOO

		if (!code[i].num) {
			dic_t.dic_i[dic.size].str = calloc(1, sizeof(char));
			char *buf = malloc(sizeof(char) + 1);
			buf[1] = 0;
			scat(buf, &code[i].str);
			scat(dic_t.dic_i[dic.size].str, buf);
			free(buf);
			continue;
		} else {
			char *buf = malloc(sizeof(char) * slen(dic_t.dic_i[code[i].num].str) + 2);
			scat(buf, dic_t.dic_i[code[i].num].str);
			buf[slen(dic_t.dic_i[code[i].num].str)] = 0;
			scat(buf, &code[i].str);
			printf("%s\n", buf);
			free(buf);
		}
	}



/*---------------------------------------------------------------*/

	//FILE *out = fopen("total.lz78", "w");
	
	//print_dic_and_code(dic, code);
	
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
