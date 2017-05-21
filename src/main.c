#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lz78.h"
#include "coder.h"
#include "strings.h"

void print_dic(Dictionary dic)
{
	printf("Dictionary:\n");
	for (int i = 0; i < dic.size; i++) {
		printf("%d, '%s'\n", i, dic.dic_i[i].str);
	}
}

void print_code(Code *code, int size)
{
	printf("Code:\n");
	for (int i = 0; i < size; i++) {
		printf("%d, %c\n", code[i].num, code[i].str);
	}
}

void free_mem(Code *code, Dictionary dic)
{
	free(code);
	for (int i = 0; i < dic.size; i++) {
		free(dic.dic_i[i].str);
	}
	free(dic.dic_i);
}

int main()
{
	FILE *in = fopen("txt/war.txt", "r");

/*--------------------------CREATE TO DICTIONARY----------------*/
	Dictionary dic;
	dic_init(&dic);
/*--------------------------CREATE TO CODE----------------------*/
	Code *code = code_init(dic.capacity);
/*--------------------------COMPRES-----------------------------*/
	compres(&dic, code, in);

	fclose(in);
/*------------------------WRITE TO FILE OF COMPRESS--------------*/
	FILE *out = fopen("out.bin", "w");
	for (int i = 1; i < dic.size; i++) {
		encode_t(code[i], out);
	}
	fclose(out);

	//free_mem(code, dic);
/*--------------------------DECOMPRES---------------------------*/
	FILE *in_t = fopen("out.bin", "r");

	Code *codes = code_init(dic.capacity);

	decode_file(in_t, codes);

	print_code(codes, dic.size);

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
	return 0;
}
