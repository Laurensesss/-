//
//  main.cpp
//  大整数的代数运算
//
//  Created by 石韬 on 17/1/3.
//  Copyright © 2017年 石韬. All rights reserved.
//

#include <iostream>
#include "HugeNumber.hpp"

int main(int argc, const char * argv[]) {
  
  HugeNumber a(true);
  a.printNumber();
  cout << a.getLength() << endl;
  HugeNumber b(true);
  b.printNumber();
  cout << b.getLength() << endl;
  HugeNumber c(false);
  c = a + b;
  c.printNumber();
  cout << c.getLength() << endl;
  
  return 0;
}
