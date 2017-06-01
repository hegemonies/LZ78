#include <stdio.h>
#include <stdlib.h>
#include "lz78.h"
#include "coder.h"
#include "strings.h"

void help()
{
	printf("Help:\n");
	printf("lz78compress -c -o file.lz78 file.txt # сжатие file.txt в file.lz78 \n");
	printf("lz78compress -d -o file1.txt file.lz78 # распаковка file.lz78 в file1.txt \n");
}

int main(int argc, char* argv[])
{
	int dic_capacity = 65536;
	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL) {
		help();
		return 1;
	}
/*--------------------------COMPRES------------------------------*/
	if (!scmp(argv[1], "-c")  && !scmp(argv[2], "-o")) {
		FILE *in = fopen(argv[4], "r");
		if (!in) {
			help();
			return 1;
		}

		Dictionary dic;
		dic_init(&dic, dic_capacity);

		Code *code = code_init(dic.capacity);

		compres(&dic, code, in);

		fclose(in);

		FILE *out = fopen(argv[3], "w");

		encode_file(out, code, dic);

		fclose(out);

		printf("Complete!\n");

		return 0;
	}
/*--------------------------DECOMPRES---------------------------*/
	
	if (!scmp(argv[1], "-d") && !scmp(argv[2], "-o")) {
		FILE *in = fopen(argv[4], "r");
		if (!in) {
			help();
			return 1;
		}

		Dictionary dic;
		dic_init(&dic, dic_capacity);

		Code *codes = code_init(dic_capacity);

		decode_file(in, codes);

		fill_dic(&dic, codes);

		fclose(in);

		FILE *out = fopen(argv[3], "w");

		write_to_file_decode(out, codes, dic);

		fclose(out);

		printf("Complete!\n");

		return 0;
	}
	
/*---------------------------------------------------------------*/
	
	return 0;
}
