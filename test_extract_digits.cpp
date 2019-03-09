#include <iostream>
#include <vector>
//this tests extract_digits
//this function extracts single digit (except 0)
void extract_digits(int num, std::vector<int>& v);
int num_of_digits(int num);
int pow(int a, int b);

   int main(){

       int a;
       std::vector<int> v;
       std::cin >> a;
       extract_digits(a, v);
       for(int i = 0; i < v.size(); i++){
         std::cout << v[i] << std::endl;
       }
    std::cout<<"life is lonly";
    return 0;
    }

    int num_of_digits(int num){//returns number of digits in an int
      int i = 10, j = 1;
      while(true){
        if(num < i){
          return j;
        }
        i = i * 10;
        j = j + 1;
      }
    }

    void extract_digits(int num, std::vector<int>& v){ //extract digits from an int into a vector
      int length = num_of_digits(num);
      if(length == 1){
        v.push_back(num);
      }
      else{
        int lsb = num % 10;
        v.push_back(lsb);
        int tmp = lsb;

        for(int i = 100, j = 10; i <= pow(10, length - 1); i = i * 10, j = j * 10){
          v.push_back((num % i - tmp) / j);
          tmp = num % i;
        }

        v.push_back((num - tmp) / pow(10, length - 1));
      }
    }

      int pow(int a, int b){
        int n = a;
        for(int i = 1; i < b; i++){
          n = n * a;
        }
        return n;
      }
