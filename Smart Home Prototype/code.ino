// LDR and TEMPERATURE SENSOR PROJECT

// variable declaration
float LDR_val,LDR_volt;
float Temperature,temp_volt,temp_degree;

// pin declaration
#define LDR A1
#define pwm_bulb 3
#define pwm_fan 6
#define Temp_Sen A5

//setup function
void setup()
{
  pinMode(LDR, INPUT);
  pinMode(Temp_Sen, INPUT);
  Serial.begin(9600);
  pinMode(pwm_bulb, OUTPUT);
  pinMode(pwm_fan, OUTPUT);
  
}

// loop function
void loop()
{
  // analog value
  LDR_val = analogRead(LDR);  
  Temperature = analogRead(Temp_Sen);
  
  //converted to digital (0-5 V)
  LDR_volt = (LDR_val*5)/1024; 
  temp_volt = (Temperature*5)/1024;
  temp_degree = (temp_volt-0.5)*100;
  //Serial.println(" LDR volt ");
  //Serial.print(LDR_volt);
  Serial.println(" degree celcius");
  Serial.print(temp_degree);
  //delay(2000);
  
  // temperature sensor control
  analogWrite(pwm_fan,0);
  if (temp_degree>18.00)
  {
    if (temp_degree<24.00)
    {analogWrite(pwm_fan,63);}
    else if (temp_degree>=24.00 && temp_degree<27.00)
    {analogWrite(pwm_fan,127);}
    else if (temp_degree>=27.00 && temp_degree<30.00)
    {analogWrite(pwm_fan,191);}
    else if (temp_degree>=30.00)
    {analogWrite(pwm_fan,255);}
    
  }
  
  // LDR control
  analogWrite(pwm_bulb,0);
  if (LDR_volt>0.46)
  {
    if (LDR_volt<0.57)
    {analogWrite(pwm_bulb,10);}
    else if (LDR_volt>=0.57 && LDR_volt<0.79)
    {analogWrite(pwm_bulb,64);}
    else if (LDR_volt>=0.79 && LDR_volt<1.42)
    {analogWrite(pwm_bulb,127);}
    else if (LDR_volt>=1.42)
    {analogWrite(pwm_bulb,255);}
    
  }
  
  
 }
