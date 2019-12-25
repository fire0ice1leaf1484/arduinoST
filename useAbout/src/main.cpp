#include <Arduino.h>
#include"communication.h"
int count;
int monitoring;
int data[10] = {0};
void timerInterrupt(HardwareTimer *)
{
  monitoring++;
  count++;
}

void setup()
{
#if defined(TIM1)
  TIM_TypeDef *Instance = TIM1;
#else
  TIM_TypeDef *Instance = TIM2;
#endif

  // Instantiate HardwareTimer object. Thanks to 'new' instanciation, HardwareTimer is not destructed when setup() function is finished.
  HardwareTimer *MyTim = new HardwareTimer(Instance);

  // configure pin in output mode
  pinMode(3, OUTPUT);

  MyTim->setMode(2, TIMER_OUTPUT_COMPARE); // In our case, channekFalling is configured but not really used. Nevertheless it would be possible to attach a callback to channel compare match.
  MyTim->setOverflow(1000, HERTZ_FORMAT);  // 1000 Hz
  MyTim->attachInterrupt(timerInterrupt);
  MyTim->resume();
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop()
{
  Serial.println(count);
  delay(400);
}
void serial3Event(){
  static int No = 0;
    int buff;
    monitoring = 0;
    buff = Serial4.read();
    if (buff == 0x80)
    {
        No = 0;
        data[No++] = 0x80;
    }
    else if (No > 0)
    {
        data[No++] = buff;
        if (No > 8)
        {
            updataState(data);
            No = 0;
        }
    }

}