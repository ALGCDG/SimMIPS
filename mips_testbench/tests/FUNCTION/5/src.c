void f(int *x);
int main()
{
    asm("li $sp, 0x34fffffc;");

    int a = 2;
    f(a);
    return a;
}

void f(int *x)
{
    *x = *x * 2 + 1;
    return;
}