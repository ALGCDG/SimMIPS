int f();

int main()
{
    asm("li $sp, 0x34fffffc;");
    f();
    return 0;
}

int f()
{
    return 1;
}



