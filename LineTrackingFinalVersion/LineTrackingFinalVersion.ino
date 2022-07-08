

int rightSensor = 39; 
int leftSensor = 34; 

int speed = 110;
int speedTurn = 150;

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

  pinMode (leftSensor, INPUT); // leftSensor pin INPUT
  pinMode (rightSensor, INPUT); // RightSensor pin INPUT
Serial.begin(9600);
}
  void loop() {
    LineTracking();
    Serial.print(F("Right sensor= "));
  Serial.println(digitalRead(rightSensor));
  Serial.print(F("Left sensor= "));
  Serial.println(digitalRead(leftSensor));
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

void LineTracking()
{
if (digitalRead(leftSensor) == 0 && digitalRead(rightSensor) == 0 ) 
{
    goBack();
  }
  else if (digitalRead(leftSensor) == 0 && digitalRead(rightSensor) == 1 ) {
    //leftturn
    turnLeft();
  }
  else if (digitalRead(leftSensor) == 1 && digitalRead(rightSensor) == 0 ) {
    Serial.println("TR");
    //rightturn
    turnRight();
  }
  else if (digitalRead(leftSensor) == 1 && digitalRead(rightSensor) == 1 ) {
    //Stop
    stop();
  }
}


  
