void f(const int &x)
{
    int a = x * 2 + 1;
    return;
}

int main()
{
    int a = 0;
    f(a);
    return a;
}

