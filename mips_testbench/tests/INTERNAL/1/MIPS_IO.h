int putc(char a)
{
	int *o = (int *) 0x30000004;
       	*o = a;
	return 0;	
}

unsigned char getc()
{
	int *i = (int *) 0x30000000;
	return *i;
}
