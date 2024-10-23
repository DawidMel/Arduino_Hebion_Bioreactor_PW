//WORKING ONLY WITCH SPECIFIC CONDITION; NOT RECOMENDED TO USE IT

#include <Arduino.h>

#ifndef ARDUINO_OS
#define ARDUINO_OS

template <typename T>
class arduino_task {
private:

    const uint8_t m_priority;  
    const unsigned long m_repeat_time; 


    T* m_object;
    void (T::*m_task_method)();


    uint8_t m_state;            
    unsigned long m_last_call;  

public: 

    arduino_task(uint8_t priority, unsigned long repeat_time, T* object, void (T::*method)());
    void examine_task_state(unsigned long time);
    void run_task();
};

template <typename T>
arduino_task<T>::arduino_task(uint8_t priority, unsigned long repeat_time, T* object, void (T::*method)())
    : m_priority(priority), 
      m_repeat_time(repeat_time), 
      m_object(object), 
      m_task_method(method), 
      m_state(0),
      m_last_call(0)
{}

template <typename T>
void arduino_task<T>::examine_task_state(unsigned long time) {
    if (time >= m_last_call + m_repeat_time) {
        m_state = 1;
        m_last_call = time;
    } else {
        m_state = 0;
    }
}

template <typename T>
void arduino_task<T>::run_task() {

    if(m_state==1){(m_object->*m_task_method)();}
    m_state = 0;

}





#endif //ARDUINO_OS