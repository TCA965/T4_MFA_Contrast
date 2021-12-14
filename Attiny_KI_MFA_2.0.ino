const int ThermistorPin = A3;
const int PotiPin = A2;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int lm317 = 0;
const int PWM_Out = 0;

void setup() {
  pinMode(PWM_Out,OUTPUT);
  digitalWrite(PWM_Out, HIGH);
  delay(2000);
  
 
}
//4.1 V LM317 = -5.3V | 180 -20
//5.2 V LM317 = -6.4V | 154 (154: -6.42 V; 155: -6.37V) 22
//6.4 V LM317 = -7.5V | 132 60



void loop() {
  // put your main code here, to run repeatedly:

 Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  int offset = analogRead(PotiPin);
  offset = map(offset, 0, 1023, 100, 200);
  
  lm317 = T * (-0.6) + offset;


  analogWrite(PWM_Out, lm317);

  
  
}
