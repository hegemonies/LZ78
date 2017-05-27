#include <stdio.h>

int slen(char *str)
{
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		count++;
	}
	return ++count;
}

int main(void)
{
	char text[] = "hello";
	printf("%d\n", slen(text));
}