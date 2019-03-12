#include <iostream>
#include <vector>

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

  bool check_contain_vector(const std::vector<int>& v1, const std::vector<std::vector<int>>& v2){ //check if v2 contains v1
    for(int i = 0; i < v2.size(); i++){
      if(v1 == v2[i]){
        return true;
      }
    }
    return false;

  }
