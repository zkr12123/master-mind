#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

/// you can add other headers as needed
/// but only headers from the standard library
/// and not the algorithm header

/// do not use using namespace std

/// functions for random number generation, do not alter the declarations
void set_random_seed();
int randn(int n);
bool check_contain(int n, const std::vector<int>& v);
int check_repeat(const std::vector<int>& v);
std::vector<int> pool_generator(int length, int num, int count);
int pow(int a, int b);
void give_feedback_trial(const std::vector<int>& attempt,const std::vector<int>& trial, int num, int& black_hits, int& white_hits);
int number_of_num(const std::vector<int>& v, int num);
int min(int n1, int n2);
bool check_contain_vector(const std::vector<int>& v1, const std::vector<std::vector<int>>& v2);

/// you can define and use additional functions and structs,
/// add here the declarations for any other functions
/// and/or structs you wish to define and use
/// (the implementation for functions that don't belong to a struct
/// should be added after the main)

/// this is the struct definition for the code maker
/// do not alter the name


struct mm_code_maker{

    /// this member function sets the values for the member data
    /// representing the length of the code
    /// and the number of symbols (the symbols will be 0 to i_num - 1)
    /// (this should be a constructor in proper OOP but ok)
    /// do not alter this function
    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;
    }

    /// this member function generates a random sequence based
    /// on the length and num parameters stored as member data
    /// do not alter this function
    void generate_sequence(){
        for(int i = 0; i < length; i++){
            sequence.push_back(randn(num));
        }
    }

    /// do not alter the function interface (name, parameter list, void return)
    void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){
        /// write here your implementation for this function
        /// which takes in input an attempt
        /// and provides feedback in terms of black hits
        /// and white hits (see linked paper)
        int total_hits = 0;
        black_hits = 0;

        std::vector<int> n_attempt;
        std::vector<int> n_sequence;
        for(int i = 0; i < num; i++){
          n_attempt.push_back(number_of_num(attempt, i));
          n_sequence.push_back(number_of_num(sequence, i));
        }

        for(int i = 0; i < num; i++){
          total_hits = total_hits + min(n_sequence[i], n_attempt[i]);
        }

        for(int i = 0; i < length; i++){
          if(attempt[i] == sequence[i]){
            black_hits++;
          }
        }

        white_hits = total_hits - black_hits;

        /*std::vector<int> black;
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

        white_hits = whiteseq.size();*/


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

    /// this member function sets the values for the member data
    /// representing the lenght of the code
    /// and the number of symbols (the symbols will be 0 to i_num - 1)
    /// (this should be a constructor in proper OOP but ok)
    /// do not alter the function interface (name, parameter list, void return)
    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;

        if(length > 7 && num > 7){
          for(int i = 0; i < pow(num, length); i++){
            pool.push_back(pool_generator(length, num, i));
          }
        }




        /// you can include additional implementation lines here if needed

    }

    /// this member function creates an attempt to find the right code
    /// (see the other examples provided for clarifications)
    /// do not alter the function interface (name, parameter list, void return)
    void create_attempt(std::vector<int>& attempt){
        /// write your implementation here

        if(length > 7 && num > 7){

          if(num_of_attempt < length){
            for(int i = 0; i < length; i++){
              attempt.push_back(num_of_attempt);
            }
          }

          else{
            attempt.resize(length);
            while(check_contain_vector(attempt, bad_attempt)){
              std::vector<int> index_filled;
              for(int i = 0; i < number.size(); i++){
                for(int j = 0; j < number[i]; j++){
                  int tmp;
                  while(check_contain(randn(length), index_filled)){
                    tmp = randn(length);
                  }
                  attempt[tmp] = i;
                  index_filled.push_back(tmp);
                }
              }
            }


          }
        }

        else{attempt = pool[randn(pool.size())];}






    }

    /// this member function acquires the feedback about a certain attempt
    /// (see the other examples provided for clarifications)
    /// do not alter the function interface (name, parameter list, void return)
    void learn(std::vector<int>& attempt, int black_hits, int white_hits){
        /// write your implementation here
        if(length > 7 && num > 7){
          if(num_of_attempt < length){
            number.push_back(black_hits);
          }
          else{
            bad_attempt.push_back(attempt);
          }
        }

        else{
        std::vector<std::vector<int>> newpool;

          int black_new, white_new;
          for(int i = 0; i < pool.size(); i++){
            give_feedback_trial(attempt, pool[i], num, black_new, white_new);
            if((black_new == black_hits) && (white_new == white_hits)){
              newpool.push_back(pool[i]);
            }

          }
          pool.clear();
          pool = newpool;
        }

    }


    int length;
    int num;
    std::vector<std::vector<int>> pool;
    int num_of_attempt = 0;
    std::vector<int> number;//contains the number of a number at each index, number represented by index
    int black_tmp;
    int white_tmp;
    std::vector<std::vector<int>> bad_attempt;

  };

int main(){
    /// write the code for the main here in order to test your functions
    /// the main is not relevant for this assignment and we will remove it
    /// from the submissions during the marking
    set_random_seed();

    int length, num;
    std::cout << "enter length of sequence and number of possible values:" << std::endl;
    std::cin >> length >> num;

    mm_solver solver;
    solver.init(length, num);

    mm_code_maker maker;
    maker.init(length, num);
    maker.generate_sequence();

    int black_hits=0, white_hits=0;
    int attempts_limit = 5000;
    int attempts = 0;
    while((black_hits < length) && (attempts < attempts_limit)){
        std::vector<int> attempt;
        solver.create_attempt(attempt);
        maker.give_feedback(attempt, black_hits, white_hits);
        std::cout << "attempt: " << std::endl;
        for(int i = 0; i < attempt.size(); i++){
            std::cout << attempt[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "black pegs: " << black_hits << " " << " white pegs: " << white_hits << " ; " << solver.pool.size() << std::endl;
        solver.learn(attempt, black_hits, white_hits);
        attempts++;
    }

    if(black_hits == length){
        std::cout << "the solver has found the sequence in " << attempts << " attempts" << std::endl;
    }
    else{
        std::cout << "after " << attempts << " attempts still no solution" << std::endl;
    }
    std::cout << "the sequence generated by the code maker was:" << std::endl;
    for(int i = 0; i < maker.sequence.size(); i++){
        std::cout << maker.sequence[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

/// not a great implementation for set_random_seed and for randn;
/// if you are trying to get better results you may want to change
/// the implementation using C++11 features, see for instance
/// https://isocpp.org/files/papers/n3551.pdf
/// but don't change the interface/declaration of the functions

void set_random_seed(){
    std::srand(std::time(0));
}

int randn(int n){
    return std::rand() % n;
}

bool check_contain(int n, const std::vector<int>& v){
  bool contain = false;
  for(int i = 0; i < v.size() && !contain; i++){
    if(n == v[i]){
      contain = true;
    }
  }
  return contain;
}

int check_repeat(const std::vector<int>& v){
  std::vector<int> single;

  for(int i = 0; i < v.size(); i++){
    bool repeat = false;
    for(int j = 0; j < single.size() && !repeat; j++){
      if(v[i] == single[j] && i != j){
        repeat = true;
      }
    }
    if(!repeat){
      single.push_back(v[i]);
    }
  }

  return single.size();
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

  void give_feedback_trial(const std::vector<int>& attempt, const std::vector<int>& trial, int num, int& black_hits, int& white_hits){

    int total_hits = 0;
    black_hits = 0;
    int length = attempt.size();

    std::vector<int> n_attempt;
    std::vector<int> n_sequence;
    for(int i = 0; i < num; i++){
      n_attempt.push_back(number_of_num(trial, i));
      n_sequence.push_back(number_of_num(attempt, i));
    }

    for(int i = 0; i < num; i++){
      total_hits = total_hits + min(n_sequence[i], n_attempt[i]);
    }

    for(int i = 0; i < length; i++){
      if(trial[i] == attempt[i]){
        black_hits++;
      }
    }

    white_hits = total_hits - black_hits;

}

int min(int n1, int n2){//out put the smaller num of the two
  if(n1 < n2){
    return n1;
  }
  else{
    return n2;
  }

}

int number_of_num(const std::vector<int>& v, int num){
  int n = 0;
  for(int i = 0; i < v.size(); i++){
    if(v[i] == num){
      n++;
    }
  }
  return n;
}

bool check_contain_vector(const std::vector<int>& v1, const std::vector<std::vector<int>>& v2){ //check if v2 contains v1
  for(int i = 0; i < v2.size(); i++){
    if(v1 == v2[i]){
      return true;
    }
  }
  return false;

}
