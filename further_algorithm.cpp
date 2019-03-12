

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

          }
        }



        else{attempt = pool[randn(pool.size())];}
    }

    void learn(std::vector<int>& attempt, int black_hits, int white_hits){
        /// write your implementation here
        if(length > 7 && num > 7){
          if(num_of_attempt < length){
            number.push_back(black_hits);
          }
          else{}
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

  };
