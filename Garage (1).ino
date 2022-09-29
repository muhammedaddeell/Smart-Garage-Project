          //*****************SMART GARAGE PROJECT****************
#include "Wire.h"                          //special dec for lcd
#include "LiquidCrystal_I2C.h"            //special dec for lcd
LiquidCrystal_I2C lcd(0x27,16,2);        //special dec for lcd
#include <Adafruit_LiquidCrystal.h>     //lcd library
Adafruit_LiquidCrystal lcd_1(0);       //special dec for lcd
#include <Servo.h>                    //servo library
Servo myservo;                       //create servo object to control a servo
int pos = 0;                        //create servo object to control motion of servo 
#define IR1 6                      //declaration for IR Sensor outside garage
#define IR2 8                     //declaration for IR Sensor inside garage
#define Buzzer 11                 //declaration for Buzzer
#define TempSensor A5              //declaration for Temperature Sensor
#define led1 2                      //declaration le led1 turn on when lights turn off
#define ledblinking 3                //declaration le led t blinking when temp over,
#define led2 4                        //declaration le led2 turn on when lights turn off
#define led3 5                         //declaration le led3 turn on when lights turn off
#define ldr1 A0                         //ldr1 for solt1
#define ldr2 A1                          //ldr1 for solt2
#define ldr3 A2                           //ldr1 for solt3
#define ldrblinking A3                     //ldr reading lights, when the lights turn off, 4 leds will turn on
unsigned long prevTime = millis();         //variable to store prev time
int x =1;                                 //variable for itiration
int Fill=0;                              //variable to store busy slots
int Emp =3;                             //variable to store empty slots
int Slot1=0;                           //mean slot1 empty
int Slot2=0;                          //mean slot2 empty
int Slot3=0;                         //mean slot3 empty

void setup() {
Serial.begin(9600);
pinMode(IR1, INPUT);
pinMode(IR2, INPUT);
pinMode(TempSensor, INPUT);
pinMode(ldr1, INPUT);
pinMode(ldr2, INPUT);
pinMode(ldr3, INPUT);
pinMode(ldrblinking, INPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(ledblinking, OUTPUT);
pinMode(Buzzer,OUTPUT);
myservo.attach(9);
myservo.write(0);
lcd.init();                      //initz lcd
lcd.backlight();                 //initz lcd
lcd.clear();
}

void loop() {

//*********************LCD********************************************
unsigned long currentTime = millis();
if(x%3 ==0){                        //every 3rd itiration, display the spaces available to park
  if(currentTime - prevTime > 5000){ // 0 is empty, 1 is full
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Slot1:");
  lcd.setCursor(6,0);
  lcd.print(Slot1);
  lcd.setCursor(0,1);
  lcd.print("Slot2:");
  lcd.setCursor(6,1);
  lcd.print(Slot2);
  lcd.setCursor(9,0);
  lcd.print("Slot3:");
  lcd.setCursor(15,0);
  lcd.print(Slot3);
  prevTime = currentTime;
  x = x+1;}}
  

else if(x%2!=0){ //every even itiration, display the welcome sign
if(currentTime - prevTime > 5000){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome to our");
  lcd.setCursor(4,1);
  lcd.print("garage");
  prevTime = currentTime;
  x = x+1;}}

else if(x%2==0){ //every odd itiration !=3 display the number of full and empty spaces
  if(currentTime - prevTime > 5000){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fill:");
  lcd.setCursor(7,0);
  lcd.print(Fill);
  lcd.setCursor(0,1);
  lcd.print("Emp:");
  lcd.setCursor(7,1);
  lcd.print(Emp);
  prevTime = currentTime;
  x= x+1;}}
//*********************Gate********************************************  
int IR1_reading = digitalRead(IR1);
int IR2_reading = digitalRead(IR2);

if (IR1_reading == 0 || IR2_reading ==0){
  for (pos = 0; pos <= 90; pos += 1){
    myservo.write(pos); delay(15);}
    delay(2000);
    for (pos = 90; pos >= 0; pos -= 1){
    myservo.write(pos); delay(15);}
  }

//*************************Parking****************************************  
int ldr1_reading = analogRead(ldr1);
int ldr2_reading = analogRead(ldr2);
int ldr3_reading = analogRead(ldr3);
  
if (ldr1_reading >= 1003){
  Slot1=1;
}
else{Slot1=0;}

if (ldr2_reading >= 1003){
  Slot2=1;
}
else{Slot2=0;}

if (ldr3_reading >= 1003){
  Slot3=1;
}
else{Slot3=0;}

if(Slot1 ==0 && Slot2 ==0 && Slot3==0){Fill=0; Emp=3;}
if(Slot1 ==1 && Slot2 ==0 && Slot3==0){Fill=1; Emp=2;}
if(Slot1 ==0 && Slot2 ==1 && Slot3==0){Fill=1; Emp=2;}
if(Slot1 ==0 && Slot2 ==0 && Slot3==1){Fill=1; Emp=2;}
if(Slot1 ==1 && Slot2 ==1 && Slot3==0){Fill=2; Emp=1;}
if(Slot1 ==0 && Slot2 ==1 && Slot3==1){Fill=2; Emp=1;}
if(Slot1 ==1 && Slot2 ==0 && Slot3==1){Fill=2; Emp=1;}
if(Slot1 ==1 && Slot2 ==1 && Slot3==1){Fill=3; Emp=0;}

//***************************Day/Night Sensor**************************************
int ldrblinking_reading = analogRead(ldrblinking);


if (ldrblinking_reading >= 1010){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  }
else{
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  }
//*************************Fire Alarm****************************************
//float temp_reading = analogRead(TempSensor);
//float temp_val = temp_reading * (50.0/1023.0);


//while(temp_val > 30){
  //Serial.println(temp_val);
//delay(300);
  //digitalWrite(Buzzer,HIGH);
  //digitalWrite(Buzzer,LOW);
  //digitalWrite(ledblinking,HIGH);
  //delay(500);
  //digitalWrite(ledblinking,LOW);
  //delay(500);}

}
