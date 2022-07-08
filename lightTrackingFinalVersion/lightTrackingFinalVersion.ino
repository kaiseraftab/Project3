
const byte led_gpio = 17; // the PWM pin the LED is attached to
const byte led_gpio1 = 5; // the PWM pin the LED is attached to

const byte back1 = 16; // the PWM pin the LED is attached to
const byte back2 = 18; // the PWM pin the LED is attached to

int speed = 170;

#define LIGHT_SENSOR_PIN 26  
#define LIGHT_SENSOR_PIN2 25
 
int value = 4095;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  ledcAttachPin(led_gpio, 0); // assign a led pins to a channel
  ledcAttachPin(led_gpio1, 1); // assign a led pins to a channel
  ledcAttachPin(back1, 2); // assign a led pins to a channel
  ledcAttachPin(back2, 3); // assign a led pins to a channel

  
  ledcSetup(0, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(1, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(3, 4000, 8); // 12 kHz PWM, 8-bit resolution

  
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  int analogValue222 = analogRead(LIGHT_SENSOR_PIN2);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  Serial.print("Analog Value222 = ");
  Serial.print(analogValue222);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue == value && analogValue222 == value) {
    
    Serial.println("Forward");
    goBack();
  } else if (analogValue222 == value ) {
    Serial.println("Left");
    turnLeft();
  } else if (analogValue == value ) {
    Serial.println("Right");
    turnRight();
  } else if (analogValue < value && analogValue222 < value) {
    
    Serial.println("Stop");
    stop();
  } 
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
    ledcWrite(0, speed); 
    ledcWrite(1, 0); 
    ledcWrite(2, 0); 
    ledcWrite(3, speed); 
}

void turnRight(){
    ledcWrite(0, 0); 
    ledcWrite(1, speed); 
    ledcWrite(2, speed); 
    ledcWrite(3, 0); 
}

void stop(){
    ledcWrite(0, 0); 
    ledcWrite(1, 0); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
}
