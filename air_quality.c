#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include "MQ2.h"

int Analog_Input = A0;
int lpg, co, smoke, smoke1;
float h, t;
MQ2 mq2(Analog_Input);
const char *ssid = "nitish's Iphone";
const char *pass = "12345678";

DHT dht(D5, DHT11);
WiFiClient client;
long myChannelNumber = 2418191;

ong myChannelNumber = 2418191;
const char myWriteAPIKey[] =
    "DS7HZN9X531KAQ2J";
// #define RLOAD 22.0
//  Calibration resistance at atmospheric CO2 level
// #define RZERO 879.13
int val;
void setup()
{
    mq2.begin();
    // put your setup code here, to run once:
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
Serial.print("
..
");
    }
    Serial.println();
    Serial.println("NodeMCU is connected!");
    Serial.println(WiFi.localIP());
    dht.begin();
    ThingSpeak.begin(client);
}

void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float *values = mq2.read(true);
    lpg = mq2.readLPG();
    co = mq2.readCO();
    smoke = mq2.readSmoke();
    smoke1 = (smoke * 100) / 1000000;
    Serial.println("LPG:");
    Serial.println(lpg);
    Serial.println(" CO:");
    Serial.println(co);
    Serial.println("SMOKE:");
    Serial.println(smoke1);
    Serial.println(" %");
    delay(1000);
    ThingSpeak.writeField(myChannelNumber, 1, lpg, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 2, co, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 3, smoke1, myWriteAPIKey);
    Serial.println("Temperature: " + (String)t);
    Serial.println("Humidity: " + (String)h);
    ThingSpeak.writeField(myChannelNumber, 4, t, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 5, h, myWriteAPIKey);
    delay(100);
}