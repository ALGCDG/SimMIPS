uint ioManager::get_word(){
    int input;
    input = getchar();
    return static_cast<uint>(input);
}

void ioManager::store_word(uint word){
    char out = 0xFF & word;
    putchar(out);
    return;
}
