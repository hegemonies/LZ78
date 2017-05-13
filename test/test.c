#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int n_str;
	char str;
} Code;

typedef struct {
	char *str;
	//int count = 0;
} Dictionary_item;

typedef struct {
	Dictionary_item *dic_i;
	int size;
	int capacity;
} Dictionary;

int find_i(Dictionary dic, char *tmp)
{
	if (!strcmp("\0", tmp)) {
			return 1;
		}
	for (int i = 0; i < dic.size; i++) {
		int t = strspn(dic.dic_i[i].str, tmp);
		if (t == strlen(tmp)) {
			return 0;
		}
	}
	return -1;
}

int main(void)
{
	FILE *in = fopen("war.txt", "r");

	Dictionary dic;
	dic.capacity = 65536;
	dic.size = 1;
	dic.dic_i = malloc(sizeof(Dictionary_item) * dic.capacity);
	dic.dic_i[0].str = malloc(sizeof(char));
	dic.dic_i[0].str = "";
//printf("1\n");
	char tmp;
	char *tmp_dic = malloc(sizeof(char) * 256);
	while (fread(&tmp, 1, 1, in)) {
	printf("start while:\n");
	printf("tmp : %c\n", tmp);
		strcat(tmp_dic, &tmp);
	printf("tmp_dic : %s\n", tmp_dic);
		int tmp_i = find_i(dic, tmp_dic);
		if (tmp_i == 1) {
	//printf("НАШЕЛ КОНЕЦ ФАЙЛА\n");
			break;
		}
		if (!tmp_i) {
	//printf("НАШЕЛ ВХОЖДЕНИЕ\n");
	//printf("2\n");
			//strcat(tmp_dic, &tmp);
			continue;
		} else {
	//printf("3ашли\n");
			if(!strcmp(tmp_dic, "\0")) {
				break;
			}
			printf("%s\n", tmp_dic);
			dic.dic_i[dic.size].str = malloc(sizeof(char) * strlen(tmp_dic) + 1);
	//printf("РАЗ\n");
			//dic.dic_i[dic.size].str = tmp_dic;
			strcat(dic.dic_i[dic.size].str, tmp_dic);
	//printf("РАЗ\n");
			dic.dic_i[dic.size].str[strlen(dic.dic_i[dic.size].str) + 1] = 0;
	//printf("РАЗ\n");
			dic.size++;
	//printf("%s\n", dic.dic_i[dic.size].str);
			*tmp_dic = '\0';
	//printf("%s\n", tmp_dic);
		}
	}
	/*
	free(tmp_dic);
	for (int i = 0; i < dic.size ; i++) {
		free(dic.dic_i[i].str);
	}
	free(dic.dic_i);
	*/
	
	//FILE *out = fopen("total.lz78", "w");
	for (int i = 0; i < dic.size - 1; i++) {
		printf("%d, '%s'\n", i, dic.dic_i[i].str);
	}
	//fclose(out);
	fclose(in);
/*
	//Dictionary dic[20];
	//Dictionary *arr[10];
	for (int i = 1; i < 10; i++) {
		arr[i] = NULL;
	}
	Dictionary **arr = malloc(sizeof(Dictionary) * 20);
	//arr[0] = malloc(sizeof(Dictionary));
	arr[0].n_str = 0;
	arr[0].str = '\0';


	char tmp;
	while (fread(&tmp, 1, 1, in) && !feof(in)) {
		Dictionary dic_tmp;
		dic_tmp.n_str = 0;
		dic_tmp.str = tmp;
		//printf("%d\n", tmp);
		for (int i = 0;; i++) {
			if (!arr[i + 1]) {
				arr[i + 1] = malloc(sizeof(Dictionary));
				arr[i + 1].n_str = dic_tmp.n_str;
				arr[i + 1].str = dic_tmp.str;
				//i = -1;
				break;
			}
			if (dic_tmp.str == arr[i + 1]->str && dic_tmp.n_str == arr[i + 1].n_str) {
				dic_tmp.n_str = i + 1;
				//printf("%d\n", tmp);
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
	//for (int i = 0; arr[i]; i++) {
		fwrite(arr, 1, sizeof(arr), out);
	//}
	fclose(out);
	fclose(in);
*/
}
