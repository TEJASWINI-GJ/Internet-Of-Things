//Google Assistant Home Automation 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h" 
#include "Adafruit_MQTT_Client.h" 

#define Relay1	D1


//WLAN Details

#define WLAN_SSID "OnePlus 6T" // Your SSID 
#define WLAN_PASS "Anuroopa" // Your password


//Adafruit.io Setup

#define AIO_SERVER "io.adafruit.com" //Adafruit Server 
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "Tejaswinigj" // Username
#define AIO_KEY "aio_jorD45K7nwOVWdPbdQNeWLElO3CS" // Auth Key



//WIFI CLIENT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe Light = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay1"); // Feeds name should be same everywhere 
void MQTT_connect();

void setup()
{

Serial.begin(115200); pinMode(Relay1, OUTPUT);



// Connect to WiFi access point. 
Serial.println(); 
Serial.println(); 
Serial.print("Connecting to "); 
Serial.println(WLAN_SSID);

WiFi.begin(WLAN_SSID, WLAN_PASS);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");

}

Serial.println(); Serial.println("WiFi connected"); Serial.println("IP address: "); Serial.println(WiFi.localIP());

mqtt.subscribe(&Light);

}

void loop()
{

MQTT_connect(); 
Adafruit_MQTT_Subscribe *subscription;

while ((subscription = mqtt.readSubscription(20000)))

{

if (subscription == &Light)
{

Serial.print(F("Got: ")); Serial.println((char *)Light.lastread);
int Light_State = atoi((char *)Light.lastread); digitalWrite(Relay1, Light_State);

}

}
}

void MQTT_connect()
{

int8_t ret;
if (mqtt.connected())
{
return;
}

Serial.print("Connecting to MQTT... "); uint8_t retries = 3;
while ((ret = mqtt.connect()) != 0)
{

Serial.println(mqtt.connectErrorString(ret)); Serial.println("Retrying MQTT connection in 5 seconds...");
mqtt.disconnect();
delay(5000); retries--;
if (retries == 0)
{
while (1);
}
}

Serial.println("MQTT Connected!");
}
