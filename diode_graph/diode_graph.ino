#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>

const char* ssid     = "Dialog 4G";
const char* password = "6A6Q2Y3MEA8";
String ICpin[3] = {"", "", ""};
String ICpinJoined = "";

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 baud
Serial.begin(9600);
  while (!Serial);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  while (!Serial) {}

  HTTPClient httpClear;
  String urlClear = "https://uokcomponent.000webhostapp.com/clear.php";
  httpClear.begin(urlClear);
  int httpResponseCodeClear = httpClear.GET();
  if (httpResponseCodeClear > 0) {
    Serial.printf("HTTP response code (clear): %d\n", httpResponseCodeClear);
  } else {
    Serial.printf("HTTP request failed, error (clear): %s\n", httpClear.errorToString(httpResponseCodeClear).c_str());
  }
  httpClear.end();  
}


void loop() {
  while(Serial.available() < 2); // wait for the size of the array to be sent
  int size = Serial.read() << 8; // read the high byte of the size
  size |= Serial.read(); // read the low byte of the size
  int data[size];

  for (int i = 0; i < size; i++) {
    while(Serial.available() < 2); // wait for two bytes to be available
    int highByte = Serial.read(); // read the high byte of the integer
    int lowByte = Serial.read(); // read the low byte of the integer
    data[i] = (highByte << 8) | lowByte; // combine the two bytes to form the integer
  }
  if(data[0]==1){
    Serial.println("Diode");
          HTTPClient http;      
          String url = "https://uokcomponent.000webhostapp.com/index.php?type=1";
          http.begin(url);
              int httpResponseCode = http.GET();
              if (httpResponseCode > 0) {
                Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
              } else {
                Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
              }
              http.end();
                                               
    for (int i = 2; i < size; i += 2) {
      float voltage = data[i] / 100.0;
      float current = data[i+1] / 100.0;
      Serial.print("Voltage: ");
      Serial.print(voltage);
      Serial.print("V, ");
      Serial.print("Current: ");
      Serial.print(current);
      Serial.println("A");
        String url = "https://uokcomponent.000webhostapp.com/dbread.php?v1=" + String(voltage) + "&v2=" + String(current);
            http.begin(url);
          int httpResponseCode = http.GET();
          if (httpResponseCode > 0) {
            Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
          } else {
            Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
          }
          http.end();        
        delay(100);      
    }  }
  else if(data[0]==2){
    Serial.print("not work \n");    

  }


}
