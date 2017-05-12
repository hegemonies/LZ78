#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int n_str;
	char str;
} Dictionary;

int main(void)
{
	FILE *in = fopen("war.txt", "r");

	//Dictionary *arr[10];
	Dictionary **arr = malloc(sizeof(Dictionary) * 50);
	arr[0] = malloc(sizeof(Dictionary));
	arr[0]->n_str = 0;
	arr[0]->str = '\0';
	/*
	for (int i = 1; i < 10; i++) {
		arr[i] = NULL;
	}
	*/
	char tmp;
	while (fread(&tmp, 1, 1, in) && !feof(in)) {
		Dictionary dic_tmp;
		dic_tmp.n_str = 0;
		dic_tmp.str = tmp;
		printf("%d\n", tmp);
		for (int i = 0;; i++) {
			if (!arr[i + 1]) {
				arr[i + 1] = malloc(sizeof(Dictionary));
				arr[i + 1]->n_str = dic_tmp.n_str;
				arr[i + 1]->str = dic_tmp.str;
				//i = -1;
				break;
			}
			if (dic_tmp.str == arr[i + 1]->str && dic_tmp.n_str == arr[i + 1]->n_str) {
				dic_tmp.n_str = i + 1;
				printf("%d\n", tmp);
				fread(&tmp, 1, 1, in);
				if (feof(in)) {
					*arr[i + 2] = dic_tmp;
					break;
				}
				dic_tmp.str = tmp;
				continue;
			}

		}
	}


	FILE *out = fopen("total.txt", "w");
	for (int i = 0; arr[i]; i++) {
		fprintf(out, "%d,'%c'|", arr[i]->n_str, arr[i]->str);
	}
	fclose(out);
	fclose(in);
}
