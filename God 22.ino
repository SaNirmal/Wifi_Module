#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>

const char* ssid     = "Xiaomi";
const char* password = "22222222";

const int potPin = 39;
int potValue;// do not change
float voltage =0;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Wait for serial to initialize
  while (!Serial) {}

  // Code to clear the database
  HTTPClient httpClear;
  String urlClear = "https://uokcomponent.000webhostapp.com/clear.php";
  httpClear.begin(urlClear);
  int httpResponseCodeClear = httpClear.GET();
  if (httpResponseCodeClear > 0) {
    Serial.printf("HTTP response code (clear): %d\n", httpResponseCodeClear);
  }
  else {
    Serial.printf("HTTP request failed, error (clear): %s\n", httpClear.errorToString(httpResponseCodeClear).c_str());
  }
  httpClear.end();

  for (int i = 0; i < 20; i++) 
  {
    // Code to be executed inside the loop
    potValue = analogRead(potPin);
    voltage = (3.3/4095.0) * potValue;
    Serial.print("potValue:");
    Serial.print(potValue);
    Serial.print(" Voltage:");
    Serial.print(voltage);
    Serial.println("V");  
    delay(2000);  

    // Send data to server
    HTTPClient http;
    String url = "https://uokcomponent.000webhostapp.com/dbread.php?v1="+String(potValue)+"&v2="+String(voltage);
    // String url = "https://uokcomponent.000webhostapp.com/icread.php?v1="+String(gateName)+"&v2="+String(valueSet);
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
    }
    else {
      Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
  }
}

void loop() {
  // do nothing
}