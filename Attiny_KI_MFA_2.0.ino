/*
 * ATtiny45
 * 8 MHz internal clock
 * Brown-Out-Detection disabled
 * Fuses:
 * EXTENDED: 0xFF
 * HIGH: 0xD7
 * LOW: 0xE2
 */

const int ThermistorPin = A3;
const int PotiPin = A2;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int lm317 = 0;
const int PWM_Out = 0;

void setup() {
  pinMode(PWM_Out, OUTPUT);
  digitalWrite(PWM_Out, HIGH);
  delay(2000);
}



void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;

  int offset = analogRead(PotiPin);
  offset = map(offset, 0, 1023, 100, 200);

  lm317 = T * (-0.6) + offset;


  analogWrite(PWM_Out, lm317);

}
