#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>


float vot = 0;
float cur = 0;

const char* ssid     = "Malitha";
const char* password = "00000000";
String ICpin[3] = {"", "", ""};
String ICpinJoined = "";
float voltage = 0;


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
  // check if there is data available on the serial port
  for (int j = 0; j < 1; j++){
    
  if (Serial.available()) {
    // read the data and save it in a variable
    int size = Serial.read();
    int data = Serial.read();
    if(data == 1){
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
      int data[size];               
             
       /*for (int i = 0; i < size; i++) {
            data[i] = Serial.read();*/
        

          // send each value in the data array to the server
          //HTTPClient http;
          for (int i = 0; i < size; i += 2) {
            float voltage = Serial.read() / 100.0;
            float current = Serial.read() / 100.0;
            if(!(vot>voltage ||cur >current)){
            String url = "https://uokcomponent.000webhostapp.com/dbread.php?v1=" + String(voltage) + "&v2=" + String(current);
            Serial.println(voltage);
            Serial.println(current);            
            http.begin(url);
            int httpResponseCode = http.GET();
            if (httpResponseCode > 0) {
              Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
            } else {
              Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
            }
            http.end();
            vot = voltage;
            cur = current;   
        delay(100);
        }}
      }    
    
    else if (data == 2) {
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
  for (int y = 2; y < 3; y++) {
    int data2 = Serial.read();
    String type;
    switch (data2) {
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
      case 20:
        type = "NOT_DETECTED";
        break;
      case 30:
        type = "NOT_DETECTED";
        break;
      case 40:
        type = "NOT_DETECTED";
        break;          
                
    }
    Serial.println(type);
    String typeIc = type;    
    if (Serial.available() >= 3) {
    // Read the data
    for (int i = 0; i < 3; i++) {
      int data3 = Serial.read();
      if (data3 != -1) {
        ICpin[i] = String(data3);
      }
    }
    
    // Join the data and send the HTTP request
    ICpinJoined = ICpin[0] + "," + ICpin[1] + "," + ICpin[2];
    HTTPClient http;
    String url = "https://uokcomponent.000webhostapp.com/icread.php?v1=" + typeIc +"&v2="+ICpinJoined;
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      Serial.printf("HTTP response code (update): %d\n", httpResponseCode);
    } else {
      Serial.printf("HTTP request failed, error (update): %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end(); 
    delay(100);
        }
        
      }      
    }
else if (data == 3) {
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
  else if (data == 4) {
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
}
}

  // wait for a moment
 

