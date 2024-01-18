#include <Arduino.h>
#include <externValues.h>
#include <LiquidCrystal_I2C.h>


int motorAdjust = 0;
int motorAdjustVal = 0;

extern LiquidCrystal_I2C lcd;

int incState(int state){
  state++;
  if (state >= maxStates){
    state = 0;
  }
  return state;
}

int decState(int state){
  state--;
  if (state < 0){
    state = maxStates-1;
  }
  return state;
}

void updateMenu(int state, PayloadStruct payload){
  lcd.clear();
  if(payload.gyro == true){
    lcd.setCursor(10,1);
    lcd.print("gyro");
  }
  if(payload.PID == true){
    lcd.setCursor(15,1);
    lcd.print("P");
  }

  if(payload.eStop == true){
    lcd.setCursor(1,1);
      lcd.print("STOP");
  }else{
      lcd.setCursor(1,1);
      lcd.print("   ");
  }
  lcd.setCursor(0,0);
  lcd.print("Control: ");
  switch (state)
  {
  case 0:{
    lcd.print("Stand");
    break;
  }
  case 1:{
     lcd.print("IK mode");
     break;
  }
  case 2:{
    lcd.print("FWalk");
    break;
  }
  case 3:{
    lcd.print("Fturn");
    break;
  }
  case 4:{
    lcd.print("User");
    break;
  }case 5:{
    lcd.print("90s");
    break;
  }case 6:{
    lcd.print("OAdjust " + String(motorAdjust) + " " + String(motorAdjustVal));
    break;
  }
  default:{
    break;
  }
  } 
}


