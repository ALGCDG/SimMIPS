char LFSR(char a);
int main()
{
    return LFSR(LFSR(LFSR(1)));
}
char LFSR(char a)
{
    char one = (a >> 2) & 0b1;
    char two = (a >> 3) & 0b1;
    char x = one ^ two;
    return ((a << 1) + x);
}