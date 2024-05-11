#ifndef MY_UTILITY
#define MY_UTILITY

class MeasureArray // TODO is not good enough make it better
{
  private:
    const char m_array_size; // max 256 (but                not recommended to use more than 100)
    float *measurement;      // Pointer array, will be initialized              in constructor
    int m_memory_cursor = 0;
    float m_oldest_measure;

  public:
    MeasureArray(int size);
    void init(float initial_value);
    void add_measure(float value);
    float read_measure(char index);
    float get_average();
};

class TimerLowPriority
{
  private:
    unsigned long m_start_time;
    unsigned long m_end_time;

  public:
    TimerLowPriority();
    bool activate(int time_to_activate);
    void reset();
};

// TODO high priority timer

class DataHMS
{
  public:
    long m_offset;

  public:
    DataHMS(long hour, long minute, long second);
    String return_data();
};

#endif