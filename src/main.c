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

	fclose(in);
/*------------------------WRITE TO FILE OF COMPRESS--------------*/
	FILE *out = fopen("out.bin", "w");
	for (int i = 1; i < dic.size; i++) {
		encode_t(code[i], out);
	}
	fclose(out);
/*--------------------------DECOMPRES---------------------------*/
	FILE *in_t = fopen("out.bin", "r");

	Code *codes = calloc(dic.capacity, sizeof(Code));
	code_init(codes);

	decode_file(in_t, codes);

	fclose(in_t);

	FILE *out_t = fopen("dec_out.txt", "w");

	write_to_file(out_t, codes, dic);

	fclose(out_t);


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
	
	//fclose(out);
}
