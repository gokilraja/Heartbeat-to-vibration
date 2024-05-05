#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //For display

#define USE_ARDUINO_INTERRUPTS true   
#include <PulseSensorPlayground.h> //for pulse sensor

const int PulseWire = 0;       //pulse sensor data pin in (Ardiuno (A0))
const int LED = 12;          
int Threshold = 550;            
                               
PulseSensorPlayground pulseSensor;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int mode=8;    //toggle switch pin in(8)
int vib_sen=7;  //vibration sensor pin  in (7)
int bazar_pin=4;  //bazar in (4)

void setup() {
  Serial.begin(9600);
  pinMode(vib_sen,INPUT);
  pinMode(mode,INPUT);  //toggle switch state
  pinMode(bazar_pin,OUTPUT);
  lcd.begin();
  lcd.backlight();
   pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);   
  pulseSensor.setThreshold(Threshold);   
 
   if (pulseSensor.begin()) {
    lcd.setCursor(0,0);
    lcd.print("Heart,vibrate");
    delay(1000);
  }
}
  
void loop() {
  int mod=digitalRead(mode);  //read data in toggle switch "0 and 1"
  switch(mod){
     case 1:                //toggle switch output is '1' or HIGH means case 1 working
       if (pulseSensor.sawStartOfBeat()) {         
       int myBPM = pulseSensor.getBeatsPerMinute();                                                                       
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Heartrate mode");
       lcd.setCursor(0,1); 
       lcd.print("Heart in BPM:");
       lcd.setCursor(13,1);                   
       lcd.print(myBPM);   //output data in 16x2 display in heart rate
      }
      delay(20);
     break;
   case 0:    //toggle switch ouput '0'
     int vib;
     vib=digitalRead(vib_sen); //read data in vibration sensor
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("vibration mode");
     if(vib==1){
        digitalWrite(bazar_pin,HIGH); //the vibration sensor data is high (vibrating)
        lcd.setCursor(0,1);
        lcd.print("vibrating!");
        delay(500);      
    }
    
    else{
      digitalWrite(bazar_pin,LOW);
      lcd.setCursor(0,1);
      lcd.print("Normal....");  //The vibration sensor data is low (not vibrating)
      delay(100);      
     }
    break;
  }
  delay(5);
}
