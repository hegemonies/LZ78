#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* ----------------------------------СТРУКТУРЫ------------------------------*/
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
		int t = sspn(dic.dic_i[i].str, tmp);
		if (t == slen(tmp)) {
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


int main(void)
{
	FILE *in = fopen("war.txt", "r");

	Dictionary dic;
	dic.capacity = 65536;
	dic.size = 1;
	dic.dic_i = malloc(sizeof(Dictionary_item) * dic.capacity);
	dic.dic_i[0].str = malloc(sizeof(char));
	dic.dic_i[0].str = "";

	char tmp;
	char *tmp_dic = malloc(sizeof(char) * 256);

	while (fread(&tmp, 1, 1, in)) {
	//printf("start while:\n");
	//printf("tmp : %c\n", tmp);
		scat(tmp_dic, &tmp);
	//printf("tmp_dic : %s\n", tmp_dic);
		int tmp_i = find_i(dic, tmp_dic);
		if(tmp_i == 1) {
			break;
		}
		if (!tmp_i) {
			continue;
		} else {
			printf("%s\n", tmp_dic);
			dic.dic_i[dic.size].str = malloc(sizeof(char) * slen(tmp_dic));
			scat(dic.dic_i[dic.size].str, tmp_dic);
			dic.size++;
			*tmp_dic = '\0';
		}
	}
	
	//FILE *out = fopen("total.lz78", "w");
	for (int i = 0; i < dic.size ; i++) {
		printf("%d, '%s'\n", i, dic.dic_i[i].str);
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
