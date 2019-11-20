#include <stdio.h>
int main()
{
	char gotten_character;
	fgetc(gotten_character, 1, stdin); // scanning one character from the terminal
	return gotten_character;
}
