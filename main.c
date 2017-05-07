#include <stdio.h>

typedef struct {
	int n_str;
	char ch;
} Сode;

typedef struct {
	int n_str;
	char *str;
} Dictionary;

void init_dic(Dictionary **arr_dic, int n)
{
	for (int i = 0; i < n; i++) {
		if (!arr_dic[i]) {
			arr_dic[i] = malloc(sizeof(Dictionary*));	
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *in = fopen(argv[4], "r");
	FILE *out = fopen(argv[3], "w");

	Code **arr_code = malloc(sizeof(Code*));
	Dictionary **arr_dic = malloc(sizeof(Dictionary*));

	init_dic(arr_dic, 1);

	char ex[] = "kot kolom rubil slona";
	
	for (int i = 0; ex; i++) {
		for (int j = 0; arr_dic[j]; j++) {
			if (ex[i] != arr_dic[j]->str) {

			}
		}
	}
	
	fclose(in);
	fclose(out);
	return 0;
}