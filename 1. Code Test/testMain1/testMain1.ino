#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte degree[8] = {
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B11111
};
/*=============LCD==============*/

#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
DateTime now;
/*=============RTC==============*/

#include <EEPROM.h>
/*============EEPROM=============*/
/*============BLYNK=============*/

#define BUZ 2
#define LIGHT1 26
#define LIGHT2 25
#define MENU 15
#define PLUS 4
#define MINUS 5
#define SW 18
#define ACC 19
#define SEL 21
/*=========PERIPHERAL==========*/

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur"};
int a[4];
int currentHour = -1;
int flagMenu = 0, flagMode = 1, flagTime = 1, flagSelect = 1;
int hOn, mOn, hOff, mOff, y;
unsigned long Time;
bool cursor = 1;
bool deviceOn;
String numberPhone = "";
/*=========VARIABLE==========*/

void setup() {

  Serial.begin(9600);     
  Serial.println();

  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  Serial2.println("AT+CMGF=1"); delay(50);
  Serial2.println("AT+CNMI=2,2,0,0,0"); delay(50);
  Serial2.println("AT+CMGL=\"REC UNREAD\""); delay(50);
  Serial2.println("AT+CMGD=1,4"); delay(50);

  EEPROM.begin(1024); 
  for (int i = 0; i<4; i++)
  {
    a[i] = EEPROM.read(i);
    delay(100);
  }
  hOn  = a[0];
  mOn  = a[1];
  hOff = a[2];
  mOff = a[3];
  Serial.print(a[0]); Serial.print("\t");
  Serial.print(a[1]); Serial.print("\t");
  Serial.print(a[2]); Serial.print("\t");
  Serial.println(a[3]);
  
  if (hOn == 255 || mOn == 255 || hOff == 255 || mOff == 255) {Serial.println("READ DATA FAILED");} //Check error
  else{Serial.println("READ DATA SUCCESS");}

  pinMode(BUZ, OUTPUT);
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  pinMode(MENU, INPUT_PULLUP);
  pinMode(PLUS, INPUT_PULLUP);
  pinMode(MINUS, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  pinMode(ACC, INPUT_PULLUP);
  pinMode(SEL, INPUT_PULLUP);

  Wire.begin(23, 22);

  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree);

  if (!rtc.begin()) 
  {
    Serial.println("Couldn't find RTC"); //Check error
    while (1);
  }
  if (!rtc.isrunning()) 
  {
    Serial.println("RTC is NOT running!"); //Check error
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  now = rtc.now();
  turnOnOffDevice(hOn, mOn, hOff, mOff);

  static bool staMenu = 1;
  if (digitalRead(MENU) == 0 && staMenu == 1) 
  {
    Ring(1,50);
    flagMenu++;
    lcd.clear();
    delay(200);
    if (flagMenu>2){flagMenu = 0;}
  }
  staMenu = digitalRead(MENU);

  switch(flagMenu) 
  {
    case 0: printTime();          break;
    case 1: selectMode();         break;
    case 2: flagMenu=0;           break;
  }
}

void Ring(int repeat, int delays)
{
  for(int i=repeat; i>0; i--)
  {
    digitalWrite(BUZ,1); delay(delays); 
    digitalWrite(BUZ,0); delay(delays);
  }
}