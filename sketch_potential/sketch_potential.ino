

const int potPin = 39;// Analog pin

int potValue;// do not change
float voltage =0;// do not change


void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}


void loop() {
  // read the input on analog pin potPin:
  potValue = analogRead(potPin);
  voltage = (3.3/4095.0) * potValue;
  Serial.print("potValue:");
  Serial.print(potValue);
   
  Serial.print(" Voltage:");
  Serial.print(voltage);
  Serial.println("V");  
  delay(2000); // delay in between reads for stability

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
 