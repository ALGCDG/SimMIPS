int w(int a)
{
	char *putc = (char*) 0x30000007;
	*putc = a; 
	return 0;
}

int main()
{
	return w((int)('A'));
}
