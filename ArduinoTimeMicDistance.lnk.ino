#include <Servo.h>
//unsigned long time = micros();

float TimeMicA0;
float TimeMicA4;
float TimeMicA5;
float First;
float Second;

int MicА0 = A0;
int MicA0Val1 = 0;
int MicA0Val2 = 0;

int MicA4 = A4;
int MicA4Val1 = 0;
int MicA4Val2 = 0;

int MicA5 = A5;
int MicA5Val1=0;
int MicA5Val2=0;

boolean HitMicA0 = false;
boolean HitMicA4 = false;
boolean HitMicA5 = false;

Servo Servo1;

void setup() {
 // Servo1.attach(servoPin);
  pinMode(MicA0, INPUT);
  pinMode(MicA4, INPUT);
  pinMode(MicA5, INPUT);
  Serial.begin(9600);

}

void loop() {

  MicA0Val1 = analogRead(MicA0);
  MicA0Val2 = analogRead(MicA0);
  MicA4Val1 = analogRead(MicA4);
  MicA4Val2 = analogRead(MicA4);
  MicA5Val1 = analogRead(MicA5);
  MicA5Val2 = analogRead(MicA5);

  //Serial.println(MicA0Val1);
  //Serial.println(MicA4Val1);
  //Serial.println(MicA5Val1);
  
  Ready();
  
  //Serial.println("first was ");
  //Serial.println(First);


  //Serial.println(TimeMicA0);
  //Serial.println(TimeMicA4);

}

void Ready() {

  if (MicA0Val2 - MicA0Val1 > 20 && HitMicA0 == false ) {
    TakeTimeMic(MicA0);
    //Serial.print("mic1=");
    //Serial.println(TimeMicA0);
     //delay(10);
  }
  if (MicA4Val2 - MicA4Val1 > 20  && HitMicA4 == false ) {
	  
    TakeTimeMic(MicA4);
    //Serial.print("mic2=");
    //Serial.println(TimeMicA4);
   // delay(10);
 
  } 
  if (MicA5Val2 - MicA5Val1 > 20 && HitMicA5==false) {
    
    TakeTimeMic(MicA5);
    //Serial.print("mic2=");
    //Serial.println(TimeMicA4);
    //delay(10);
  }
  
  while (HitMicA0 == true && HitMicA4 == true && HitMicA5==true) {
    Compare();
	HitMicA0 = false;
	HitMicA4 = false;
	HitMicA5 = false;
	delay(1000);
	break;
  }
}

void Compare() {
  if (TimeMicA0 < TimeMicA4 && TimeMicA0 <TimeMicA5) {
    First = TimeMicA0;
    Serial.println("first was mic1");
    Servo1.write(0);
   //delay(1000);

  } 
  if (TimeMicA4 < TimeMicA0 && TimeMicA4 < TimeMicA5) {
    First = TimeMicA4;
    Serial.println("first was mic2");
    Servo1.write(180);
  // delay(1000);
  }
  if ( TimeMicA5< TimeMicA0 && TimeMicA5 < TimeMicA4) {
    First = TimeMicA5;
    Serial.println("first was mic3");
    Servo1.write(180);
  // delay(1000);
  }

  Servo1.write(90);
  TimeMicA0=0;
  TimeMicA4=0;
  TimeMicA5=0;

}

void TakeTimeMic(int mic){
	switch(mic){
		case MicA0:
			TimeMicA0 = micros();
			Serial.print("mic1=");
			Serial.println(TimeMicA0);
			HitMicA0 = true;
		break;
		case MicA4:
			TimeMicA4 = micros();
			Serial.print("mic2=");
			Serial.println(TimeMicA4);
			// Serial.print(TimeMicA4);
			HitMicA4 = true;
		break;
		case MicA5:
			TimeMicA5 = micros();
			Serial.print("mic3=");
			Serial.println(TimeMicA5);
			// Serial.print(TimeMicA4);
			HitMicA5 = true;
		break;
	}
}

/*
void TakeTimeMicA0() {
  TimeMicA0 = micros();
  Serial.print("mic1=");
  Serial.println(TimeMicA0);
  HitMicA0 = true;
  //return TimeMicA0;
}

void TakeTimeMicA4( ) {
  TimeMicA4 = micros();
  Serial.print("mic2=");
  Serial.println(TimeMicA4);
  // Serial.print(TimeMicA4);
   HitMicA4 = true;
}

void TakeTimeMicA5( ) {
  TimeMicA5 = micros();
  Serial.print("mic3=");
  Serial.println(TimeMicA5);
  // Serial.print(TimeMicA4);
   HitMicA5 = true;
}
*/

/*  Serial.println(MicA0Val1);
  Serial.print(" , ");
  Serial.println(MicA4Val1);
  // delay(10);
*/
//Serial.println(MicA0Val2);
//Servo1.write(90);
// delay(400);
/*   if (MicA4Val2-MicA4Val1>10 && HitMicA0 == false){


  Servo1.write(180);

  TimeMicA0=time;
  Serial.print(TimeMicA0);

  Serial.print(" , ");
  Serial.println("moved left, ");
  HitMicA0=true;



    }else if (MicA0Val2-MicA0Val1>10 && HitMicA4 == false){

  Servo1.write(0);
  time = micros();
  TimeMicA0=time;
  Serial.print(TimeMicA0);
  Serial.print(" , ");
  Serial.println("moved right, ");
  HitMicA4=true;


    }
  else {


     Servo1.write(90);

    }*/

