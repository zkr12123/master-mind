

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
