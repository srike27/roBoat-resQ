#ifndef tl
#define tl

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ultdist  {
  public:
    ultdist(int trig,int echo);
    void ultinit();
    long getdist();

  private:
    int trig;
    int echo;
};
#endif
