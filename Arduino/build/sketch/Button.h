#ifndef Button_h
#define Button_h

class Button
{
    private:
        // variables
        byte _pin;
        byte _state;
        byte _lastReading;
        byte _newReading;
        unsigned long _lastDebounceTime = 0;
        unsigned long _debounceDelay = 50;

    public:
        // Constructor
        Button(byte pin);

        // functions
        void init(void);
        void update(void);
        byte getState(void);
        bool isPressed(void);
};

#endif