#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


void set_random_seed();
int randn(int n);
bool check_contain(int n, const std::vector<int>& v);
//int check_repeat(const std::vector<int>& v);
std::vector<int> pool_generator(int length, int num, int count);
int pow(int a, int b);
void give_feedback_trial(const std::vector<int>& attempt,const std::vector<int>& trial, int num, int& black_hits, int& white_hits);
int number_of_num(const std::vector<int>& v, int num);
int min(int n1, int n2);
//improved algorithm which eliminates a number from the number vector when the number is confirmed




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

    std::vector<int> sequence;


    int length;
    int num;


};



struct mm_solver{

    void init(int i_length, int i_num){
        length = i_length;
        num = i_num;

        if((length > 7) && (num > 7)){
          for(int i = 0; i < length; i++){
            test_attempt.push_back(0);
          }

        }
        else{
          for(int i = 0; i < pow(num, length); i++){
            pool.push_back(pool_generator(length, num, i));
          }
        }

    }


    void create_attempt(std::vector<int>& attempt){
        /// write your implementation here

        if((length > 7) && (num > 7)){//higher situation

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

        }



        else{attempt = pool[randn(pool.size())];}
    }

    void learn(std::vector<int>& attempt, int black_hits, int white_hits){
        /// write your implementation here
        if((length > 7) && (num > 7)){//higher situation

          if(num_of_attempt < num){//testing phase
            for(int i = 0; i < black_hits; i++){
              number.push_back(num_of_attempt);
            }
          }
          else{
            if((black_hits == 0) && (!found_test_attempt)){
              test_attempt = attempt;
              found_test_attempt = true;
              black_tmp = black_hits;
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
    std::vector<int> test_attempt;
    std::vector<int> tested_num; //contains number already tested for blackhit, must be cleared for every check_index
    bool found_test_attempt = false;
    int check_index = 0; //contains the next index to be checked for blackhit
    int check_num = 0;

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









/// add here the implementation for any other functions you wish to define and use
