int dot_prod( const int vec1[], const int vec2[], int size);

int main(){
  static const int veca[10] = { -1, 3, 170, 4000, -70, 0, 666, 420, 69, -42};
  static const int vecv[10] = { 12, 13, 9000, 4307, -65, -100007, -50028, -1, -4, 7};
  int product = dot_prod(veca, vecv, 10);
  product += 14557061;
  return product;
}

int dot_prod( const int vec1[],  const int vec2[], int size){
  int accum = 0;
  for(int i = 0; i < size; i++){
    accum += vec1[i]*vec2[i];
  }
  return accum;
}
