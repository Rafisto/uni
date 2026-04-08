class Ticker {
  private: 
    unsigned long period;
    unsigned long previousStart;
    void (*trigger)(void);
  public: 
    Ticker(unsigned long p, void(*fun)(void)) {
      period = p;
      trigger = fun;
      previousStart = 0;
    }
    void check() {
      unsigned long timeNow = millis();
      if(timeNow - previousStart > period) {
        (*trigger)();
        previousStart = timeNow;
      }
    }
};