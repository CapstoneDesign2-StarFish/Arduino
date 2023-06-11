#define Main_pin 2 
#define Sub_pin 7


void setup() {
  // put your setup code here, to run once:
  pinMode(Main_pin,OUTPUT); // 메인 수조
  pinMode(Sub_pin,OUTPUT);  //서브 수조
  Serial.begin(9600);
}

void Main_Pump_on()
{
  digitalWrite(Main_pin,HIGH);
}

void Main_Pump_off()
{
  digitalWrite(Main_pin,LOW);
}

void Sub_Pump_on()
{
  digitalWrite(Sub_pin,HIGH);
}

void Sub_Pump_off()
{
  digitalWrite(Sub_pin,LOW);
}

void Cycle()
{
  Main_Pump_on();
  Sub_Pump_on();
}

void Cycle_Quit()
{
  Main_Pump_off();
  Sub_Pump_off();
}

void Supply()
{
  Sub_Pump_on();
}
void Supply_Quit()
{
  Sub_Pump_off();
}
void loop() {
  // put your main code here, to run repeatedly:

  int signal = 0;
  signal = Serial.read();
  switch(signal)
  {
    case 1:
      Cycle();
      break;
    case 2:
      Cycle_Quit();
      break;
    case 3:
      Sub_Pump_on();
      break;
    case 4:
      Sub_Pump_off();
      break;
    case 5:
      Serial.write('7');
      break;
  }
}
