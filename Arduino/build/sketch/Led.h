#ifndef Led_h
#define Led_h

class Led
{
  public:
    // Constructor
    Led(byte pin);

    // Functions
    void on();
    void off();

  private:
    // variables
    byte _pin;
};

#endif