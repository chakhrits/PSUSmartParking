#include <ESP8266WiFi.h>
#include<PubSubClient.h>

#define TRIGGER_PIN  D5
#define ECHO_PIN     D6
#define B_pin D0
#define G_pin D3
#define R_pin D4

int st_B = 0;
int st_G = 0;
int st_R = 0;
long distance = 0;

const char* ssid = "";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* pubTopic = "easyparkingPSU";
//const char* subTopic = "easyparkingPSU";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin (9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(G_pin, OUTPUT);
  pinMode(R_pin, OUTPUT);

  client.setServer(mqtt_server, mqtt_port);

}

void loop() {
  int d = (int)sr04();
  
  publish_distance(d);

  distance = sr04();
  if (distance >= 0 && distance <= 200) {
    displayRGB(1, 0, 0);
  } else {
    displayRGB(0, 1, 0);
  }

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
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

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Chakhrit5730213017"))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish(pubTopic, "hello world");
      // ... and resubscribe
      //client.subscribe(subTopic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void publish_distance(int d) {
  char buf[256];

  snprintf(buf, 256, "distance:%d", d);
  client.publish(pubTopic, buf);
}



