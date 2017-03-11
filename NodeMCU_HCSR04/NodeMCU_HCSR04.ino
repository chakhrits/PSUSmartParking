#include <stdio.h>
#include <ESP8266WiFi.h>
#define TRIGGER_PIN  D5
#define ECHO_PIN     D6
#define B_pin D0
#define G_pin D3
#define R_pin D4
const char* ssid = "";
const char* password = "";
int st_B = 0;
int st_G = 0;
int st_R = 0;
long distance = 0;

void setup() {
  Serial.begin (9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(R_pin, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("connect fail!");
    Serial.print(".");
    delay(100);
  }
  
  distance = sr04();
  if (distance >= 0 && distance <= 200) {
    displayRGB(1, 0, 0);
  } else {
    displayRGB(0, 1, 0);
  }
}

//LED RGB Function
void displayRGB(int R, int G, int B)
{
  digitalWrite(B_pin, B);
  digitalWrite(G_pin, G);
  digitalWrite(R_pin, R);
}

//Read distance from sensor HC-SR04
long sr04()
{
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29;
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);
  return distance;

}


