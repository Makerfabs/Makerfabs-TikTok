#include <hcsr04.h>
#include <FastLED.h>
#include "SSD1306Wire.h"  

//hc-sr04 pin initialization
#define TRIG_PIN 12
#define ECHO_PIN 13
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

//led pin initialization
#define NUM_LEDS 12//LED数量
#define LED_PIN 3//定义io口
CRGB leds[NUM_LEDS];//定义led数组

//ssd1306 pin initialization
SSD1306Wire display(0x3c, 4, 5);//SDA-->4;SCL-->5

void setup() 
{
  display.init(); // OLED initialization
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16); // set font size
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS); // ssd1306 initialization
}

void led(int a) // led color
{
    for(int i=0;i<12;i++)
    {
      if(a==1){leds[i] = CRGB::Green;}
      else if(a==2){leds[i] = CRGB::Yellow;}
      else if(a==3){leds[i] = CRGB::Red;}
      FastLED.show();
      delay(100);
    }
}

void ssd_1306()// change color with distance
{
  if(hcsr04.distanceInMillimeters()<70) //2-7CM
  {
    led(1);
  }
  else if(hcsr04.distanceInMillimeters()>=120) //12-17CM
  {
    led(3);
  }
  else //7-12CM
  {
    led(2);
  }
}

void loop() 
{
  ssd_1306();
  display.clear();
  display.drawString(0, 20, "distance:");
  display.drawString(0, 40,String(hcsr04.distanceInMillimeters()));
  display.display();
  delay(250);  
}
