
#define led 9

void setup() {                
  pinMode(led, OUTPUT);     
}

void loop() {
    for(int c=0;c<=10;c++){ //10
    for(int i=0;i<=255;i++){
		analogWrite(led, i);
		delay(10);
	}
	
	//затухания светодиода
	for(int i=255;i>=0;i--){
		analogWrite(led, i);
		delay(10);
	}
	delay(500);
  }
  
  for(int i=0;i<=50;i++){  
      digitalWrite(led, HIGH);   
      delay(200);               
      digitalWrite(led, LOW);    
      delay(200);              
   }
   
     for(int b=0;b<=18;b++){  
      digitalWrite(led, HIGH);   
      delay(600);               
      digitalWrite(led, LOW);    
      delay(600);              
   }
}
