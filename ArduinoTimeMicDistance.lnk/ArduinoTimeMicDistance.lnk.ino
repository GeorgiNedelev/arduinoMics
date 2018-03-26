#include <Servo.h>
#include <DHT.h>

#define DHTPIN 3
#define DHTTYPE DHT11 

// global variables
float hum;  // humidity var
float temp; //temperature var

float SoundSpeed;
float SoundSpeedCm;
//int iterations = 5;

// variables to store the time whenever the mic is activated
float TimeMicA0;
float TimeMicA4;
float TimeMicA5;

// variables of which microphone was first/second/third
float First;
float Second;
float Third;

//unsigned long time = micros(); // taking time of the program started in microseconds

//bools to take time only when the mics are hit // or the sensor
boolean HitMicA0 = false;
boolean HitMicA4 = false;
boolean HitMicA5 = false;
bool Sensor = false;

//  variables for all 3 mics + analog input attach
int MicA0 = A0;
int MicA0Val1 = 0;
int MicA0Val2 = 0;

int MicA4 = A4;
int MicA4Val1 = 0;
int MicA4Val2 = 0;

int MicA5 = A5;
int MicA5Val1=0;
int MicA5Val2=0;

// declearing a sevo and sensor from their classes
Servo Servo1;
DHT dht(DHTPIN, DHTTYPE);// declearing sensor

void setup() {
 // Servo1.attach(servoPin);
 
  //attaching the imput to the analog IN on the arduinos
  pinMode(MicA0, INPUT);
  pinMode(MicA4, INPUT);
  pinMode(MicA5, INPUT);
  Serial.begin(9600);
  dht.begin();//sensor

}

void loop() {
  //  assigning the variables to be red form the different microphones
  
  MicA0Val1 = analogRead(MicA0);
  MicA0Val2 = analogRead(MicA0);
  MicA4Val1 = analogRead(MicA4);
  MicA4Val2 = analogRead(MicA4);
  MicA5Val1 = analogRead(MicA5);
  MicA5Val2 = analogRead(MicA5);

  TempHumSensor(); // sensor function

  Ready();

  //Serial.println(MicValue1);
  //Serial.println(MicVal1);
  //Serial.println(MicPin2Val1);
  
  


  //Serial.println("first was ");
  //Serial.println(First);


  //Serial.println(TimeMic1);
  //Serial.println(TimeMic2);

}
void TempHumSensor(){// function of the sensor 
  if (Sensor==false){// just an if statement to execute the code only once 
    delay(2000);
    hum = dht.readHumidity(); // attaching value to hum variable thru reading humidity from the sensor
    temp = dht.readTemperature(); // attaching value to temp variable thru reading temperature from the sensor 

    SoundSpeed = 331.4+(0.606*temp)+(0.0124*hum);// equation for the speed of sound 
    SoundSpeedCm = SoundSpeed/10000; // calculating speed of sound in milisec
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" Temperature: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.print("speed of sound = ");
    Serial.print(SoundSpeedCm);
    Serial.println(" centimeters per milisecond ");
    Sensor=true; // bool to true to execute once
  }
}
void Ready() {
  if (MicA0Val2 - MicA0Val1 > 20 && HitMicA0 == false ) {
    TakeTimeMic(MicA0);
  }
  if (MicA4Val2 - MicA4Val1 > 20  && HitMicA4 == false ) {
    TakeTimeMic(MicA4);
  } 
  if (MicA5Val2 - MicA5Val1 > 20 && HitMicA5 == false) {
    TakeTimeMic(MicA5);
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
  } 
  if (TimeMicA4 < TimeMicA0 && TimeMicA4 < TimeMicA5) {
    First = TimeMicA4;
    Serial.println("first was mic2");
    Servo1.write(180);

  }
  if ( TimeMicA5< TimeMicA0 && TimeMicA5 < TimeMicA4) {
    First = TimeMicA5;
    Serial.println("first was mic3");
    Servo1.write(180);
  }

  Servo1.write(90);
  TimeMicA0=0;
  TimeMicA4=0;
  TimeMicA5=0;

}


/*void TakeTimeMic1() { // taking the time mike 1 is hit
  unsigned long time = micros();
  TimeMic1 = time;
  Serial.print("mic1=");
  Serial.println(TimeMic1);

  Hit1 = true;
  //return TimeMic1;
}*/

void TakeTimeMic(int mic){
  switch(mic){
    case A0:
      TimeMicA0 = micros();
      Serial.print("mic1=");
      Serial.println(TimeMicA0);
      HitMicA0 = true;
    break;
    case A4:
      TimeMicA4 = micros();
      Serial.print("mic2=");
      Serial.println(TimeMicA4);
      // Serial.print(TimeMicA4);
      HitMicA4 = true;
    break;
    case A5:
      TimeMicA5 = micros();
      Serial.print("mic3=");
      Serial.println(TimeMicA5);
      // Serial.print(TimeMicA4);
      HitMicA5 = true;
    break;
  }
}


