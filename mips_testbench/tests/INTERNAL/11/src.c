void vec_prod_3d( const int vec1[],  const int vec2[], int vec3[]);
int dot_prod( const int vec1[],  const int vec2[], int size);

int main(){
  static const int vec1[3] = {7, -1, 62};
  static const int vec2[3] = {-7, 0, 105};
  int vec3[3];
  vec_prod_3d(vec1,vec2,vec3);
  int dot_sum = dot_prod(vec1,vec3,3);
  dot_sum+= dot_prod(vec2,vec3,3);
  return dot_sum;
}

void vec_prod_3d(const int vec1[], const int vec2[], int vec3[]){
  int i = vec1[1]*vec2[2] - vec1[2]*vec2[1];
  int j = -(vec1[0]*vec2[2] - vec1[2]*vec2[0]);
  int k = vec1[0]*vec2[1] - vec1[1]*vec2[0];
  vec3[0] = i;
  vec3[1] = j;
  vec3[2] = k;
  return;
}

int dot_prod(const int vec1[], const int vec2[], int size){
  int accum = 0;
  for(int i = 0; i < size; i++){
    accum += vec1[i]*vec2[i];
  }
  return accum;
}
