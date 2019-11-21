int putc(char a)
{
	int *o = (int *) 0x30000004;
       	*o = (int)a;
	return 0;	
}

int getc()
{
	int *i = (int *) 0x30000000;
	return *i;
}
