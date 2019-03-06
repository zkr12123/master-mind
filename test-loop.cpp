#include <iostream>
#include <vector>

int main(){
  std::vector<int> attempt, sequence, black, white;

  for(int i = 0; i < 4; i++){
    int tmp;
    std::cin >> tmp;
    sequence.push_back(tmp);
  }
  std::cout << std::endl;

  while(true){
  for(int i = 0; i < 4; i++){
    int tmp;
    std::cin >> tmp;
    attempt.push_back(tmp);
  }


  for(int i = 0; i < attempt.size(); i++){
    if(attempt[i] == sequence[i]){
      //black_hits++;
      black.push_back(i);
    }
  }

  for(int i = 0; i < attempt.size(); i++){
    for(int j = 0; j < sequence.size(); j++){
      for(int k = 0; k < black.size(); k++){
        if((attempt[i] == sequence[j]) && (j != black[k])){ //probelm
          white.push_back(j); //contains repeated white_hits
        }
      }
    }
  }

  for(int i = 0; i < white.size(); i++){
    std::cout << white[i] << " ";
  }

  std::cout << std::endl;
  std::cout << std::endl;
}

  return 0;


}
