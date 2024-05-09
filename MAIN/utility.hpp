#ifndef MY_UTILITY
#define MY_UTILITY




class MeasureArray  //TODO is not good enough make it better
{
  private:
  const char array_size; //max 256 (but not recommended to use more than 100)
  float* measurement; // Pointer array, will be initialized in constructor  
  int memory_cursor = 0;

  char are_full = 0;
  float oldest_measure;


  public:
  MeasureArray(int size);
  void add_measure(float value);
  float read_measure(char index);
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


//TODO high priority timer




#endif