int main(){
  int *p = (int *) 0x20000000;
  int accumulator = 0;
  for(int i = 0; i < 0x1000000; i++){
    accumulator+= *(p++);
  }
  return accumulator;
}
