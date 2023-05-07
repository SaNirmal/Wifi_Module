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
   else if (data[0]== 2) {
  Serial.println("IC");
  HTTPClient http;  
  String url = "https://uokcomponent.000webhostapp.com/index.php?type=2";
  http.begin(url);
          int httpResponseCode = http.GET();
          if (httpResponseCode > 0) {
            Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
          } else {
            Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
          }
          http.end();   
 //for (int y = 2; y < size; y++) {
    String type;
    switch (data[1]) {
      case 21:
        type = "TWO_INPUT_AND";
        break;
      case 22:
        type = "TWO_INPUT_OR";
        break;
      case 23:
        type = "TWO_INPUT_XOR";
        break;
      case 24:
        type = "TWO_INPUT_NAND";
        break;
      case 25:
        type = "TWO_INPUT_NOR";
        break;
      case 26:
        type = "TWO_INPUT_XNOR";
        break;
      case 31:
        type = "THREE_INPUT_AND";
        break;
      case 32:
        type = "THREE_INPUT_OR";
        break;
      case 33:
        type = "THREE_INPUT_XOR";
        break;
      case 34:
        type = "THREE_INPUT_NAND";
        break;
      case 35:
        type = "THREE_INPUT_NOR";
        break;
      case 36:
        type = "THREE_INPUT_XNOR";
        break;
      case 41:
        type = "FOUR_INPUT_AND";
        break;
      case 42:
        type = "FOUR_INPUT_OR";
        break;
      case 43:
        type = "FOUR_INPUT_XOR";
        break;
      case 44:
        type = "FOUR_INPUT_NAND";
        break;
      case 45:
        type = "FOUR_INPUT_NOR";
        break;
      case 46:
        type = "FOUR_INPUT_XNOR";
        break;
    }
    Serial.println(type);
    String typeIc = type;    
    ICpin[0] = String(data[2]);
    ICpin[1] = String(data[3]);
    ICpin[2] = String(data[4]);
     
  
    
    // Join the data and send the HTTP request
    ICpinJoined = ICpin[0] + "," + ICpin[1] + "," + ICpin[2];
  // HTTPClient http;  
   
    url = "https://uokcomponent.000webhostapp.com/icread.php?v1=" + typeIc +"&v2="+ICpinJoined;
    http.begin(url);
    // int httpResponseCode = http.GET();
    httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
    } else {
      Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end(); 
    delay(100);
        
        
     // }      
    }
else if (data[0]== 3) {
  Serial.println("Transistor");
  HTTPClient http;  
  String url = "https://uokcomponent.000webhostapp.com/index.php?type=2";
  http.begin(url);
          int httpResponseCode = http.GET();
          if (httpResponseCode > 0) {
            Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
          } else {
            Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
          }
          http.end();   }
  else if (data[0] == 4) {
  Serial.println("Op-Amp");
  HTTPClient http;  
  String url = "https://uokcomponent.000webhostapp.com/index.php?type=2";
  http.begin(url);
          int httpResponseCode = http.GET();
          if (httpResponseCode > 0) {
            Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
          } else {
            Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
          }
          http.end();     }  

  }



