#ifndef ml
#define ml

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class dcm  {
  public:
    dcm(int e,int i1,int i2);
    void minit();
    void mspeed(int s);

  private:
    int e;
    int i1;
    int i2;
    int s;
};
#endif
