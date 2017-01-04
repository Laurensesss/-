//
//  HugeNumber.hpp
//  大整数的代数运算
//
//  Created by 石韬 on 17/1/3.
//  Copyright © 2017年 石韬. All rights reserved.
//

#ifndef HugeNumber_hpp
#define HugeNumber_hpp

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int Max = 100;

class HugeNumber {
private:
  static int flag;
  int length = 0;
  int num[Max];
  void setLength();
  int convertStringIntoInt(string, int);
public:
  HugeNumber(bool);
  void inputNumber();
  void printNumber();
  int getLength();
  
  HugeNumber operator+(HugeNumber);
  HugeNumber operator-(HugeNumber);
  HugeNumber operator*(HugeNumber);
  HugeNumber operator/(HugeNumber);
};



#endif /* HugeNumber_hpp */
