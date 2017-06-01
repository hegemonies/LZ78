#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int i;
	int count;
	char *str;
} Array;

int main(void)
{
	Array array[20];

	int ar[] = {0, 9, 1, 12, 0, 5, 2};
	char *arr[] = {"ah", "bb", "ci", "dg", "el", "fb", "qt"};
	printf("Source:\ni :: count :: str\n");
	for (int i = 0; i < 7; i++) {
		array[i].i = i;
		array[i].count = ar[i];
		array[i].str = malloc(sizeof(char) * strlen(arr[i]));
		strcat(array[i].str, arr[i]);
		printf("%d :: %d :: %s\n", array[i].i, array[i].count, array[i].str);
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (array[i].count < array[j].count) {
				Array tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	printf("\nResult:\ni :: count :: str\n");
	for (int i = 0; i < 7; i++) {
		printf("%d :: %d :: %s\n", array[i].i, array[i].count, array[i].str);
	}
	int sum = 0;
	for (int i = 0; i < 7; i++) {
		sum += array[i].count;
	}
	int avarage = sum / 7;
	for (int i = 0; i < avarage; i++) {
		//array[i].i = 0;
		array[i].count = 0;
		free(array[i].str);
		array[i].str = NULL;
	}
	printf("\nResult after alghotm:\ni :: count :: str\n");
	for (int i = 0; i < 7; i++) {
		if (array[i].str != NULL) {
			printf("%d :: %d :: %s\n", array[i].i, array[i].count, array[i].str);
			continue;
		}
		printf("%d :: %d :: NULL\n", array[i].i, array[i].count);
	}

	/*-----------------------------------*/
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (array[i].i < array[j].i) {
				Array tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	printf("\nSort by i:\ni :: count :: str\n");
	for (int i = 0; i < 7; i++) {
		if (array[i].str != NULL) {
			printf("%d :: %d :: %s\n", array[i].i, array[i].count, array[i].str);
			continue;
		}
		printf("%d :: %d :: NULL\n", array[i].i, array[i].count);
	}
	/*----*/
	Array array_copy[20];
	for (int i = 0; i < 7; i++) {
		array_copy[i].i = array[i].i;
		array_copy[i].count = array[i].count;
		if (array[i].str != NULL) {
			array_copy[i].str = calloc(strlen(array[i].str), sizeof(char));
			strcat(array_copy[i].str, array[i].str);
			continue;
		}
		array_copy[i].str = NULL;
	}
	printf("\nResult after copy:\ni :: count :: str\n");
	for (int i = 0; i < 7; i++) {
		if (array_copy[i].str != NULL) {
			printf("%d :: %d :: %s\n", array_copy[i].i, array_copy[i].count, array_copy[i].str);
			continue;
		}
		printf("%d :: %d :: NULL\n", array[i].i, array[i].count);
	}
	for (int i = 0; i < 7; i++) {
		if (!array_copy[i].str) {
			array_copy[i].str = calloc(4, sizeof(char));
			array_copy[i].str = "POP";
		}
	}
	printf("\nResult !!!:\ni :: count :: str\n");
	for (int i = 0; i < 7; i++) {
		if (array_copy[i].str != NULL) {
			printf("%d :: %d :: %s\n", array_copy[i].i, array_copy[i].count, array_copy[i].str);
			continue;
		}
		printf("%d :: %d :: NULL\n", array[i].i, array[i].count);
	}
}