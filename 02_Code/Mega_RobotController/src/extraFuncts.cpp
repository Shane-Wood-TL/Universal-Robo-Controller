#include <externValues.h>


void updateAll(values &Ivalues){
  Ivalues.L0V = analogRead(analogL0);
  Ivalues.L1V = analogRead(analogL1);
  Ivalues.L2V = analogRead(analogL2);
  
  Ivalues.R0V = analogRead(analogR0);
  Ivalues.R1V = analogRead(analogR1);
  Ivalues.R2V = analogRead(analogR2);

  
  Ivalues.swA0V = digitalRead(swA0);
  Ivalues.swB0V = digitalRead(swB0);

  Ivalues.swA1V = digitalRead(swA1);
  Ivalues.swB1V = digitalRead(swB1);

  Ivalues.swA2V = digitalRead(swA2);
  Ivalues.swB2V = digitalRead(swB2);

  Ivalues.swA3V = digitalRead(swA3);
  Ivalues.swB3V = digitalRead(swB3);

  Ivalues.swA4V = digitalRead(swA4);
  Ivalues.swB4V = digitalRead(swB4);

  Ivalues.bt0V = digitalRead(bt0);
  Ivalues.bt1V = digitalRead(bt1);
  Ivalues.bt2V = digitalRead(bt2);
  // Serial.print(Ivalues.swA0V);
  // Serial.print(Ivalues.swB0V);
  // Serial.print(Ivalues.swA1V);
  // Serial.print(Ivalues.swB1V);
  // Serial.print(Ivalues.swA2V);
  // Serial.print(Ivalues.swB2V);
  // Serial.print(Ivalues.swA3V);
  // Serial.print(Ivalues.swB3V);
  // Serial.print(Ivalues.swA4V);
  // Serial.print(Ivalues.swB4V);
  // Serial.print(Ivalues.bt0V);
  // Serial.print(Ivalues.bt1V);
  // Serial.println(Ivalues.bt2V);

}



// // float rationalizeJoystick(float value){
// //   ////874 max, 443 = mid, 0 min
// //   value = map(value,0,875,-150,150);
// //   return value;
// // }