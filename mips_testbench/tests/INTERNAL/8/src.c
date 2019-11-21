int main()
{
	// asm("li $sp, 0x34fffffc;");
	int product = 1;
	for (int i = 0; i < 10; i++)
	{
		product *= i;
	}	
	return 0;
}
