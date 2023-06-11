
#include<OneWire.h>  //수온센서
#include<DallasTemperature.h>  //수온센서

#define main_level_sensor_pin 3     //아날로그핀 1은 메인 물높이센서
#define sub_level_sensor_pin 1     //아날로그핀 3은 보조 물높이센서
#define pH_sensor_pin 7             //아날로그핀 7은 산성도 센서
#define temperature_sensor_pin 2    //디지털핀 2는 수온센서
#define ph_offset 0.33            //ph 7.0 오프셋

OneWire OneWire(temperature_sensor_pin);  //수온센서 
DallasTemperature temperature(&OneWire);

#define ArrayLenth 10
int pHArray[ArrayLenth];
int pHArrayIndex = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(1,INPUT);
  temperature.begin();
  Serial.begin(9600);
}

String Temperature_examine()  //온도측정
{
  long long sensor_sum = 0.0;
  temperature.requestTemperatures();
  for(int i = 0; i < 10; ++i){
    float water_temperature = temperature.getTempCByIndex(0);
    sensor_sum += water_temperature;
  }
  return String(sensor_sum/10.0);
  //return "1.23";
}

String Level_examine(int Lpin)  //수위 측정
{
  long long sensor_sum = 0.0;
  for(int i = 0; i < 10; ++i){
   float water_level = analogRead(Lpin);
   sensor_sum += water_level;
  }
  return String(sensor_sum/10.0);
  //return "4.56";
}

String PH_examine() //산성도 측정
{
  static unsigned long samplingTime = millis();
  static float pHValue, voltage;
  for(int i = 0; i < 10; ++i) {
    pHArray[pHArrayIndex++] = analogRead(pH_sensor_pin);
    if (pHArrayIndex == ArrayLenth) pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
    pHValue = 3.5 * voltage + ph_offset;
  }
  pHValue = pHValue - 3; 
  return String(pHValue);
  //return "7.13";
}

double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    return 0;
  }
  if (number < 5) {
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0];
      max = arr[1];
    } else {
      min = arr[1];
      max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;
          max = arr[i];
        } else {
          amount += arr[i];
        }
      }
    }
    avg = (double)amount / (number - 2);
  }
  return avg;
}

void Examine()  //측정한 값 출력하기
{
  String strTemp = Temperature_examine(); //수온
  String strPh = PH_examine(); //산성도
  String strMainWaterLevel = Level_examine(main_level_sensor_pin); //메인수위
  String strSubWaterLevel = Level_examine(sub_level_sensor_pin); //보조수위

  for (int T = 0 ; T < strTemp.length() ; T ++)
    Serial.write(strTemp.charAt(T));

  Serial.write('@');

  for (int T = 0 ; T < strPh.length() ; T ++) 
    Serial.write(strPh.charAt(T));

  Serial.write('@');

  for (int T = 0 ; T < strMainWaterLevel.length() ; T ++) 
    Serial.write(strMainWaterLevel.charAt(T));

  Serial.write('@');

  for (int T = 0 ; T < strSubWaterLevel.length() ; T ++) 
    Serial.write(strSubWaterLevel.charAt(T));

  Serial.write('#');
}


void loop() {
  // put your main code here, to run repeatedly:
  int signal = 0;
  signal = Serial.read();

  switch(signal)
  {
    case '1': 
      Examine();
      break;
    case '5':
      Serial.write('6');
  }
  
}
