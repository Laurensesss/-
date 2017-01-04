//
//  HugeNumber.cpp
//  大整数的代数运算
//
//  Created by 石韬 on 17/1/3.
//  Copyright © 2017年 石韬. All rights reserved.
//

#include "HugeNumber.hpp"

int HugeNumber::flag = 0;


// MARK: - Private Functions
void HugeNumber::setLength() {
  
}

int HugeNumber::convertStringIntoInt(string str, int index) {
  
  int num;
  stringstream ss;
  
  ss << str[index];
  ss >> num;
  
  if (ss.good()) {
    cout << "Convertint String Into Integer Failed." << endl;
  }
  
  return num;
}

// MARK: - Public Functions

HugeNumber::HugeNumber(bool isUserInput) {
  if (isUserInput) {
    inputNumber();
  }
}

void HugeNumber::inputNumber() {
  string str;
  cin >> str;
  
  unsigned long int strLen = str.length();
  if (str[0] == '-') {
    strLen -= 1;
  }
  
  if (strLen > Max) {
    throw "String input is too long!";
  }
  
  for (int i = 0; i < strLen; i++) {
    if (str[0] == '-') {
      num[strLen-i-1] = convertStringIntoInt(str, i+1);
    } else {
      num[strLen-i-1] = convertStringIntoInt(str, i);
    }
    length++;
  }
  
  if (str[0] == '-') {
    num[length-1] = -num[length-1];
  }
  
}

void HugeNumber::printNumber() {
  for (int i = 0; i < length; i++) {
    cout << num[length-i-1];
  }
  cout << endl;
}

int HugeNumber::getLength() {
  return length;
}

// MARK: - Operations Override

HugeNumber HugeNumber::operator+(HugeNumber B) {
  // FIXME: - 减法问题
//  
//  // + +
//  if (num[length-1] > 0 && B.num[B.length-1] > 0) {
//    
//  }
//  
//  // + -
//  if (num[length-1] > 0 && B.num[B.length-1] < 0) {
//    for (int i = 0; i<B.length-1; i++) {
//      B.num[i] = -B.num[i];
//    }
//  }
//  
//  // - +
//  if (num[length-1] < 0 && B.num[B.length-1] > 0) {
//    for (int i = 0; i<length-1; i++) {
//      num[i] = -num[i];
//    }
//  }
//  
//  // - -
//  if (num[length-1] < 0 && B.num[B.length-1] < 0) {
//    num[length-1] = -num[length-1];
//    B.num[B.length-1] = -B.num[B.length-1];
//    // FIXME: - 修改正负性需变回
//  }
//  
//  if (B.length > length || (B.length == length &&
//                            abs(B.num[B.length-1]) > abs(num[length-1])
//                            )) {
//    for (int i = 0; i<length; i++) {
//      num[i] = -num[i];
//    }
//    for (int j = 0; j<B.length; j++) {
//      B.num[j] = -B.num[j];
//    }
//    HugeNumber temp(false);
//    
//    temp = B;
//    B = *this;
//    *this = temp;
//  }
//  
  // 减法设置结束
  
  
  
  /**
   1、无负数，正常加法；
   2、如果两个数之中有一个为负数，且是较大的那个数，那么交换两个数的正负值，在运算结束之后再改变正负号；
   3、如果两个数都是负数，则把两个数都变成正数，在运算结束之后改变正负号；
   4、一旦为负数，必须将每一位的数都变成负数。
   */
  
  // 1省略，2、有一个为负数，且较大
  // 先假设为第二个操作数
  if (num[length-1] > 0 && B.num[B.length-1] < 0) {
    if ( (B.length == length
         && -B.num[B.length-1] > num[length-1] )
         || B.length > length) {
      B.num[B.length-1] = -B.num[B.length-1];
      num[length-1] = -num[length-1];
    }
  }
  
  // 再假设为第一个操作数
  if (num[length-1] < 0 && B.num[B.length-1] > 0) {
    if ( (B.length == length
          && B.num[B.length-1] < -num[length-1] )
        || B.length < length) {
      B.num[B.length-1] = -B.num[B.length-1];
      num[length-1] = -num[length-1];
    }
  }
  
  // 3、两个负数
  if (num[length-1] < 0 && B.num[B.length-1] < 0) {
    B.num[B.length-1] = -B.num[B.length-1];
    num[length-1] = -num[length-1];
  }
  
  // 4、把每一位都变成负数
  if (num[length-1] < 0) {
    for (int i = 0; i < length-1; i++) {
      num[i] = -num[i];
    }
  }
  
  if (B.num[B.length-1] < 0) {
    for (int i = 0; i < B.length-1; i++) {
      B.num[i] = -B.num[i];
    }
  }
  
  
  int i = 0;
  HugeNumber C(false);
  int n = this->length, m = B.length;
  
  for ( ; i<n && i<m; i++) {
    C.num[i] = (this->num[i] + B.num[i] + flag) % 10;
    flag = (this->num[i] + B.num[i] + flag) / 10;
    
  }
  
  for ( ; i<n; i++) {
    C.num[i] = (this->num[i] + flag) % 10;
    flag = (this->num[i] + flag) / 10;
  }
  
  for ( ; i<m; i++) {
    C.num[i] = (B.num[i] + flag) % 10;
    flag = (B.num[i] + flag) / 10;
  }
  
  C.length = max(m, n) + flag;
  if (C.length <= Max) {
    if (flag == 1) {
      C.num[C.length-1] = 1;
    }
  } else {
    cout << "Pass the top of 100-digit integer, the past part has been cut." << endl;
    C.length = Max;
  }
  
  return C;
}

HugeNumber HugeNumber::operator-(HugeNumber B) {
  
  B.num[B.length-1] = -B.num[B.length-1];
  
  return *this + B;
}













