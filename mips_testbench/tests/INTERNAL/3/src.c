#include "../../../MIPS_IO.h"
int main()
{
	char * s = "Hello world!";
	for ( int i = 0; i < 13; i++)
	{
		putc(s[i]);
	}
	return 0;
}
