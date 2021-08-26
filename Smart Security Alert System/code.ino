// C++ code
//

#define echo 2
#define trig 3
#define buzzer 13

#include <LiquidCrystal.h>

float duration;
float distance;

LiquidCrystal lcd(12,11,7,6,5,4);

void setup()
{
  lcd.begin(16,2);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
  lcd.setCursor(1,0);
  lcd.print("Welcome Punit");
  delay(5000);
  
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("UltraSonic");
  lcd.setCursor(1,1);
  lcd.print("Sensor Project");
  delay(5000);
  
  lcd.clear();
  lcd.print("Smart Security");
  lcd.setCursor(0,1);
  lcd.print("Alarm System");
  delay(5000);
  
  lcd.clear();
  lcd.print("Scanning...");
  delay(3000);
}

void timeMeasurement()
{
  //triggering the Trig pin of US sensor by creating a pulse
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  //duration of pragration of ultrasonic sound
  duration = pulseIn(echo,HIGH);
}

void displayDistance()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance in Cm:");
  lcd.setCursor(0,1);
  lcd.print(distance);
  delay(1000);
}

void loop()
{
  timeMeasurement();
  distance = duration * (0.0343) / 2;
  
  if (distance <= 70)
  {
    tone(buzzer,300);
    lcd.clear();
    displayDistance();
    lcd.setCursor(7,1);
    lcd.print("Alert!!!");
    delay(1000);
  }
  else
  {
    noTone(buzzer);
    lcd.clear();
    displayDistance();
  }
}