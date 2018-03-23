#include <Servo.h>
unsigned long time = micros();

float TimeMic1;
float TimeMic2;
float TimeMic3;
float First;
float Second;

int MicPin = A0;
int MicValue1 = 0;
int MicValue2 = 0;

boolean Hit1=false;
boolean Hit2=false;
boolean Hit3=false;


int MicPin1 = A4;
int MicVal1 = 0;
int MicVal2 = 0;

int MicPin2 = A5;
int MicPin2Val1=0;
int MicPin2Val2=0;


Servo Servo1;


void setup() {


 // Servo1.attach(servoPin);
  pinMode(MicPin, INPUT);
  pinMode(MicPin1, INPUT);
  pinMode(MicPin2, INPUT);
  Serial.begin(9600);

}

void loop() {

  MicValue1 = analogRead(MicPin);
  MicValue2 = analogRead(MicPin);
  MicVal1 = analogRead(MicPin1);
  MicVal2 = analogRead(MicPin1);
  MicPin2Val1=analogRead(MicPin2);
  MicPin2Val2=analogRead(MicPin2);

  //Serial.println(MicValue1);
  //Serial.println(MicVal1);
  //Serial.println(MicPin2Val1);
  
  Ready();


  //Serial.println("first was ");
  //Serial.println(First);


  //Serial.println(TimeMic1);
  //Serial.println(TimeMic2);

}

void Ready() {

  if (MicValue2 - MicValue1 > 20 && Hit1 == false ) {
    TakeTimeMic1();
    //Serial.print("mic1=");
    //Serial.println(TimeMic1);
     //delay(10);
  }
  if (MicVal2 - MicVal1 > 20  && Hit2 == false ) {
    
    TakeTimeMic2();
    //Serial.print("mic2=");
    //Serial.println(TimeMic2);
   // delay(10);
 
  } 
  if (MicPin2Val2 - MicPin2Val1 > 20 && Hit3==false) {
    
    TakeTimeMic3();
    //Serial.print("mic2=");
    //Serial.println(TimeMic2);
    //delay(10);
  }
  while (Hit1 == true && Hit2 == true && Hit3==true) {
    Compare();
  Hit1 = false;
  Hit2 = false;
  Hit3 = false;
  delay(1000);
  break;
    }
  

}

void Compare() {
  if (TimeMic1 < TimeMic2 && TimeMic1 <TimeMic3) {
    TimeMic1 = First;
    Serial.println("first was mic1");
    Servo1.write(0);
   //delay(1000);

  } 
  if (TimeMic2 < TimeMic1 && TimeMic2 < TimeMic3) {
    TimeMic2 = First;
    Serial.println("first was mic2");
    Servo1.write(180);
  // delay(1000);
  }
  if ( TimeMic3< TimeMic1 && TimeMic3 < TimeMic2) {
    TimeMic3 = First;
    Serial.println("first was mic3");
    Servo1.write(180);
  // delay(1000);
  }

  Servo1.write(90);
  TimeMic1=0;
  
  TimeMic2=0;
  TimeMic3=0;

}


void TakeTimeMic1() {
  unsigned long time = micros();
  TimeMic1 = time;
  Serial.print("mic1=");
  Serial.println(TimeMic1);

  Hit1 = true;
  //return TimeMic1;
}

void TakeTimeMic2( ) {
  unsigned long time = micros();
  TimeMic2 = time;
  Serial.print("mic2=");
  Serial.println(TimeMic2);

  // Serial.print(TimeMic2);

   Hit2 = true;

}

void TakeTimeMic3( ) {
  unsigned long time = micros();
  TimeMic3 = time;
  Serial.print("mic3=");
  Serial.println(TimeMic3);

  // Serial.print(TimeMic2);

   Hit3 = true;

}

/*  Serial.println(MicValue1);
  Serial.print(" , ");
  Serial.println(MicVal1);
  // delay(10);
*/
//Serial.println(MicValue2);
//Servo1.write(90);
// delay(400);
/*   if (MicVal2-MicVal1>10 && Hit1 == false){


  Servo1.write(180);

  TimeMic1=time;
  Serial.print(TimeMic1);

  Serial.print(" , ");
  Serial.println("moved left, ");
  Hit1=true;



    }else if (MicValue2-MicValue1>10 && Hit2 == false){

  Servo1.write(0);
  time = micros();
  TimeMic1=time;
  Serial.print(TimeMic1);
  Serial.print(" , ");
  Serial.println("moved right, ");
  Hit2=true;


    }
  else {


     Servo1.write(90);

    }*/

