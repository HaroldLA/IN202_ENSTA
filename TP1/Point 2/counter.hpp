#ifndef counterHPP
#define counterHPP

class MyCounter
{
public:
    unsigned counter;
    unsigned max; 
    
    void increment() {
      counter ++;
      if(counter > max)
        counter = 0;
    }
 
    void reset() {
      counter = 0;
    }
};



#endif
