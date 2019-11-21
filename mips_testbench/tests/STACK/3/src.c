int fib(int n);

int main()
{
	// asm("li $sp, 0x24fffffc; sw	$ra, 28($sp); sw	$s8, 24($sp); move $s8, $sp;");
	return fib(13);
}
int fib(int n)
{
	if ( n <= 1 ) return n;
	return fib(n-1) + fib(n-2);
}
