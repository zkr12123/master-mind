#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <cmath>


void set_random_seed();
int randn(int n);
bool check_contain(int n, const std::vector<int>& v);
int check_repeat(const std::vector<int>& v);
void pool_generator(int length, int num, int count, std::vector<int>& v);
//int pow(int a, int b);
void give_feedback_trial(const std::vector<int>& attempt,const std::vector<int>& trial, int num, int& black_hits, int& white_hits);
int number_of_num(const std::vector<int>& v, int num);
int min(int n1, int n2);
//improved guessing algorithm for finding 0 black_hits
//the testing phase where (num_of_attempt < num) now also looks for vector with 0 black_hits
//this algorithm does not work well when length is significantly greater than num
//e.g. 30/8 because it takes too many steps to generate a vector with no black_hits
//fixed pool_generator to void according to requirement




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

    /// do not alter the function interface (name, parameter list, void return)
    void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){

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

        /*if((length > 7) && (num > 7)){
          for(int i = 0; i < length; i++){
            test_attempt.push_back(0);
          }

        }*/
        //else{
          for(int i = 0; i < pow(num, length); i++){
            std::vector<int> tmp;
            pool_generator(length, num, i, tmp);
            pool.push_back(tmp);
          }
        //}




        /// you can include additional implementation lines here if needed

    }

    /// this member function creates an attempt to find the right code
    /// (see the other examples provided for clarifications)
    /// do not alter the function interface (name, parameter list, void return)
    void create_attempt(std::vector<int>& attempt){
        /// write your implementation here

        /*if((length > 7) && (num > 7)){//higher situation

          if(num_of_attempt < num){//testing
            for(int i = 0; i < length; i++){
              attempt.push_back(num_of_attempt);
            }
          }
          else{//after test
            if(!found_test_attempt){//finding starting vector
              for(int i = 0; i < length; i++){
              attempt.push_back(randn(num));
            }
          }
          else{//start vector found
            attempt = test_attempt;
            attempt[check_index] = number[check_num];//check each index of the attempt with numbers from numbervector, starting with check_index = 0, check_num = 0
          }
          }

        }*/



        //else{attempt = pool[randn(pool.size())];}
        attempt = pool[randn(pool.size())];
    }

    void learn(std::vector<int>& attempt, int black_hits, int white_hits){
        /// write your implementation here
        /*if((length > 7) && (num > 7)){//higher situation

          if(num_of_attempt < num){//testing phase
            for(int i = 0; i < black_hits; i++){
              number.push_back(num_of_attempt);
            }
            if((black_hits == 0) && (!found_test_attempt)){//improvement
              found_test_attempt = true;
              test_attempt = attempt;
            }
          }
          else{
            if((black_hits == 0) && (!found_test_attempt)){//this now represents the worst case scenario //or situation when length is greater than num
              test_attempt = attempt;
              found_test_attempt = true;
              //black_tmp = black_hits; //starting test vector has 0 black_hits, already initialized to 0
            }
            else if(found_test_attempt){//actual test phase
              if(black_hits > black_tmp){
                test_attempt = attempt;
                number.erase(number.begin() + check_num);
                check_index++;
                check_num = 0;
                black_tmp = black_hits;
                tested_num.clear();
              }
              else{
                //check_num++;
                tested_num.push_back(number[check_num]);
                for(int i = 0; i < number.size(); i++){
                  if(!check_contain(number[i], tested_num)){
                    check_num = i;
                  }
                }
              }
            }


          }


          num_of_attempt++;
        }*/

        //else{
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
      //  }

    }


    int length;
    int num;
    std::vector<std::vector<int>> pool;
    //int num_of_attempt = 0;
    //std::vector<int> number;//contains the number of a number at each index, number represented by index
    //int black_tmp = 0;//starting test vector has 0 black_hits
    //int white_tmp;
    //std::vector<int> test_attempt;
    //std::vector<int> tested_num; //contains number already tested for blackhit, must be cleared for every check_index
    //bool found_test_attempt = false;
    //int check_index = 0; //contains the next index to be checked for blackhit
    //int check_num = 0;

  };

/*int main(){
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
}*/
int main(){
  while(true){
  set_random_seed();
  int length, num;
  std::cout << "enter length of sequence and number of possible values:" << std::endl;
  std::cin >> length >> num;



  int trial_limit = 10;
  int trial = 0;
  int total_attempts = 0;


  while(trial < trial_limit){
    int attempts = 0;
    int black_hits=0, white_hits=0;

    mm_solver solver;
    solver.init(length, num);

    mm_code_maker maker;
    maker.init(length, num);
    maker.generate_sequence();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(black_hits < length){
      std::vector<int> attempt;
      solver.create_attempt(attempt);
      maker.give_feedback(attempt, black_hits, white_hits);
      solver.learn(attempt, black_hits, white_hits);
      attempts++;
      total_attempts++;
    }
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "this trial takes: " << attempts << " attempts" << std::endl;
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;

  trial++;

}
std::cout << std::endl;

double average = total_attempts / trial_limit;
std::cout << "total attempts: " << total_attempts << std::endl;
std::cout << "average attempts each trial: " << average << std::endl;
}

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

bool check_contain(int n, const std::vector<int>& v){//return true if the vector contains n
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

  void pool_generator(int length, int num, int count, std::vector<int>& v){
    //int set_length = pow(num, length);
    std::vector<int> tmp;
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









/// add here the implementation for any other functions you wish to define and use
