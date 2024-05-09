#ifndef MY_UTILITY
#define MY_UTILITY




class measure_arr  //DOPRACOWAĆ
{
  private:
  const char array_size; //max 256 ale wtedy może nie starczyć pamięci
  float* mesurment; // Tablica wskaźników, zostanie zainicjowana w konstruktorze
  int memory_cursor = 0;

  char are_full = 0;
  float oldest_mesure;


  public:
  measure_arr(int size);
  void add_measure(float value);
  float read_mesure(char index);
  float get_average();
  float get_average_fast();
};



class TimerLowPriority {
private:
    unsigned long start_time;
    unsigned long end_time;

public:
    TimerLowPriority();
    bool activate(int time_to_activate);
    void reset();
};


//TODO high piority timer




#endif