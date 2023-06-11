#include<Servo.h> //서보모터
#include<Adafruit_NeoPixel.h>  //네오픽셀
//pwm 3,5,6,9,10,11
#define cleanMoter 3            //아날로그핀 3번 전면청소
#define Feed_Moter 9
#define Num_LEDS 8                  //LED 갯수 8개
#define neo_pin 8              //디지털핀 8은 네오픽셀
Servo servo1;     // 서보모터

Adafruit_NeoPixel Neo = Adafruit_NeoPixel(Num_LEDS,neo_pin,NEO_GRBW + NEO_KHZ800);

bool Light_bool = false;

void setup() {
  // put your setup code here, to run once:
  Neo.begin();  //네오픽셀 시작
  Neo.show();   //네오픽셀 초기화

  pinMode(Feed_Moter,OUTPUT);
  pinMode(cleanMoter,OUTPUT); // 청소

  light_off();
  Serial.begin(9600);
}
void clean(){
    analogWrite(cleanMoter,145);//140~170(정방향 허용 PWM)
  delay(6170);
    analogWrite(cleanMoter,0);
  delay(500);
    analogWrite(cleanMoter,225);//190~225(역방향 허용 PWM)
  delay(6300);
    analogWrite(cleanMoter,0);
  delay(1000);
}

void clean_bowl()
{
  clean();
}

void feed() //먹이주는 모터 
{
    analogWrite(Feed_Moter,145);//140~170(정방향 허용 PWM)
  delay(370);
    analogWrite(Feed_Moter,0);
  delay(500);
    analogWrite(Feed_Moter,225);//190~225(역방향 허용 PWM)
  delay(400);
    analogWrite(Feed_Moter,0);
  delay(1000);
}

void light_on()  //조명 켜기 
{
  Neo.Color(255,255,255);
  Neo.setPixelColor(1,0,0,255);
  Neo.show();
}

void light_off()  //조명 끄기
{
  Neo.Color(0,0,0);
  Neo.setPixelColor(1,0,0,0);
  Neo.show();
}

void light(){
  if (Light_bool == false)
  {
    light_on();
    Light_bool = true;
  }
  else if(Light_bool == true)
  {
    light_off();
    Light_bool = false;
  }
}

void loop() {
  // put your main code here, to run repeatedly
  int signal = 0;
  signal = Serial.read();
  switch(signal)
  {
    case '1':
      feed();
      break;
    case '2':
      light();
      break;
    case '3':
      clean_bowl();
      break;
    case '5':
      Serial.write('8');
      break;
  }
}