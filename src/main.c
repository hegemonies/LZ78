#include <stdio.h>
#include <stdlib.h>
#include "lz78.h"
#include "coder.h"
#include "strings.h"

#define DIC_CAPACITY 65536

void print_dic(Dictionary dic)
{
	printf("Dictionary:\n");
	for (int i = 0; i < dic.size; i++) {
		printf("%d, '%s'\n", i, dic.dic_i[i].str);
	}
}

void print_code(Code *code)
{
	printf("Code:\n");
	for (int i = 0; code[i].str != '~'; i++) {
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

int main(int argc, char* argv[])
{
	/*
		FILE *in = fopen("out.lz78", "r");
		Dictionary dic;
		dic_init(&dic);

		Code *codes = code_init(DIC_CAPACITY);

		decode_file(in, codes);

		//print_code(codes);

		fill_dic(&dic, codes);

		//print_dic(dic);

		fclose(in);
*/
/*--------------------------COMPRES------------------------------*/
	
	if (!scmp(argv[1], "-c")) {
		FILE *in = fopen(argv[4], "r");

		Dictionary dic;
		dic_init(&dic);

		Code *code = code_init(dic.capacity);

		compres(&dic, code, in);

		fclose(in);

		FILE *out = fopen(argv[3], "w");

		encode_file(out, code, dic);

		fclose(out);
		return 0;
	}
	
/*--------------------------DECOMPRES---------------------------*/
	
	if (!scmp(argv[1], "-d")) {
		FILE *in = fopen(argv[4], "r");

		Dictionary dic;
		dic_init(&dic);

		Code *codes = code_init(DIC_CAPACITY);
		
		decode_file(in, codes);
//print_code(codes);
//printf("\n");
	
		fill_dic(&dic, codes);

		fclose(in);
//print_dic(dic);
		FILE *out = fopen(argv[3], "w");

		write_to_file_decode(out, codes, dic);

		fclose(out);
		return 0;
	}
	
/*---------------------------------------------------------------*/
	/*
	printf("Help:\n");
	printf("lz78compress -c -o file.lz78 file.txt # сжатие file.txt в file.lz78 \n");
	printf("lz78compress -d -o file1.txt file.lz78 # распаковка file.lz78 в file1.txt \n");
	*/
	return 0;
}
