#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int n_str;
	char *str;
} Dictionary;

void init_dic(Dictionary **arr_dic, int n)
{
	arr_dic = realloc(arr_dic, n);
	if (!arr_dic) {
		return;
	}
	arr_dic[n] = malloc(sizeof(Dictionary*));
}

int main(int argc, char *argv[])
{
	
	//FILE *in = fopen(argv[4], "r");
	//FILE *out = fopen(argv[3], "w");
	
	FILE *file_in = fopen("war.txt", "r");
	FILE *file_out = fopen("total.lz78", "w");

	Dictionary **arr_dic = malloc(sizeof(Dictionary*));
	//Dictionary *pointer;
	//init_dic(arr_dic, 1);

	
	char *tmp = malloc(sizeof(char));
	char *buf = malloc(sizeof(char) * 512);
	int t;
	for (int i = 0; ((t = fread(tmp, 1, 1, file_in)) && !feof(file_in)); i++) {
		//if (!ferror(file_in)) {
		//buf = tmp;
		strcat(buf, tmp);
		if (!arr_dic[i]) {
			//init_dic(arr_dic, i);
			printf("1\n");
			arr_dic[i] = malloc(sizeof(Dictionary*));
			arr_dic[i]->n_str = i;
			arr_dic[i]->str = buf;
			//i--;
			free(buf);
			//buf = NULL;
			continue;
		}

		if (arr_dic[i] && !strcmp(arr_dic[i]->str, buf)) {
			strcat(buf, tmp);
			t = fread(tmp, 1, 1, file_in);
		}
		
			
			for (int i = 0; arr_dic[i]; i++) {
				char *buf = malloc(sizeof(char) * 512);
				buf = tmp;
				if (!arr_dic[i]) {
					init_dic(arr_dic, i);
					arr_dic[i]->n_str = i;
					arr_dic[i]->str = buf;
					//i--;
					free(buf);
					continue;
				}
				if (arr_dic[i] && !strcmp(arr_dic[i]->str, buf)) {
					strcat(buf, tmp);
					fread(tmp, 1, 1, file_in);
				}
			}
			
		//}
	
	}
	for (int i = 0; arr_dic[i]; i++) {
		printf("%d :: %s\n", arr_dic[i]->n_str, arr_dic[i]->str);
	}
	
/*
	char *tmp = malloc(sizeof(char));

	arr_dic[0]->n_str = 0;
	arr_dic[0]->str = "";
con:
	for (int i = 0; (fread(tmp, 1, 1, file_in) && !ferror(file_in)); i++) {
		char *buf = malloc(sizeof(char) * 512);
		strcat(buf, tmp);
		if (!arr_dic[i + 1]) {
			arr_dic[i + 1] = malloc(sizeof(Dictionary*));
			arr_dic[i + 1]->n_str = i + 1;
			arr_dic[i + 1]->str = buf;
			continue;
		}
		if (arr_dic[i] && (strspn(arr_dic[i]->str, buf) == strlen(arr_dic[i]->str))) {
			strcat(buf, tmp);
			continue;
		} else if (strspn(arr_dic[i]->str, buf) < strlen(arr_dic[i]->str))
	}

*/

	

	fclose(file_in);
	fclose(file_out);
	return 0;
}