#include <Arduino.h>
#include <HCSR04.h>

//servo initialization
int freq = 50;
int channel = 8;   
int resolution = 8; 
const int ServoPin = 3;

int buttonPin =2;
int flag=0;

int calculatePWM(int degree)
{ //0-180度
 //20ms cycle，high level 0.5-2.5ms，corresponding to 0-180 degree
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
  ledcSetup(channel, freq, resolution); // set channel
  ledcAttachPin(ServoPin, channel);          // connect the channel to the SeverPin
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, CHANGE);  // connect the interrupt function to the buttonPin
}

void loop() 
{
  Serial.println(flag);
  if(flag==1)
  {
    ledcWrite(channel, calculatePWM(100));
    delay(3000);
    ledcWrite(channel, calculatePWM(0));
    flag=0;
  }
}

void buttonInterrupt() // button interrupt function
{
  if (digitalRead(buttonPin) == HIGH) 
  {
     flag=1;
  }
}
