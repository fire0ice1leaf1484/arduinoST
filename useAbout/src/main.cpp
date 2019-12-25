#include <Arduino.h>

int count;
void timerInterrupt(HardwareTimer *)
{ // Toggle pin. 10hz toogle --> 5Hz PWM
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
  MyTim->setOverflow(1000, HERTZ_FORMAT);  // 10 Hz
  MyTim->attachInterrupt(timerInterrupt);
  MyTim->resume();
  Serial.begin(9600);
}

void loop()
{
  /* Nothing to do all is done by hardware. Even no interrupt required. */
  Serial.println(count);
}