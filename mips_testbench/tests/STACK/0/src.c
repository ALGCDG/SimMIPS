int f(int x);

int g(int x);

int main()
{
	// asm("li $sp, 0x34fffffc;");
	// asm("li $sp, 0x32fffffc; sw	$ra, 28($sp); sw	$s8, 24($sp); move $s8, $sp;");

	return g(1); // expecting return value of 10
}

int f(int x)
{
	return x + 4;
}

int g(int x)
{
	return f(x) * 2;
}
