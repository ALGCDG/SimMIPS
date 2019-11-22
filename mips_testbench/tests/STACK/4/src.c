int factorial(int x);

int main()
{
	// return factorial(7);
	return factorial(5);
}

int factorial(int x)
{
	if( x == 0 )
	{
		return 1;
	}
	else
	{
		return x * factorial(x - 1);
	}
}
