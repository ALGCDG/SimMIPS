float f();
int main()
{
    asm("li $sp, 0x34fffffc;");

    f();
    return 0;
}

float f()
{
    return 1;
}
