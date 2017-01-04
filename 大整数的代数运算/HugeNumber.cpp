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
  /**
   1、无负数，正常加法；
   2、如果两个数之中有一个为负数，且是较大的那个数，那么交换两个数的正负值，在运算结束之后再改变正负号；
   3、如果两个数都是负数，则把两个数都变成正数，在运算结束之后改变正负号；
   4、一旦为负数，必须将每一位的数都变成负数。
   */
  
  // 1省略，2、有一个为负数，且较大
  // 先假设为第二个操作数
  if (num[length-1] > 0 && B.num[B.length-1] < 0) {
    // 长度更高
    if (B.length > length) {
      B.num[B.length-1] = -B.num[B.length-1];
      num[length-1] = -num[length-1];
    }
    
    // 长度相等
    if (B.length == length) {
      
      if (-B.num[length-1] > num[length-1]) {
        B.num[B.length-1] = -B.num[B.length-1];
        num[length-1] = -num[length-1];
      } else if(-B.num[length-1] == num[length-1]) {
        for (int i = 0; i < length-1; i++) {
          
          if (B.num[length-i-1] < num[length-i-1]) {
            break;
          } else if(B.num[length-i-1] > num[length-i-1]) {
            B.num[B.length-1] = -B.num[B.length-1];
            num[length-1] = -num[length-1];
            break;
          } else {
            continue;
          }
          
        }
      }
      
    }
  }
  
  // 再假设为第一个操作数
  if (num[length-1] < 0 && B.num[B.length-1] > 0) {
    // 长度更高
    if (B.length < length) {
      B.num[B.length-1] = -B.num[B.length-1];
      num[length-1] = -num[length-1];
    }
    
    // 长度相等
    if (B.length == length) {
      
      if (B.num[length-1] < -num[length-1]) {
        B.num[B.length-1] = -B.num[B.length-1];
        num[length-1] = -num[length-1];
      } else if(B.num[length-1] == -num[length-1]) {
        for (int i = 0; i < length-1; i++) {
          
          if (B.num[length-i-1] > num[length-i-1]) {
            break;
          } else if(B.num[length-i-1] < num[length-i-1]) {
            B.num[B.length-1] = -B.num[B.length-1];
            num[length-1] = -num[length-1];
            break;
          } else {
            continue;
          }
          
        }
      }
      
    }
  }
  
  // 3、两个负数
  bool isTwoNegative = false;
  if (num[length-1] < 0 && B.num[B.length-1] < 0) {
    B.num[B.length-1] = -B.num[B.length-1];
    num[length-1] = -num[length-1];
    isTwoNegative = true;
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
  int n = length, m = B.length;
  
  for ( ; i<n && i<m; i++) {
    C.num[i] = (num[i] + B.num[i] + flag) > 0 ? (num[i] + B.num[i] + flag) % 10 : (num[i] + B.num[i] + flag + 10) % 10;
    flag = (num[i] + B.num[i] + flag) > 0 ? (num[i] + B.num[i] + flag) / 10 : -1;
  }
  
  for ( ; i<n; i++) {
    C.num[i] = (num[i] + flag) > 0 ? (num[i] + flag) % 10 : (num[i] + flag + 10) % 10;
    flag = (num[i] + flag) > 0 ? (num[i] + flag) / 10 : -1;
  }
  
  for ( ; i<m; i++) {
    C.num[i] = (B.num[i] + flag) > 0 ? (B.num[i] + flag) % 10 : (B.num[i] + flag + 10) % 10;
    flag = (B.num[i] + flag) > 0 ? (B.num[i] + flag) / 10 : -1;
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
  
  if (num[length-1] < 0 || B.num[B.length-1] < 0 || isTwoNegative) {
    C.num[C.length-1] = -C.num[C.length-1];
  }
  
  return C;
}

HugeNumber HugeNumber::operator-(HugeNumber B) {
  
  B.num[B.length-1] = -B.num[B.length-1];
  
  return *this + B;
}













