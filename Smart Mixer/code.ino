// Smart Mixer Project

#define force_sensor A5
#define led_red 13
#define led_blue 12
#define led_green 11
#define pwm 3

float force;
float force_volt;


void setup()
{
  Serial.begin(9600);
  pinMode(force_sensor,INPUT);
  pinMode(led_red,OUTPUT);
  pinMode(led_blue,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(pwm,OUTPUT);
}

void loop()
{
  force = analogRead(force_sensor);
  force_volt = (force/1024)*5;
  // Serial.println(force_volt);
  
  if (force_volt == 0)
  {
    analogWrite(pwm,0);
    Serial.println("Mixer is off");
  }
  else if (force_volt>0)
  {
    if (force_volt<=0.75)
    {
      analogWrite(pwm,85);
      Serial.println("Mixer speed: Low");
      digitalWrite(led_red,LOW);
      digitalWrite(led_blue,LOW);
      digitalWrite(led_green,HIGH);
    }
    else if (force_volt>0.75 && force_volt<=1.5)
    {
      analogWrite(pwm,167);
      Serial.println("Mixer speed: Medium");
      digitalWrite(led_red,LOW);
      digitalWrite(led_blue,HIGH);
      digitalWrite(led_green,LOW);
    }
    else if (force>1.5)
    {
      analogWrite(pwm,255);
      Serial.println("Mixer speed: High");
      digitalWrite(led_red,HIGH);
      digitalWrite(led_blue,LOW);
      digitalWrite(led_green,LOW);
    }
  }
}