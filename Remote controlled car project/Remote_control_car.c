#include<TM1637Display.h>

int temp;
float divisor;
float val = 0;
float final_per = 0;
float height = 30;
const int CLK = 9;
const int DIO = 8;

int red = 6;
int yellow = 5;
int green = 4;

int trigPin = 10;
int echoPin = 11;
long duration, cm, inches;

TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin (9600);
 
  display.setBrightness(0xff);
 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
 
  pinMode(7, OUTPUT);
  digitalWrite(7, 1);
}

void loop() {
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;
 
  divisor = height/100;
  val = height - cm;
  final_per = val / divisor;
 
  display.showNumberDec(final_per);
 
  Serial.print(final_per);
  Serial.println(" % ");
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();
  delay(250);

  if(final_per>2.0 && final_per<25.0) //0%-25%
  {
    digitalWrite(red, 0);
    digitalWrite(yellow, 0);
    digitalWrite(green, 1);
    Serial.println("Started ");
  }
  else if(final_per>25.0 && final_per<90.0) //25%-90.0%
  {
    digitalWrite(red, 0);
    digitalWrite(yellow, 1);
    digitalWrite(green, 0);
    Serial.println("midway");
  }
  else if(final_per>90.0 && final_per<100.0)  //90.=%-100%
  {
    digitalWrite(red, 1);
    digitalWrite(yellow, 0);
    digitalWrite(green, 0);
    Serial.println("Almost full");
  }
}