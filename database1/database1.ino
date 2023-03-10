///////////////Created by Gledis Qose//////////////////


#include <WiFi.h>
//#include "DHT.h"


const int potPin = 39;// Analog pin

int potValue;// do not change
float voltage =0;// do not change


const char* ssid     = "Zintech";
const char* password = "12345678";
const char* host = "localhost";


void setup()
{
  
    Serial.begin(115200);
  

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}



void loop()
{
  
 potValue = analogRead(potPin);
  voltage = (3.3/4095.0) * potValue;
  Serial.print("potValue:");
  Serial.print(potValue);
   
  Serial.print(" Voltage:");
  Serial.print(voltage);
  Serial.println("V");  
  delay(2000); // delay in between reads for stability
   
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 5555;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

 


  client.print(String("GET http://localhost/iot_project/connect.php?") + 
                          ("&Plot=") + potValue +
                          ("&voltage=") + voltage +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
}

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        
    }

    Serial.println();
    Serial.println("closing connection");
}