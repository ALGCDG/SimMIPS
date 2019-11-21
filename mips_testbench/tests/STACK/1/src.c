
int succ(int x);

int main()
{
	// asm("li $sp, 0x34fffffc;");
	return succ(succ(succ(0)));
}
int succ(int x)
{
	return x + 1;
}
