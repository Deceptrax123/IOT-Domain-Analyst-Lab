#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#define D5 0
DHT dht(D5, DHT11);
WiFiClient client;
const char *ssid = "SriNitish_5G";
const char *pass = "Sri9Nit@124";
const char *server = "api.thingspeak.com";
long channel_id = 2443725;
String write_api = "6XPM9WVI4FYSU3LP";
void setup()
{
    Serial.begin(9600);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print("..");
    }
    Serial.println();
    Serial.println("NodeMCU is connected!");
    Serial.println(WiFi.localIP());
}
void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT Sensor");
        return;
    }
    if (client.connect(server, 80))
    {
        String post_key = write_api;
        post_key += "&field1=";
        post_key += String(t);
        post_key += "&field2=";
        post_key += String(h);
        post_key += "\r\n\r\n";
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + write_api + "\n");
        client.print("Content-Type: application/x-www-form-urlenc
        client.print("Content-Length: ");
        client.print(post_key.length());
        client.print("\n\n");
        client.print(post_key);
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.print("Degree celsius, Humidity: ");


        Serial.print(h);
        Serial.println("%. Send data to ThingSpeak");
    }
    client.stop();
    Serial.println("Waiting");
    delay(1000);
}
