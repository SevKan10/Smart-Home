#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
/*=============LCD==============*/

#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
DateTime now;
/*=============RTC==============*/

#define BUZ 2
#define LIGHT1 26
#define LIGHT2 25
#define MENU 15
#define PLUS 4
#define MINUS 5
/*=========PERIPHERAL==========*/

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur"};
int currentHour = -1;
int flag = 0;
int h = 0, m = 0;
/*=========VARIABLE==========*/

void setup() {

  Serial.begin(9600);     

  pinMode(BUZ, OUTPUT);
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  pinMode(MENU, INPUT_PULLUP);
  pinMode(PLUS, INPUT_PULLUP);
  pinMode(MINUS, INPUT_PULLUP);

  Wire.begin(23, 22);

  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop() {
  now = rtc.now();

  if (digitalRead(MENU) == 0) 
  {
    Ring(1,50);

    flag++;
    lcd.clear();
    delay(500);

    if (flag>2){flag = 0;}
  }
  switch (flag) 
  {
    case 0:
      printTime();
      turnOnOffDevice(12, 8, 12, 10);
    break;

    case 1:
      settingTime();
    break;

    case 2:
      flag = 0;
    break;
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