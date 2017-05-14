#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* ----------------------------------СТРУКТУРЫ------------------------------*/
typedef struct {
	int num;
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

/*----------------------------------СТРИНГИ---------------------------------*/

int slen(char *str)
{
	int count = 0;;
	for (int i = 0; str[i] != '\0'; i++) {
		count++;
	}
	return count++;
}

int sspn(char *str, const char *substr)
{
	int count = 0;
	for (int i = 0; str[i] != 0; i++) {
		if (str[i] == substr[i]) {
			count++;
		} else {
			return count;
		}
	}
	return count;
}

char *scpy(char *des, const char *src)
{
	int i;
	for (i = 0; src[i] != 0; i++) {
		des[i] = src[i];
	}
	des[i] = 0;
	return des;
}

char *scat(char *des, char *src)
{
	int j = slen(des);
	for (int i = 0; src[i] != 0; i++) {
		des[j] = src[i];
		j++;
	}
	des[j] = 0;
	return des;
}

/*-------------------------------------------------------------------*/

int find_i(Dictionary dic, char *tmp)
{
	if (!strcmp("\n", tmp)) {
		return 1;
	}
	for (int i = 0; i < dic.size; i++) {
		int len = sspn(dic.dic_i[i].str, tmp);
		if (len == slen(tmp)) {
			return 0;
		}
	}
	return -1;
}

void free_all(char *tmp_dic, Dictionary dic)
{
	for (int i = 1; i < dic.capacity; i++) {
		free(dic.dic_i[i].str);
	}
	free(dic.dic_i);
	free(tmp_dic);
}

void find_code(Code *code, Dictionary dic)
{
	if (slen(dic.dic_i[dic.size].str) == 1) {
		code[dic.size].num = 0;
		code[dic.size].str = dic.dic_i[dic.size].str[0];
		//strcat(code[dic.size].str, dic.dic_i[dic.size]);
		return;
	}
//printf("dic.dic_i[dic.size].str%d\n", dic.dic_i[dic.size].str[slen(dic.dic_i[dic.size].str)]);

	char second_substr = dic.dic_i[dic.size].str[slen(dic.dic_i[dic.size].str) - 1];
	code[dic.size].str = second_substr;
	//strcat(code[dic.size].str, second_substr);

	char *first_substr = malloc(sizeof(char) * slen(dic.dic_i[dic.size].str));
	scat(first_substr, dic.dic_i[dic.size].str);
	first_substr[slen(dic.dic_i[dic.size].str) - 1] = '\0';
//printf("%s\n", first_substr);

	for (int i = 0; i < dic.size; i++) {
		int len = sspn(dic.dic_i[i].str, first_substr);
		if (len == slen(first_substr)) {
			code[dic.size].num = i;
			break;
		}
	}
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

	Code *code = malloc(sizeof(Code) * dic.capacity);
	//code[0] = malloc(sizeof(Code));
	code[0].num = 0;
	code[0].str = '\0';

	char tmp;
	char *tmp_dic = malloc(sizeof(char) * 256);

	while (fread(&tmp, 1, 1, in)) {
	//printf("start while:\n");
	//printf("tmp : %c\n", tmp);
		scat(tmp_dic, &tmp);
	//printf("tmp_dic : %s\n", tmp_dic);
		int tmp_i = find_i(dic, tmp_dic);
		if (tmp_i == 1) {
			break;
		}
		if (!tmp_i) {
			continue;
		} else {
		//printf("%s\n", tmp_dic);
			dic.dic_i[dic.size].str = malloc(sizeof(char) * slen(tmp_dic));
			scat(dic.dic_i[dic.size].str, tmp_dic);

			find_code(code, dic);

			dic.size++;
			*tmp_dic = '\0';

			
		}
	}
	
	//FILE *out = fopen("total.lz78", "w");
	printf("Dictionary:\n");
	for (int i = 0; i < dic.size ; i++) {
		printf("%d, '%s'\n", i, dic.dic_i[i].str);
	}
	
	printf("Code:\n");
	for (int i = 0; i < dic.size; i++) {
		printf("%d, %c\n", code[i].num, code[i].str);
	}
	
	//fclose(out);
	fclose(in);

	for (int i = 1; i < dic.capacity; i++) {
		free(dic.dic_i[i].str);
	}
	free(dic.dic_i);
	free(tmp_dic);
	//free_all(tmp_dic, &dic);
}
