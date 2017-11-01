/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define led 9

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
// digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
// delay(100);               // wait for a second
// digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
// delay(100);               // wait for a second


for(int i=0;i<=255;i++){
		analogWrite(led, i);
		//Задержка для более плавного эффекта свечения
		delay(5);
	}
	
	//затухания светодиода
	for(int i=255;i>=0;i--){
		analogWrite(led, i);
		//Задержка для более плавного эффекта потухания
		delay(5);
	}

	//Выставляем паузу 0.5с 
	delay(500);
}
