#include <iostream>
#include <cstdlib>

void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){
    std::vector<int> black;

    for(int i = 0; i < attempt.size(); i++){
      if(attmpt[i] == sequence[i]){
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
