#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"


#include <hcsr04.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


//----Motor Pins----//

const byte led_gpio = 17; 
const byte led_gpio1 = 5; 

const byte back1 = 16; 
const byte back2 = 18; 


int speedSlow = 80;
int speedHigh = 100;
int speedMedium = 130;
int speedTurn = 200;

int speed =150 ;


// defines pins numbers
const int trigPinNew = 3;
const int echoPinNew = 19;
const int trigPin = 2;
const int echoPin =  4;

// defines variables
long duration;
int distance;
long duration2;
int distance2;

int distanceRight;
int distanceLeft;
int frontDistance;

void setup() {

  ledcAttachPin(led_gpio, 0); 
  ledcAttachPin(led_gpio1, 1); 
  ledcAttachPin(back1, 2); 
  ledcAttachPin(back2, 3); 
  
  ledcSetup(0, 4000, 8); 
  ledcSetup(1, 4000, 8); 
  ledcSetup(2, 4000, 8); 
  ledcSetup(3, 4000, 8); 
Serial.begin(9600);


  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
    

  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  
  pinMode(trigPinNew, OUTPUT); // Sets the trigPinNew as an Output
  pinMode(echoPinNew, INPUT); // Sets the echoPinNew as an Input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
void loop() {
 
Maze();

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  
  Serial.print("DistanceLeft: ");
  Serial.println(distance);
//------------------------------------
  
  digitalWrite(trigPinNew, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPinNew, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinNew, LOW);
  
  duration2 = pulseIn(echoPinNew, HIGH);
  
  distance2 = duration2 * 0.034 / 2;
  
  Serial.print("DistanceRight: ");
  Serial.println(distance2);

//---------------------------------------
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(100);
}
//------------------------------------
 void goForward(){
    ledcWrite(0, speed); 
    ledcWrite(1, speed); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
}

void goForwardSlow(){
    ledcWrite(0, speedSlow); 
    ledcWrite(1, speedSlow); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
    
}

void goForwardMedium(){
    ledcWrite(0, speedMedium); 
    ledcWrite(1, speedMedium); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
    
}

void goForwardHigh(){
    ledcWrite(0, speedHigh); 
    ledcWrite(1, speedHigh); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
    
}

void goBack(int speed){
    ledcWrite(0, 0); 
    ledcWrite(1, 0); 
    ledcWrite(2, speed); 
    ledcWrite(3, speed); 
}

void turnLeft(){
    ledcWrite(0, speedTurn); 
    ledcWrite(1, 0); 
    ledcWrite(2, 0); 
    ledcWrite(3, speedTurn); 
}

void turnRight(){
    ledcWrite(0, 0); 
    ledcWrite(1, speedTurn); 
    ledcWrite(2, speedTurn); 
    ledcWrite(3, 0); 
}

void stopMoving(){
    ledcWrite(0, 0); 
    ledcWrite(1, 0); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
}

int valueDistance()
{
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  return measure.RangeMilliMeter;
  }

  int getDistanceLeft()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  return distance;

  }

int getDistanceRight()
{
    // Clears the trigPin
  digitalWrite(trigPinNew, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinNew, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinNew, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPinNew, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  return distance2;
}

void CompareDistance () {                   
  if (distanceRight > distanceLeft) {       
     turnLeft();                          
    }
  else if (distanceLeft > distanceRight) {  
      turnRight ();                          
    }
  else {                                    
      goForward ();                        
    }
}


void ChangePath () 
{                             
  
  stopMoving();

  delay(500);
  
  distanceRight = getDistanceRight();

  delay(500);
  distanceLeft = getDistanceLeft();
  delay(500);
  CompareDistance ();
                             
}



//-------------Maze--------------//

void Maze()
{
  frontDistance = valueDistance();

  if (frontDistance < 180 ) 
  {                            
    goForwardSlow();
    ChangePath ();
    
  } 
     else if ((frontDistance >= 150) && (frontDistance < 180)) 
  { 
     goForwardMedium(); //130
  }
  else if ((frontDistance >= 180) && (frontDistance < 200)) 
  { 
    goForwardHigh(); //150
  }
  else 
  {                                          
    goForward(); //200
  }
}
