

#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

 

int speed = 150;
int speedTurn = 160;

const byte led_gpio = 17; 
const byte led_gpio1 = 5; 
const byte back1 = 16; 
const byte back2 = 18; 

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

}
  void loop() {
    
  CurlingStop();
///----------------------//  
 
    

  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); 

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(100);

  
  }

void goForward(){
    ledcWrite(0, speed); 
    ledcWrite(1, speed); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
}

void goBack(){
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

void stop(){
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

void CurlingStop()
{
  int backDistance = valueDistance();
  
  if( backDistance < 300 )
  {
      goBack();
    }
  
  else
  {
    stop();
    Serial.println(" stop ");
   }
}



  
