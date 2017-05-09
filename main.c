#include <stdio.h>
#include <string.h>

typedef struct {
	int n_str;
	char *str;
} Dictionary;

void init_dic(Dictionary **arr_dic, int *n)
{
	if (!arr_dic[*n]) {
		arr_dic[*n] = malloc(sizeof(Dictionary*));
		*n++;
	}
}

int main(int argc, char *argv[])
{
	/*
	FILE *in = fopen(argv[4], "r");
	FILE *out = fopen(argv[3], "w");
	*/
	FILE *in = fopen("war.txt", "r");
	FILE *out = fopen("total.lz78", "w");

	Dictionary **arr_dic = malloc(sizeof(Dictionary*));
	int count_dic = 0;

	init_dic(arr_dic, &count_dic);

	//**
	char *tmp = malloc(sizeof(char));
	for (fread(tmp, 1, 1, in)) {
		char *buf = malloc(sizeof(char) * 512);
		if (!ferror(in)) {
			for (int i = 0; arr_dic[i]; i++) {
				if (arr_dic[i] && !strcmp(arr_dic[i]->str, tmp)) {
					strcat(arr_dic[i]->str, tmp);
					fread(tmp, 1, 1, in);
					continue;
				}
				if (arr_dic[i] && ())
				if (!arr_dic[i]) {
					init_dic(arr_dic, 1);
					arr_dic[i]->n_str = i;
					arr_dic[i]->str = tmp;
					//запись в структуру словаря
				}
			}
		}
		if (tmp) {
			free(tmp);
		}
		
	}
	///**
	fclose(in);
	fclose(out);
	return 0;
}