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

#define BUZ 2
#define LIGHT1 26
#define LIGHT2 25
#define MENU 15
#define PLUS 4
#define MINUS 5
#define SW 18
#define ACC 19

/*=========PERIPHERAL==========*/

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur"};
int currentHour = -1;
int flag = 0, flag1 = 1;
int hOn = 0, mOn = 0, hOff = 0, mOff = 0;
unsigned long Time;
bool cursor = 1;
/*=========VARIABLE==========*/

void setup() {

  Serial.begin(9600);     

  // EEPROM.begin(16); 
  // readEeprom(hOn, mOn, hOff, mOff);

  pinMode(BUZ, OUTPUT);
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  pinMode(MENU, INPUT_PULLUP);
  pinMode(PLUS, INPUT_PULLUP);
  pinMode(MINUS, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  pinMode(ACC, INPUT_PULLUP);

  Wire.begin(23, 22);

  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree);


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
    delay(200);

    if (flag>2){flag = 0;}
  }
  switch(flag) 
  {
    case 0:
      printTime();
      turnOnOffDevice(hOn, mOn, hOff, mOff);
    break;

    case 1:
      settingTime();
    break;

    case 2:
      flag = 0;
    break;
  }
}

