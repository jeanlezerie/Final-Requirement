#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#define sensorpin A0

LiquidCrystal_I2C lcd(32, 16, 2);
int servoPin=12; //Micro Servo1 Variable
int servoPin1=11;//Micro Servo2 Variable
Servo myservo1;
Servo myservo2;
int fSensor; // Force sensor Variable
int gLED=2;
int rLED=7;
int buzz=8;

int enRight = 9; //pin digital 9 enable right
int in1 = 10; //pin digital 8 input 1 negative motor right conveyor
int in2 = 6; //pin digital 7 input 2 positive motor right conveyor

int enLeft = 3; //pin digital 3 enable left
int in3 = 5; //pin digital 5 input 3 negative motor left conveyor 
int in4 = 4; //pin digital 4 input 4 positive motor left conveyor 
float kg;

void setup() 
{
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  
  pinMode(sensorpin,INPUT);
  pinMode(servoPin,OUTPUT);
  myservo1.attach(servoPin);
  pinMode(servoPin1,OUTPUT);
  myservo2.attach(servoPin1);
  
  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(buzz, OUTPUT);
  
  
  pinMode(enRight, OUTPUT);
  pinMode(enLeft, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  analogWrite(enRight, 255);
  analogWrite(enLeft, 255);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  Serial.begin(9600);
}

void loop() 
{

  fSensor=analogRead(A0);
  kg = fSensor/9.81; //conversion of newton to kg
  Serial.print("N = ");
  Serial.println(fSensor);
  Serial.print("Kg = ");
  Serial.println(kg);
  Serial.println();
  
  if (fSensor==0)
  {
    myservo1.write(0);
    myservo2.write(0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Detecting...");
  }
  if(fSensor>0&&fSensor<600)
  {
    myservo2.write(0);
    myservo1.write(90);
    digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
    digitalWrite(rLED, LOW);
    digitalWrite(gLED, HIGH);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print(kg);
    lcd.setCursor(9,0);
    lcd.print("kg"); 
    lcd.setCursor(2,1);
    lcd.print("Under Weight");
  }
  if(fSensor>600&&fSensor<800)
  {
    myservo1.write(0);
    myservo2.write(0);
    digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(rLED, LOW);
    digitalWrite(gLED, LOW);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print(kg);
    lcd.setCursor(9,0);
    lcd.print("kg");
    lcd.setCursor(2,1);
    lcd.print("Ideal Weight");
  }  
  if(fSensor>800)
  {
    myservo1.write(0);
    myservo2.write(90);
    digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
    digitalWrite(rLED, HIGH);
    digitalWrite(gLED, LOW);
    tone(buzz,500);
    delay(200);
    noTone(buzz);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print(kg);
    lcd.setCursor(9,0);
    lcd.print("kg");
    lcd.setCursor(2,1);
    lcd.print("Over Weight");
    
  }
    
 }
