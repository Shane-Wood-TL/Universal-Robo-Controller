#include <Arduino.h>

#define swA0 28
#define swB0 29

#define swA1 26
#define swB1 27

#define swA2 30
#define swB2 31

#define swA3 24
#define swB3 25

#define swA4 22
#define swB4 23

#define bt0 34
#define bt1 33
#define bt2 32





#define AtState 0
#define maxStates 6

#define stand 0
#define IK_Mode 1
#define FWalk 2
#define FTurn 3
#define User 4
#define Set90s 5
#define motorOffADJ 6


struct values{
    int swA0V, swB0V, swA1V, swB1V, swA2V, swB2V, swA3V, swB3V, swA4V, swB4V, bt0V, bt1V, bt2V;
    float L0V, L1V, L2V, R0V, R1V, R2V;
};


//led matrix pins with resistor (gnd pins)
#define m0r 43
#define m1r 44
#define m2r 45
#define m3r 46
#define m4r 47
#define m5r 48
#define m6r 49
#define m7r 53

//led matrix pins without resistor (high pins)
#define m0 35
#define m1 36
#define m2 37
#define m3 38
#define m4 39
#define m5 40
#define m6 41
#define m7 42

//nrf 2401 CE and CSN pins 
#define NRFCE 7
#define NRFCSN 8

#define analogL0 A0
#define analogL1 A1
#define analogL2 A2

#define analogR0 A3
#define analogR1 A4
#define analogR2 A5



//the data sent with the radio
struct PayloadStruct {
  uint8_t eStop; //sw2
  uint8_t state;
  uint8_t gyro;
  uint8_t PID;
  int16_t j1_x;
  int16_t j1_y;
  int16_t j1_z;
  int16_t j2_x;
  int16_t j2_y;
  int16_t j2_z;
  uint8_t bt0_;
  uint8_t bt1_;
  uint8_t bt2_;
};


void updateAll(values &Ivalues);
// float rationalizeJoystick(float value);



int incState(int state);
int decState(int state);
void updateMenu(int state, PayloadStruct payload);