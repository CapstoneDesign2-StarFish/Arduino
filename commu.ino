#include<stdio.h>
#include<string.h>

int test = 9;

void setup() {
  pinMode(test, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  int val = '0';
  while(!Serial.available()){}
  int mov= Serial.read();

  Serial.write(mov);
}
