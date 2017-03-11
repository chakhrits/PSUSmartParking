
#include<stdio.h>
#define TRIGGER_PIN  D5
#define ECHO_PIN     D6
#define B_pin D0
#define G_pin D3
#define R_pin D4
int st_B = 0;
int st_G = 0;
int st_R = 0;

void setup() {
  Serial.begin (9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(B_pin,OUTPUT);
  pinMode(G_pin,OUTPUT);
  pinMode(R_pin,OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  delay(1);

  if(distance >= 150){
    displayRGB(0,1,0);
  }else{
    displayRGB(1,0,0);
  }
}

void displayRGB(int R, int G, int B)
{
  digitalWrite(B_pin, B);  
  digitalWrite(G_pin, G);  
  digitalWrite(R_pin, R);  
} 

