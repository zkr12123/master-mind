#include <iostream>
#include <vector>

//this tests pool_generator

std::vector<int> pool_generator(int length, int num, int count);
int pow(int a, int b);

int main(){
  std::cout << "pumping vectors..." << std::endl;
  int num = 6;
  int length = 4;
  std::vector<std::vector<int>> pool;

  for(int i = 0; i < pow(num, length); i++){
    pool.push_back(pool_generator(length, num, i));
  }

  std::cout << "pool size: " << pool.size() << std::endl;

  for(int i = 0; i < pool.size(); i++){
    for(int j = 0; j < pool[i].size(); j++){
      std::cout << pool[i][j] << " ";
    }
    std::cout << std::endl;
  }


}

/*int main(){
  int n;
  std::cout << "input n" << std::endl;
  std::cin >> n;
  std::vector<int> v = pool_generator(15, 15, n);
  for(int i = 0; i < v.size(); i++){
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}*/



std::vector<int> pool_generator(int length, int num, int count){
  //int set_length = pow(num, length);
  std::vector<int> v, tmp;
  //int tmp = count;
  for(int i = 0; i < length; i++){
    v.push_back(0);
  }

  int quotient = count;
  int remainder;
  while(quotient != 0){
    remainder = quotient % num;
    quotient = (int) quotient / num;
    tmp.push_back(remainder);
  }

  for(int i = v.size() - 1, j = 0; j < tmp.size(); i--, j++){
    v[i] = tmp[j];
  }

  return v;
}

int pow(int a, int b){
  int n = a;
  for(int i = 1; i < b; i++){
    n = n * a;
  }
  return n;
}
