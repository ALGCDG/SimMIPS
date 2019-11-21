int f(int x);

int g(int x);

int main()
{
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
