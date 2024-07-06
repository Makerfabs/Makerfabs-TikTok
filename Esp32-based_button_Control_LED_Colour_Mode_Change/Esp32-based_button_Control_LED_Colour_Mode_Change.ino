#include <FastLED.h>

#define NUM_LEDS 12
#define LED_PIN 3
CRGB leds[NUM_LEDS];

int buttonPin = 2;

int flag=0,b=0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
  
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, CHANGE);  // Associate the interrupt function with the button pin
  
  Serial.begin(115200);
}


void led_RED_on()
{
  delay(500);
  for(int i=0;i<12;i++)
  {
    leds[i] = CRGB::Green;
    FastLED.show();
  }
}

void led_Blue_on()
{
  delay(500);
  for(int i=0;i<12;i++)
  {
    leds[i] = CRGB::Blue;
    FastLED.show();
  }
}

void led_Yello_on()
{
  delay(500);
  for(int i=0;i<12;i++)
  {
    leds[i] = CRGB::Yellow;
    FastLED.show();
  }
}

void led_Green_on()
{
  delay(500);
  for(int i=0;i<12;i++)
  {
    leds[i] = CRGB::Red;
    FastLED.show();
  }
}
void led_off()
{
  delay(500);
  for(int i=0;i<12;i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}
void led_glint()
{
  led_RED_on();
  delay(500);
  led_off();
  delay(500);
}

void led_run()
{
  led_off();
  for(int i=0;i<12;i++)
  {
     leds[i] = CRGB::Green;
     FastLED.show();
     delay(200);
  }
}

void led_gap()
{
  led_off();
  for(int i=0;i<12;i=i+2)
  {
      leds[i] = CRGB::Green;
      FastLED.show();
  }
  delay(500);
  led_off();
  for(int i=1;i<11;i=i+2)
  {
      leds[i] = CRGB::Green;
      FastLED.show();
  }
  delay(500);
}

void led_dis(int a)
{
    if(a==1){led_Green_on();}
    else if(a==2){led_Yello_on();}
    else if(a==3){led_Blue_on();}
    else if(a==4){led_RED_on();}
    else if(a==5){led_glint();}
    else if(a==6){led_run();}
    else if(a==7){led_gap();}
    else {led_off();}
}

void loop() 
{
  if (digitalRead(buttonPin) == LOW && b==1)
  { 
    b=0;  
    Serial.println("Button pressed");
    flag=flag+1;
    if(flag==8){flag=0;}
  }
  Serial.print("flag=");
  Serial.println(flag);
  Serial.print("b=");
  Serial.println(b);
  led_dis(flag);
  
}

void buttonInterrupt() //button interrupt function
{
  if (digitalRead(buttonPin) == HIGH) {b=1;}
}
