int f(int x)
{
	return x + 4;
}

int g(int x)
{
	return f(x) * 2;
}

int main()
{
	return g(1); // expecting return value of 10
}
