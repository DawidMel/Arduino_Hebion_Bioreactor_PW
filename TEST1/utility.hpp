#ifndef MY_UTILITY
#define MY_UTILITY




class mesure_arr  //DOPRACOWAĆ
{
  private:
  const char array_size; //max 256 ale wtedy może nie starczyć pamięci
  float* mesurment; // Tablica wskaźników, zostanie zainicjowana w konstruktorze
  int memory_cursor = 0;
  char arey_full = 0;

  public:

  mesure_arr(int size);
  void add_mesure(float value);
  float read_mesure(char index);
  float get_average();
};








#endif