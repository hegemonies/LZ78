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
	//FILE *in = fopen("txt/eng.txt", "r");

/*--------------------------CREATE TO DICTIONARY----------------*/
	Dictionary dic;
	dic_init(&dic);

	fill_dic(&dic, "txt/eng.txt");
	print_dic(dic);

	return 0;
	
/*--------------------------CREATE TO CODE----------------------*/
	//Code *code = code_init(dic.capacity);
/*--------------------------COMPRES-----------------------------*/
	/*
	compres(&dic, code, in);

	fclose(in);
	*/
/*------------------------WRITE TO FILE OF COMPRESS--------------*/
	/*
	FILE *out = fopen("out.bin", "w");

	encode_file(out, code, dic);

	fclose(out);

	//free_mem(code, dic);
	*/
/*--------------------------DECOMPRES---------------------------*/
	/*
	FILE *in_t = fopen("out.bin", "r");

	Code *codes = code_init(dic.capacity);

	decode_file(in_t, codes);

	//print_code(codes, dic.size);

	fclose(in_t);

	FILE *out_t = fopen("dec_out.txt", "w");

	write_to_file_decode(out_t, codes, dic);

	fclose(out_t);
	*/
/*---------------------------------------------------------------*/
	//return 0;
}
