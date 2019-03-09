#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

//this tests random pumping

void set_random_seed();
int randn(int n);
int pow(int a, int b);

struct mm_solver{

    /// this member function sets the values for the member data
    /// representing the lenght of the code
    /// and the number of symbols (the symbols will be 0 to i_num - 1)
    /// (this should be a constructor in proper OOP but ok)
    /// do not alter the function interface (name, parameter list, void return)
    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
        std::vector<int> tmp;
        for(int i = 0; i < length; i++){
          tmp.push_back(randn(num));
        }
        set.push_back(tmp);

        while(set.size() < pow(num, length)){

          std::vector<int> tmp;
          bool repeated = false;
          for(int i = 0; i < length; i++){
            tmp.push_back(randn(num));
          }

          for(int i = 0; i < set.size() && !repeated; i++){
            if(tmp == set[i]){
              repeated = true;
            }
          }

          if(!repeated){
            set.push_back(tmp);
          }
        }




        /// you can include additional implementation lines here if needed

    }

    /// this member function creates an attempt to find the right code
    /// (see the other examples provided for clarifications)
    /// do not alter the function interface (name, parameter list, void return)
    void create_attempt(std::vector<int>& attempt){
        /// write your implementation here
    }

    /// this member function acquires the feedback about a certain attempt
    /// (see the other examples provided for clarifications)
    /// do not alter the function interface (name, parameter list, void return)
    void learn(std::vector<int>& attempt, int black_hits, int white_hits){
        /// write your implementation here
    }

    int length;
    int num;
    std::vector<std::vector<int>> set;

    /// you may add other member functions and member data as needed
    /// (keep in mind the distinction between member function variables
    /// and member data of the struct)

};

int main(){
  std::cout << "initializing" << std::endl;
  mm_solver test;
  test.init(6, 6);
  std::cout << "size: " << test.set.size() << std::endl << std::endl;
  for(int i = 0; i < test.set.size(); i++){
    for(int j = 0; j < test.set[i].size(); j++){
          std::cout << test.set[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}

void set_random_seed(){
    std::srand(std::time(0));
}

int randn(int n){
    return std::rand() % n;
}

int pow(int a, int b){
  int n = a;
  for(int i = 1; i < b; i++){
    n = n * a;
  }
  return n;
}
