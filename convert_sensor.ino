#include<stdio.h>
#include<String.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char *sensor = "21.45@7.00.@0.00@254.00";
  int len = strlen(sensor);
  Serial.println("sensor : " + *sensor);
  Serial.println("len : " + len);
  for(int i=0;i<len;i++){
    sensor[i] = sensor[i]+17;
    Serial.println(sensor[i]);
  }
  Serial.println(sensor);
  delay(50000);
}
