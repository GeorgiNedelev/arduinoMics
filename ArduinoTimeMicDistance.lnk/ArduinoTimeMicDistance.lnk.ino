#include <Servo.h>
#include <DHT.h>


#define DHTPIN 3
#define DHTTYPE DHT11 



// global variables

float hum;// humidity var
float temp; //temperature var

unsigned long time = micros(); // taking time of the profram started in microseconds

float SoundSpeed= 331.4+(0.606*temp)+(0.0124*hum);// equation for the speed of sound 
float SoundSpeedCm = SoundSpeed/10000; // convert to centimeters per microsecond 
int iterations=5;

// variables to store the time whenever the mic is activated
float TimeMic1;
float TimeMic2;
float TimeMic3;

// variables of which microphone was first/second/third
float First;
float Second;
float Third;

//bools to take time only when the mics are hit // or the sensor
boolean Hit1=false;
boolean Hit2=false;
boolean Hit3=false;
bool Sensor = false;

//  variables for all 3 mics + analog input attach
int MicPin = A0;            
int MicValue1 = 0;
int MicValue2 = 0;

int MicPin1 = A4;
int MicVal1 = 0;
int MicVal2 = 0;

int MicPin2 = A5;
int MicPin2Val1=0;
int MicPin2Val2=0;

// declearing a sevo and sensor from theyr classes
Servo Servo1;
DHT dht(DHTPIN, DHTTYPE);// declearing sensor

void setup() {


 // Servo1.attach(servoPin);
  pinMode(MicPin, INPUT); //attaching the imput to the analog IN on the arduinos
  pinMode(MicPin1, INPUT);
  pinMode(MicPin2, INPUT);
  Serial.begin(9600);
  dht.begin();//sensor

}

void loop() {

  MicValue1 = analogRead(MicPin); //  assigning the variables to be red form the different microphones
  MicValue2 = analogRead(MicPin);
  MicVal1 = analogRead(MicPin1);
  MicVal2 = analogRead(MicPin1);
  MicPin2Val1=analogRead(MicPin2);
  MicPin2Val2=analogRead(MicPin2);


TempHumSensor(); // sensor function


  //Serial.println(MicValue1);
  //Serial.println(MicVal1);
  //Serial.println(MicPin2Val1);
  
  Ready();


  //Serial.println("first was ");
  //Serial.println(First);


  //Serial.println(TimeMic1);
  //Serial.println(TimeMic2);

}
void TempHumSensor(){ // function of the sensor 
  if (Sensor==false){ // just an if statement to execute the code only once 
  delay(2000);
  hum = dht.readHumidity(); // attaching value to hum variable thru reading humidity from the sensor
temp = dht.readTemperature(); // attaching value to temp variable thru reading temperature from the sensor 


SoundSpeed= 331.4+(0.606*temp)+(0.0124*hum);// equation for the speed of sound 
SoundSpeedCm = SoundSpeed/10000; // calculating speed of sound in milisec
  

Serial.print("Humidity: ");
Serial.print(hum);
Serial.print("Temperature: ");
Serial.print(temp);
Serial.println("Celsius");
Serial.print("speed of sound = ");
Serial.print(SoundSpeedCm);
  Serial.println(" centimeters per milisecond ");
  Sensor=true; // bool to true to execute once
  }
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
    First = TimeMic1;
    Serial.println("first was mic1");
    Servo1.write(0);
   //delay(1000);

  } 
  if (TimeMic2 < TimeMic1 && TimeMic2 < TimeMic3) {
    First = TimeMic2;
    Serial.println("first was mic2");
    Servo1.write(180);
  // delay(1000);
  }
  if ( TimeMic3< TimeMic1 && TimeMic3 < TimeMic2) {
    First = TimeMic3;
    Serial.println("first was mic3");
    Servo1.write(180);
  // delay(1000);
  }

  Servo1.write(90);
  TimeMic1=0;
  TimeMic2=0;
  TimeMic3=0;

}


void TakeTimeMic1() { // taking the time mike 1 is hit
  unsigned long time = micros();
  TimeMic1 = time;
  Serial.print("mic1=");
  Serial.println(TimeMic1);

  Hit1 = true;
  //return TimeMic1;
}

void TakeTimeMic2( ) {//taking the time mic 2 was hit
  unsigned long time = micros();
  TimeMic2 = time;
  Serial.print("mic2=");
  Serial.println(TimeMic2);

  // Serial.print(TimeMic2);

   Hit2 = true;

}

void TakeTimeMic3( ) {// taking the time mic 3 was hit 
  unsigned long time = micros();
  TimeMic3 = time;
  Serial.print("mic3=");
  Serial.println(TimeMic3);

  // Serial.print(TimeMic2);

   Hit3 = true;

}


