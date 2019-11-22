#include "../../../MIPS_IO.h"
int main()
{
	char name[20];
	char * welcome = "please entre your name: ";
	for ( int i = 0 ; i < 25; i++)
	{
		putc(welcome[i]);
	}
	char tmp;
	for (int i =0 ;i < 20 ; i++)
	{
		tmp = getc();
		if (-1 != tmp)
		{
			name[i] = tmp;
		}
		else
		{
			i = 20;
		}

	}
	putc('\n');
	char * hello = "Hello ";
	for ( int i = 0 ; i < 7; i++)
	{
		putc(hello[i]);
	}
	for ( int i = 0 ; i < 20; i++)
	{
		putc(name[i]);
	}
	putc('\n');
	return 0;
}
#include "../../../MIPS_IO.c"
