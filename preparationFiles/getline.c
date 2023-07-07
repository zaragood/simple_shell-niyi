#include <stdio.h>
#include <stdlib.h>

int main() {
	char *lineptr = NULL;
	size_t n = 0;

	printf("$ ");
	getline(&lineptr, &n, stdin);

	printf("%s", lineptr);
	free(lineptr);
}

