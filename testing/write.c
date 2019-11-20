void w(char a)
{
	char *putc = (char*) 0x30000004;
	*putc = a; 
}

int main()
{
	w('A');
	return 0;
}
