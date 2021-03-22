#include<iostream>
#include "counter.hpp"
 
void testCounter()
{
  MyCounter counterA;
  counterA.counter = 0;
  counterA.max = 2;
 
  MyCounter counterB;
  counterB.counter = 0;
  counterB.max = 4;
 
  for(int i = 0; i < 4; i++)
  {
      std::cout << "compteur A: (" << counterA.counter << ", " << counterA.max << ")" << std::endl;
      std::cout << "compteur B: (" << counterB.counter << ", " << counterB.max << ")" << std::endl;
      counterA.increment();
      counterB.increment();
  }
}
 
int main(){
  testCounter();
  return 0;
}
