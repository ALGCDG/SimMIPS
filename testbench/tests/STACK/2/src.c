void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	int x, y;
	x = 5;
	y = 7;
	swap(x,y);
	return (if(7==x && 5==y)); 
}
