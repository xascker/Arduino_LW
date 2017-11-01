#include <OLED_I2C.h>

OLED  myOLED(A2, A3, 8);

extern uint8_t SmallFont[];

float y;
int x,z=0;

void setup()
{
  myOLED.begin();
  myOLED.setFont(SmallFont);
}

void loop()
{
 // myOLED.clrScr();
  myOLED.drawRect(0, 0, 127, 63);
  myOLED.drawLine(0, 31, 127, 31);
  myOLED.drawLine(63, 0, 63, 63);
//    for (int x=0; x<128; x++)
//    {
//      y=x*0.04974188368183839294232518690191;
//      //y = random(10,25);
//      //myOLED.invPixel(x, z, x+1, y);
//      myOLED.invPixel(x, (sin(y)*28)+31);
//      myOLED.update();
//     // z=y;
//      delay(10);
//    }
//
// delay(1000);

  y = map(random(235,300), 235, 300, 63, 8);
  //y = random(63, 8);
//  myOLED.drawLine(старт(х), высота-начало, длина, высота-конец);
  myOLED.drawLine(x, z, x+1, y);
  myOLED.update();
  z=y;
  x++;
  if(x>=123){
      x=0;
      myOLED.clrScr();
  }
  //delay(100);

}


