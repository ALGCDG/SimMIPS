#include <stdio.h>
int main()
{
	char name[20];
	printf("please entre your name: ");
	fgets(name, 20, stdin);
	printf("\nHello ",name,"!\n");
	return 0;
}
