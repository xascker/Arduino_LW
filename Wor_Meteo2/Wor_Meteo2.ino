#include <Wire.h>
#include <BMP085.h>
#include <OLED_I2C.h>

#define PLOT_LEN      96 // 96 пикселей - длинна графика
#define STORAGE_TIME  205 // 205*delay(2000) = ~7,5 мин. период обновления одной точки г-ка.В итоге статистика за 12ч. (7.5мин*96пикс=720мин/60сек=12ч)

BMP085 bmp;
OLED  myOLED(A2, A3, 8); //SDA pin -> Analog 2; SCL pin -> Analog 3

extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];

struct {
  byte temp = 0;
//  byte hum = 0;
  byte pres = 0;
} infoArr[PLOT_LEN];

struct {
  float temp = 0;
//  float hum = 0;
  float pres = 0;
  int counter = 0;
} avrg;

//byte wait_cnt = 0;
//bool fastMode = true;

// Prototypes
void drawCol(int x, int y, int yn);

void setup() {
  myOLED.begin();
  bmp.begin();  
}

void loop() {
  bool metric = true;
//  float temp(NAN), hum(NAN), pres(NAN);
  float temp(NAN), hum(NAN), pres(NAN);
  uint8_t pressureUnit(0); // unit: B000 = Pa, B001 = hPa, B010 = Hg, B011 = atm, B100 = bar, B101 = torr, B110 = N/m^2, B111 = psi

  //bmp.read(pres, temp, hum, metric, pressureUnit);
  pres = bmp.readPressure();
  temp = bmp.readTemperature();
//    pres = random (95000,110000);
//    temp = random (15,35);
    
  // temp -= 0.3; // correct temp
  pres /= 133.3; // convert to mmHg

  avrg.temp += temp;
//  avrg.hum += hum;
  avrg.pres += pres;
  avrg.counter++;

//  if (fastMode && avrg.counter >= STORAGE_TIME) {
//    fastMode = false;
//    for (int i = 0; i < PLOT_LEN - 1; i++) {
//      infoArr[i].temp = 0;
////      infoArr[i].hum = 0;
//      infoArr[i].pres = 0;
//    }
//  }  

//  if (fastMode || avrg.counter >= STORAGE_TIME) {
    if (avrg.counter >= STORAGE_TIME) {
      temp = avrg.temp / avrg.counter;
//      hum = avrg.hum / avrg.counter;
      pres = avrg.pres / avrg.counter;
      avrg.temp = 0;
//      avrg.hum = 0;
      avrg.pres = 0;
      avrg.counter = 0;
//    }
    for (int i = 1; i < PLOT_LEN; i++) {
      infoArr[i - 1] = infoArr[i];
    }
    infoArr[PLOT_LEN - 1].temp = round(temp * 2) + 80;
    infoArr[PLOT_LEN - 1].pres = round(pres * 2) - 1380;
//    infoArr[PLOT_LEN - 1].hum = round(hum);
  }
//  delay(1000);

  /*
    Graph
  */

    myOLED.clrScr();

    byte minTemp = 255;
//    byte minHum = 255;
    byte minPres = 255;
    byte maxTemp = 0;
//    byte maxHum = 0;
    byte maxPres = 0;

    for (int i = PLOT_LEN - 1; i >= 0 ; i--) {
//      if (infoArr[i].temp == 0 && infoArr[i].hum == 0 && infoArr[i].pres == 0) break;
      if (infoArr[i].temp == 0 && infoArr[i].pres == 0) break;

      if (infoArr[i].temp < minTemp) minTemp = infoArr[i].temp;
//      if (infoArr[i].hum < minHum) minHum = infoArr[i].hum;
      if (infoArr[i].pres < minPres) minPres = infoArr[i].pres;

      if (infoArr[i].temp > maxTemp) maxTemp = infoArr[i].temp;
//      if (infoArr[i].hum > maxHum) maxHum = infoArr[i].hum;
      if (infoArr[i].pres > maxPres) maxPres = infoArr[i].pres;
    }
    if (maxTemp - minTemp < 10) maxTemp = minTemp + 10;
//    if (maxHum - minHum < 10) maxHum = minHum + 10;
    if (maxPres - minPres < 10) maxPres = minPres + 10;


    myOLED.setFont(SmallFont);
//    myOLED.printNumI(round((minTemp - 80) / 2.0), 0, 11);
    myOLED.printNumI(round((minTemp - 80) / 2.0), 0, 22);
    myOLED.printNumF(temp, 1, 0, 11);
    myOLED.printNumI(round((maxTemp - 80) / 2.0), 0, 1);

//    myOLED.printNumI(minHum, 0, 34);
//    myOLED.printNumI(maxHum, 0, 24);

    myOLED.printNumI(round((minPres + 1380) / 2.0), 0, 55);
//    myOLED.printNumI(round((maxPres + 1380) / 2.0), 0, 47);
    myOLED.printNumI(pres, 0, 45);
    myOLED.printNumI(round((maxPres + 1380) / 2.0), 0, 34);

    int z = 0;
    int x = 25;
    for (int i = 0; i < PLOT_LEN; i++) {
//      if (infoArr[i].temp == 0 && infoArr[i].hum == 0 && infoArr[i].pres == 0) continue;
      if (infoArr[i].temp == 0 && infoArr[i].pres == 0) continue;

      /*
        myOLED.drawLine(x, map(infoArr[i].temp, minTemp, maxTemp, 18, 0), x + 1, map(infoArr[i + 1].temp, minTemp, maxTemp, 18, 0));
        myOLED.drawLine(x, map(infoArr[i].hum, minHum, maxHum, 40, 22), x + 1, map(infoArr[i + 1].hum, minHum, maxHum, 40, 22));
        myOLED.drawLine(x, map(infoArr[i].pres, minPres, maxPres, 62, 44), x + 1, map(infoArr[i + 1].pres, minPres, maxPres, 62, 44));
      */

/*
      drawCol(x, map(infoArr[i].temp, minTemp, maxTemp, 17, 0), 17);
      drawCol(x, map(infoArr[i].hum, minHum, maxHum, 40, 23), 40);
      drawCol(x, map(infoArr[i].pres, minPres, maxPres, 63, 46), 63);
*/
      drawCol(x, map(infoArr[i].temp, minTemp, maxTemp, 23, 0), 23);      //рисуем г-к температуры
      drawCol(x, map(infoArr[i].pres, minPres, maxPres, 63, 40), 63);     //рисуем г-к давление
      
      z++;
      if (z > 15) {z = 0; x++;} //6 столбиков по 15 точек, примерно 2 часа
      
      x++;
    }
    
    myOLED.update();
    delay(2000);
    
  }

inline void drawCol(int x, int y, int yn) {
  for (int i = y; i <= yn; i++) {
    myOLED.setPixel(x, i);
  }
}

