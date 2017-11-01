#include <Wire.h>
#include <BMP085.h>
#include <OLED_I2C.h>

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

BMP085 bmp;

OLED  myOLED(A2, A3, 8); //SDA pin -> Analog 2; SCL pin -> Analog 3

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
  
void setup() {
  Serial.begin(9600);
  bmp.begin();  
  myOLED.begin();
}
  
void loop() {
    myOLED.clrScr();
    myOLED.setFont(SmallFont);
    myOLED.print("Temp ->", LEFT, 4);
    myOLED.setFont(MediumNumbers);
    myOLED.printNumF(bmp.readTemperature(),1, RIGHT, 0);
    
    myOLED.setFont(SmallFont);
    myOLED.print("Pressure:", LEFT, 18);
    myOLED.print(" mm. rt. ->", LEFT, 28);
    myOLED.print(" hPa     ->", LEFT, 38);
    myOLED.printNumF(bmp.readPressure()/133.3224,2, RIGHT, 28);
    myOLED.printNumF(bmp.readPressure()*0.01,2, RIGHT, 38);
    myOLED.setFont(MediumNumbers);
    myOLED.printNumF(bmp.readPressure()*0.01,1, CENTER, 48);
    
    myOLED.update();
    
    //Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature(),1);
    //Serial.println(" *C");
   
    //Serial.print("Pressure = ");
    //Serial.print(bmp.readPressure()/133.3224);
    //Serial.println(" mm. rt.");
    Serial.print("  ");
    Serial.print(bmp.readPressure()*0.01,1);

    Serial.println();
    delay(5000);
}
