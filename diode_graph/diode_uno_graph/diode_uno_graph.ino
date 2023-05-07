void setup() {
  Serial.begin(9600);

  int data[] =  {1,1,0,0,24,0,49,7,74,41,99,85,125,132,150,178,175,226,200,274,225,322,250,371,275,420,300,468,325,518,350,567,375,616,399,665,424,714,450,764,472,808};
  int size = sizeof(data) / sizeof(data[0]);
  Serial.write(size >> 8); // send the size of the array (high byte)
  Serial.write(size & 0xFF); // send the size of the array (low byte)
  for(int i = 0; i < size; i++){
    Serial.write(data[i] >> 8); // send the high byte of the integer
    Serial.write(data[i] & 0xFF); // send the low byte of the integer
  }

  delay(1000);
}

void loop() {
  // read data from sensors or other sources and save it in a variable
}
