#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
const char* ssid = ".Phuket Smart WiFi";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
//const char* mqtt_user = "nvgrhlox";
//const char* mqtt_pass = "j361Nw7qNHe3";
const int mqtt_port = 1883;

const char* pubTopic = "sound";
const char* subTopic = "light";

#define LED  D5

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

void setup()
{
  pinMode(LED, OUTPUT);   // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
      reconnect();
  }
  client.loop();



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

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
      Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1')
  {
      digitalWrite(LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
      // but actually the LED is on; this is because
      // it is acive low on the ESP-01)
  }
  else
  {
      digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
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
          client.subscribe(subTopic);
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


