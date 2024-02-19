#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
RTC_DS1307 rtc;
DateTime now;

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

#include <EEPROM.h>

#define BUZ 2
#define LIGHT1 26
#define LIGHT2 25
#define MENU 15
#define PLUS 4
#define MINUS 5
#define SW 18

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur"};
int currentHour = -1;
int flag = 0, flag1 = 1;
int hOn = 0, mOn = 0, hOff = 0, mOff = 0;
int H1, H2, H3, H4;
unsigned long Time;
bool cursor = 1;

void setup() {
  Serial.begin(9600);     
  EEPROM.begin(16); 
  readEeprom(H1, H2, H3, H4);

  pinMode(BUZ, OUTPUT);
  pinMode(LIGHT1, OUTPUT);
  pinMode(LIGHT2, OUTPUT);
  pinMode(MENU, INPUT_PULLUP);
  pinMode(PLUS, INPUT_PULLUP);
  pinMode(MINUS, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  Wire.begin(23, 22);

  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  now = rtc.now();

  if (digitalRead(MENU) == 0) {
    Ring(1, 50);
    flag++;
    lcd.clear();
    delay(200);
    if (flag > 2) {
      flag = 0;
    }
  }

  switch (flag) {
    case 0:
      printTime();
      turnOnOffDevice(H1, H2, H3, H4);
      break;
    case 1:
      settingTime();
      break;
    case 2:
      flag = 0;
      break;
  }
}

void printTime() {
  lcd.setCursor(0, 0);
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  lcd.print("|");

  lcd.setCursor(10, 0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);

  lcd.setCursor(0, 1);
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC);
  lcd.print("   ");

  if (now.hour() != currentHour) {
    Ring(2, 100);
    currentHour = now.hour();
  }
}

void turnOnOffDevice(int hourOn, int minuteOn, int hourOff, int minuteOff) {
  if (now.hour() == hourOn && now.minute() == minuteOn) {
    digitalWrite(LIGHT1, 1);
    digitalWrite(LIGHT2, 1);
  } else if (now.hour() == hourOff && now.minute() == minuteOff) {
    digitalWrite(LIGHT1, 0);
    digitalWrite(LIGHT2, 0);
  }
}

void settingTime() {
  int i2 = 3;
  int i3 = 6;
  int i4 = 9;
  lcd.setCursor(3, 0);
  lcd.print("SET TIMER:");
  lcd.setCursor(0, 1);
  lcd.print(String(hOn));
  lcd.print(" ");
  lcd.print(":");
  lcd.print(mOn);
  lcd.print(" ");
  lcd.print("|");
  lcd.print(String(hOff));
  lcd.print(" ");
  lcd.print(":");
  lcd.print(mOff);
  lcd.print(" ");
  if (digitalRead(SW) == 0) {
    Ring(1, 50);
    flag1++;
    lcd.clear();
    delay(50);
    if (flag1 > 4) {
      flag1 = 1;
    }
  }

  switch (flag1) {
    case 1:
      lcd.setCursor(0, 1);
      lcd.write(1);
      if (digitalRead(PLUS) == 0) {
        Ring(1, 50);
        hOn++;
        if (hOn > 23) {
          hOn = 0;
        }
        delay(50);
      }
      if (digitalRead(MINUS) == 0) {
        Ring(1, 50);
        hOn--;
        if (hOn < 0) {
          hOn = 23;
        }
        delay(50);
      }
      break;

    case 2:
      if (hOn >= 10) {
        i2 = i2 + 1;
      } else {
        i2 = 3;
      }
      lcd.setCursor(i2, 1);
      lcd.write(1);
      if (digitalRead(PLUS) == 0) {
        Ring(1, 50);
        mOn++;
        if (mOn > 60) {
          mOn = 0;
        }
        delay(50);
      }
      if (digitalRead(MINUS) == 0) {
        Ring(1, 50);
        mOn--;
        if (mOn < 0) {
          mOn = 60;
        }
        delay(50);
      }
      break;

    case 3:
      if (hOn >= 10 || mOn >= 10) {
        i3 = i3 + 1;
      } else if (hOn >= 10 && mOn >= 10) {
        i3 = i3 + 3;
      } else {
        i3 = 6;
      }
      lcd.setCursor(i3, 1);
      lcd.write(1);
      if (digitalRead(PLUS) == 0) {
        Ring(1, 50);
        hOff++;
        if (hOff > 23) {
          hOff = 0;
        }
        delay(50);
      }
      if (digitalRead(MINUS) == 0) {
        Ring(1, 50);
        hOff--;
        if (hOff < 0) {
          hOff = 23;
        }
        delay(50);
      }
      break;

    case 4:
      if (hOn >= 10 || mOn >= 10 || hOff >= 10) {
        i4 = i4 + 1;
      } else if (hOn >= 10 && mOn >= 10) {
        i4 = i4 + 3;
      } else if (hOn >= 10 && mOn >= 10 && hOff >= 10) {
        i4 = i4 + 4;
      } else {
        i4 = 9;
      }
      lcd.setCursor(i4, 1);
      lcd.write(1);
      if (digitalRead(PLUS) == 0) {
        Ring(1, 50);
        mOff++;
        if (mOff > 60) {
          mOff = 0;
        }
        delay(50);
      }
      if (digitalRead(MINUS) == 0) {
        Ring(1, 50);
        mOff--;
        if (mOff < 0) {
          mOff = 60;
        }
        delay(50);
      }
      break;
  }

  if (digitalRead(MENU) == 0) {
    if (millis() - Time >= 3000) {
      turnOnOffDevice(hOn, mOn, hOff, mOff);
      writeEeprom(hOn, mOn, hOff, mOff);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("SET TIME");
      lcd.setCursor(3, 1);
      lcd.print("COMPLETED");
      delay(2000);
      lcd.clear();
      flag = 0;
      Time = millis();
    }
  }
}

void writeEeprom(int HOn, int MOn, int HOff, int MOff) {
  EEPROM.write(1, HOn);
  EEPROM.write(2, MOn);
  EEPROM.write(3, HOff);
  EEPROM.write(4, MOff);
}

void readEeprom(int &HOn, int &MOn, int &HOff, int &MOff) {
  HOn = EEPROM.read(1);
  MOn = EEPROM.read(2);
  HOff = EEPROM.read(3);
  MOff = EEPROM.read(4);
}
void Ring(int repeat, int delays)
{
  for(int i=repeat; i>0; i--)
  {
    digitalWrite(BUZ,1); delay(delays); 
    digitalWrite(BUZ,0); delay(delays);
  }
}
