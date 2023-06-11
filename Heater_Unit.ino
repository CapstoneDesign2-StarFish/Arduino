#define heat_pin 8

bool heater_bool = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(heat_pin,OUTPUT); // 온열기
  Serial.begin(9600);
}

void heater()
{
  digitalWrite(heat_pin,HIGH);
  delay(30000);
  digitalWrite(heat_pin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!Serial.available()){}
  int signal = Serial.read();
  switch(signal)
  {
    case '5':
      Serial.write('9');
      break;

    case '1':
      heater();
      break;
  }

}
