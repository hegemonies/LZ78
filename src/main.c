#include <stdio.h>
#include <stdlib.h>
#include "lz78.h"
#include "coder.h"
#include "strings.h"

void print_dic(Dictionary dic)
{
	for (int i = 0; i < dic.size; i++) {
		printf("%d :: %d, '%s'\n", i, dic.dic_i[i].count, dic.dic_i[i].str);
	}
	printf("\n");
}

void print_code(Code *code)
{
	printf("Code:\n");
	printf("%d, '%c'\n", code[0].num, code[0].str);
	for (int i = 1; code[i].str != 0; i++) {
		printf("%d, '%c'\n", code[i].num, code[i].str);
	}
}

int main(int argc, char* argv[])
{
	int dic_capacity;
	printf("Enter the volume of the dictionary: ");
	scanf("%d", &dic_capacity);
/*--------------------------COMPRES------------------------------*/
	if (!scmp(argv[1], "-c")  && !scmp(argv[2], "-o")) {
		FILE *in = fopen(argv[4], "r");

		Dictionary dic;
		dic_init(&dic, dic_capacity);

		Code *code = code_init(dic.capacity);

		compres(&dic, code, in);
print_code(code);
print_dic(dic);

		fclose(in);

		FILE *out = fopen(argv[3], "w");

		encode_file(out, code, dic);

		fclose(out);
		return 0;
	}
/*--------------------------DECOMPRES---------------------------*/
	
	if (!scmp(argv[1], "-d") && !scmp(argv[2], "-o")) {
		//FILE *in = fopen("out.lz78", "r");
		FILE *in = fopen(argv[4], "r");

		Dictionary dic;
		dic_init(&dic, dic_capacity);

		Code *codes = code_init(dic_capacity);

		decode_file(in, codes);
//print_code(codes);
//printf("\n");

		fill_dic(&dic, codes);
print_dic(dic);
return 0;
		fclose(in);

		FILE *out = fopen(argv[3], "w");

		write_to_file_decode(out, codes, dic);

		fclose(out);

		return 0;
	}
	
/*---------------------------------------------------------------*/

	printf("Help:\n");
	printf("lz78compress -c -o file.lz78 file.txt # сжатие file.txt в file.lz78 \n");
	printf("lz78compress -d -o file1.txt file.lz78 # распаковка file.lz78 в file1.txt \n");
	
	return 0;
}
