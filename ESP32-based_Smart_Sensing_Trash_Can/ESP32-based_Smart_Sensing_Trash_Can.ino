#include <Arduino.h>
#include <HCSR04.h>

//hc-sr04 pin initialization
byte triggerPin = 21;
byte echoPin = 22;
  
//servo initialization
int freq = 50;      
int channel = 8;    
int resolution = 8; 
const int ServoPin = 12;

int calculatePWM(int degree)
{ //0-180°
 //20ms cycle, high level 0.5-2.5ms, corresponding to 0-180 degree Angle
  const float deadZone = 6.4;//corresponding 0.5ms（0.5ms/(20ms/256）)
  const float max = 32;//corresponding 2.5ms
  if (degree < 0)
    degree = 0;
  if (degree > 180)
    degree = 180;
  return (int)(((max - deadZone) / 180) * degree + deadZone);
}

void setup() 
{
  Serial.begin(9600);
  // PWM initialization
  ledcSetup(channel, freq, resolution); // Set channel
  ledcAttachPin(ServoPin, channel);          // Connect the channel to the ServoPin
  ledcWrite(channel, calculatePWM(0)); // initial position
  HCSR04.begin(triggerPin, echoPin);
}


void loop() 
{
  double* distances = HCSR04.measureDistanceCm();
  if(distances[0]<6&&distances[0]>2)
  {
    ledcWrite(channel, calculatePWM(180));
    delay(4000);
    ledcWrite(channel, calculatePWM(0));
  }
  Serial.print("1: ");
  Serial.print(distances[0]);
  Serial.println(" cm");
  delay(250);
}
