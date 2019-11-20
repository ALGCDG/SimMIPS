void f(int *x)
{
    *x = *x * 2 + 1;
    return;
}

int main()
{
    int a = 2;
    f(a);
    return a;
}

