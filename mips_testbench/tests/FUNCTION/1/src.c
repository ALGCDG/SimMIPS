char f();

int main()
{
    // asm("li $sp, 0x34fffffc;");
    f();
    return 0;
}

char f()
{
    return 1;
}


