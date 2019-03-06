#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void set_random_seed();
int randn(int n);

struct mm_code_maker{


    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
    }


    void generate_sequence(){
        for(int i = 0; i < length; i++){
            sequence.push_back(randn(num));
        }
    }


    void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){

        std::vector<int> black;
        std::vector<int> white;

        for(int i = 0; i < attempt.size(); i++){
          if(attempt[i] == sequence[i]){
            black_hits++;
            black.push_back(i);
          }
        }


        for(int i = 0; i < attempt.size(); i++){
          for(int j = 0; j < sequence.size(); j++){
            for(int k = 0; k < black.size(); k++){
              if((attempt[i] == sequence[j]) && (j != black[k])){
                white.push_back(j); //contains repeated white_hits
              }
            }
          }
        }

        if(white.size() > 0){
          //std::vector<int> truwhite;
          //truwhite.push_back(white[0]);
          white_hits++;
          for(int i = 1; i < white.size(); i++){

            bool repeated = false;

            for(int j = 0; j < white.size() && !repeated; j++){
              if(white[i] == white[j]){
                repeated = true;
              }
            }

            if(!repeated){
              //truwhite.push_back(white[i]);
              white_hits++;
            }

          }
    }

  }

    std::vector<int> sequence;
    int length;
    int num;

};


/// this is the struct definition for the solver, do not alter the name
struct mm_solver{

    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;

    }

    void create_attempt(std::vector<int>& attempt){
        /// write your implementation here
    }


    void learn(std::vector<int>& attempt, int black_hits, int white_hits){
        /// write your implementation here
    }

    int length;
    int num;

};

int main(){
  set_random_seed();
  mm_code_maker maker;
  maker.init(4, 6);
  maker.generate_sequence();

  for(int i = 0; i < maker.sequence.size(); i++){
    std::cout << maker.sequence[i] << " ";
  }
  std::cout << std::endl;

  int black = 0, white = 0;

  while(true){
    std::vector<int> attempt;
  for(int i = 0; i < 4; i++){
    int tmp;
    std::cin >> tmp;
    attempt.push_back(tmp);
  }

  maker.give_feedback(attempt, black, white);
  std::cout << black << " ; " << white << std::endl;

  black = 0;
  white = 0;



}

return 0;
}

void set_random_seed(){
    std::srand(std::time(0));
}

int randn(int n){
    return std::rand() % n;
}
