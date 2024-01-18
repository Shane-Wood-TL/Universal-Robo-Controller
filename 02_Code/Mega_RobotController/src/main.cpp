#include <Arduino.h>
#include <externValues.h>
#include <Wire.h>
#include <SPI.h>
#include <RF24.h>

#include <nRF24L01.h>
#include <LiquidCrystal_I2C.h>



PayloadStruct payload;
values InputValues;


//display
LiquidCrystal_I2C lcd(0x27,20,4);



//radio setup
RF24 radio(NRFCE, NRFCSN);
const byte slaveAddress[5] = {'R','x','A','A','A'};


//joystick inputs
float j1_X_angle, j1_Y_angle, j2_X_angle, j2_Y_angle;
float j1_X_angle_r = 0, j1_Y_angle_r = 0, j2_X_angle_r = 0, j2_Y_angle_r = 0;


//amount of states on the controller (must match robot)



int oldState = 0;
int state = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("alive");
  //set up display
  lcd.init();           
  lcd.backlight();
  lcd.clear();

  lcd.print("working");
  Serial.print("here2");
  //set all button/switches ;as input pullup (no resistor is used, buttons are tied to gnd)
  pinMode(swA0, INPUT_PULLUP);
  pinMode(swB0, INPUT_PULLUP);

  pinMode(swA1, INPUT_PULLUP);
  pinMode(swB1, INPUT_PULLUP);

  pinMode(swA2, INPUT_PULLUP);
  pinMode(swB2, INPUT_PULLUP);

  pinMode(swA3, INPUT_PULLUP);
  pinMode(swB3, INPUT_PULLUP);

  pinMode(swA4, INPUT_PULLUP);
  pinMode(swB4, INPUT_PULLUP);

  pinMode(bt0, INPUT_PULLUP);
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);

  

 


  radio.begin();
  // begin radio
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    lcd.print("no radio");
    while (1) {}  // hold in infinite loop
  }
  radio.setDataRate( RF24_250KBPS );
   radio.setRetries(3,5); // delay, count
   radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(slaveAddress);
   
   
   
   //radio.stopListening();

   //updateMenu(Cstate, payload);
   //payload.j1_x = 5;
}



void loop() {
  //radio.printPrettyDetails();
  //update all inputs
  // Serial.print(map(InputValues.L0V, 680,348,-80,80));
  // Serial.print("   ");
  // Serial.print(map(InputValues.L1V,344,678,-80,80));
  // Serial.print("   ");
  // Serial.print(map(InputValues.L2V,16,39,-10,10));
  // Serial.print("   ");
  // Serial.print(map(InputValues.R0V, 671,340,-80,80));
  // Serial.print("   ");
  // Serial.println(map(InputValues.R1V, 337,667,-80,80));

  
  updateAll(InputValues);
  Serial.print(payload.eStop);
  
  if(InputValues.swA0V != 1){
    if(payload.eStop != 1){
      payload.eStop = 1;
      updateMenu(state, payload);
    }
  }else{
    if(payload.eStop != 0){
      payload.eStop = 0;
      updateMenu(state, payload);
    }
  }


  if (state != oldState && InputValues.swA1V == 1){
    oldState = state;
    payload.state = oldState; 
           
  }
  

  if(InputValues.swB2V != 1){
      if(payload.gyro != 1 | payload.gyro != 1){
        payload.gyro = 1;
        payload.PID = 1;
        updateMenu(state, payload);
      }
  }else if(InputValues.swA2V != 1){
    if((payload.gyro != 1) | (payload.PID != 0)){
      payload.gyro = 1;
      payload.PID = 0;
      updateMenu(state, payload);
    }
  }else{
    if(payload.gyro != 0 | payload.PID != 0){
      payload.gyro = 0;
      payload.PID = 0;
      updateMenu(state, payload);
    }
  }
  if(InputValues.swA1V != 1){
    float menuJ = map(InputValues.L0V, 680,348,-80,80);
    int temp_state = state;
    //Serial.println(menuJ);
      if(menuJ >=75){
        state = decState(state);
        delay(100);
      }else if(menuJ <= -75){
        state = incState(state);
        delay(100);
      }
      if(temp_state!=state){
        updateMenu(state, payload);
      }
  }
 

  switch (payload.state)
  {
  case(User):
    j1_X_angle_r=map(InputValues.L0V, 680,348,-80,80);
    j1_Y_angle_r=map(InputValues.L1V, 0,1023,-80,80);
    j2_X_angle_r=map(InputValues.R0V, 0,1023,-50,50);
    j2_Y_angle_r=map(InputValues.R1V, 0,1023,-40,40);

    
    payload.j1_x = int(j1_X_angle_r);
    payload.j1_y = int(j1_Y_angle_r);
    payload.j2_x = int(j2_X_angle_r);
    payload.j2_y = int(j2_Y_angle_r);
    break;
  case IK_Mode:{
    j1_X_angle_r=map(InputValues.L0V, 680,348,0,150);
    j1_Y_angle_r=0;
    j2_X_angle_r=map(InputValues.R0V, 0,1023,-50,50);
    j2_Y_angle_r=map(InputValues.R1V, 0,1023,-40,40);

    payload.j1_x = int(j1_X_angle_r);
    payload.j1_y = int(j1_Y_angle_r);
    payload.j2_x = int(j2_X_angle_r);
    payload.j2_y = int(j2_Y_angle_r);
    break;
  }

  case(motorOffADJ):{
    break;
  }
  case stand:
  case(FWalk):
  case(FTurn):
  case(Set90s):
  default:{
    payload.j1_x = 0;
    payload.j1_y = 0;
    payload.j2_x = 0;
    payload.j2_y = 0;
    break;
  }
  }
  

  bool sent;
  sent = radio.write(&payload, sizeof(PayloadStruct));
}



