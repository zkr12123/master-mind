#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

int main(){
  set_random_seed();
  int length, num;
  std::cout << "enter length of sequence and number of possible values:" << std::endl;
  std::cin >> length >> num;

  mm_solver solver;
  solver.init(length, num);

  mm_code_maker maker;
  maker.init(length, num);
  maker.generate_sequence();

  int trial_limit = 100
  int trial = 0
  int total_attempts = 0;

  while(trial < trial_limit){
    int attempts = 0;
    int black_hits=0, white_hits=0;

    while(black_hits < length){
      std::vector<int> attempt;
      solver.create_attempt(attempt);
      maker.give_feedback(attempt, black_hits, white_hits);
      solver.learn(attempt, black_hits, white_hits);
      attempts++;
      total_attempts++;
    }
    std::cout << "this trial takes: " << attempts << " attempts" << std::endl;

  trial++;

}
std::cout << std::endl;

double average = total_attempts / trial_limit;
std::cout << "total attempts: " << total_attempts << std::endl;
std::cout << "average attempts each trial: " << average << std::endl;

return 0;


}
