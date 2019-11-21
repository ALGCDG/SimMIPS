void swap(int *a, int *b);

int main()
{
	asm("li $sp, 0x34fffffc;");
	int x, y;
	x = 5;
	y = 7;
	swap(&x,&y);
	return ((7==x && 5==y)); 
}
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}