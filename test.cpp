#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

//this checks check_repeat, check_contain, and give_feedback
//also fixes bug
//wrong, need fix, fixed, still wrong

void set_random_seed();
int randn(int n);
bool check_contain(int n, const std::vector<int>& v);
int check_repeat(const std::vector<int>& v);

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
        /// write here your implementation for this function
        /// which takes in input an attempt
        /// and provides feedback in terms of black hits
        /// and white hits (see linked paper)
        std::vector<int> black;
        std::vector<int> whiteseq;
        std::vector<int> whiteatt;

        for(int i = 0; i < attempt.size(); i++){
          if(attempt[i] == sequence[i]){
            black.push_back(i);
          }
        }
        black_hits = black.size();

        for(int i = 0; i < attempt.size(); i++){ //hopefully fixed
          for(int j = 0; j < sequence.size(); j++){
            if((attempt[i] == sequence[j]) && (!check_contain(j, black)) && (!check_contain(i, black)) && (!check_contain(j, whiteseq)) && (!check_contain(i, whiteatt)) ){
              whiteseq.push_back(j);
              whiteatt.push_back(i);
            }
          }
        }

        white_hits = whiteseq.size();


        /*for(int i = 0; i < attempt.size(); i++){ //fatal bug: cannot use elimination of same index method
          for(int j = 0; j < sequence.size(); j++){
            if((attempt[i] == sequence[j]) && (!check_contain(j, black)) && (!check_contain(i, black))){ //found bug, position of both sequence and attempt shouldnt be taken into account when a black hit occurs
              //white.push_back(j); //contains repeated //found bug, j is position of sequence, since attempt is fixed to be compared with sequence, position of sequence is not repeated when position of sequence is pushed_back
              whiteatt.push_back(i);
              whiteseq.push_back(j);
            }
          }
        }

        if(check_repeat(whiteatt) < check_repeat(whiteseq)){
          white_hits = check_repeat(whiteatt);
        }
        else{
          white_hits = check_repeat(whiteseq);
        }*/

        //white_hits = check_repeat(white);

      /*  if(white.size() > 0){
          white_hits++;
          for(int i = 1; i < white.size(); i++){

            bool repeated = false;

            for(int j = 0; j < white.size() && !repeated; j++){
              if((white[i] == white[j]) && (i != j)){ //problem: repeated it self, fixed
                repeated = true;
              }
            }

            if(!repeated){
              white_hits++;
            }

          }
    } */ //problem

  }

    /// member data holding the sequence generated by generate_sequence
    /// do not alter this
    std::vector<int> sequence;

    /// member data holding the values for length of code and number of symbols
    /// do not alter these
    int length;
    int num;

    /// do not add any other member data,
    /// in particular note that any variables needed for function give_feedback
    /// need to be declared within give_feedback
    /// (they are not member data of the struct)

    /// you may add other member functions if needed
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
  int length = 10;
  int num = 9;
  maker.init(length, num);
  maker.generate_sequence();

  for(int i = 0; i < maker.sequence.size(); i++){
    std::cout << maker.sequence[i] << " ";
  }
  std::cout << std::endl;

  int black = 0, white = 0;
  int trial = 0;

  while(trial < 10){
    std::vector<int> attempt;
  for(int i = 0; i < length; i++){
    /*int tmp;
    std::cin >> tmp;
    attempt.push_back(tmp);*/
    attempt.push_back(randn(num));
  }

  for(int i = 0; i < attempt.size(); i++){
    std::cout << attempt[i] << " ";
  }
  std::cout << std::endl;

  maker.give_feedback(attempt, black, white);
  std::cout << black << " ; " << white << std::endl;

  black = 0;
  white = 0;
  trial ++;



}

return 0;
}

void set_random_seed(){
    std::srand(std::time(0));
}

int randn(int n){
    return std::rand() % n;
}

bool check_contain(int n, const std::vector<int>& v){ //check if  n is contained in vector v
  //bool contain = false;
  for(int i = 0; i < v.size(); i++){
    if(n == v[i]){
      //contain = true;
      return true;
    }
  }

  return false;
}

int check_repeat(const std::vector<int>& v){
  std::vector<int> single;

  for(int i = 0; i < v.size(); i++){
    bool repeat = false;
    for(int j = 0; j < single.size() && !repeat; j++){
      if((v[i] == single[j]) && (i != j)){
        repeat = true;
      }
    }
    if(!repeat){
      single.push_back(v[i]);
    }
  }

  return single.size();
}
