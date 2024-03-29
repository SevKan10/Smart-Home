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
#define BLYNK_TEMPLATE_ID "TMPL6XAznY3Lo"
#define BLYNK_TEMPLATE_NAME "SMART HOME"
#define BLYNK_AUTH_TOKEN "DTN0jSU9VzT6GvEJr8ULeTh4nWK8ChY1"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <string.h>
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
int flagMenu = 0, flagTime = 1, flagMode = 1;
int hOn, mOn, hOff, mOff;
unsigned long Time;
bool cursor = 1;
bool deviceOn;
String numberPhone = "";

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MINH KHA";
char pass[] = "0855508877";
/*=========VARIABLE==========*/

void setup() {

  Serial.begin(9600);     
  Blynk.begin(auth, ssid, pass);
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

  for(int i = 10; i >-1 ;i-- )
  {  
    lcd.setCursor(7,0);
    lcd.print(i);
    lcd.print(" ");
    lcd.setCursor(3,1);
    lcd.print("WATTING...");  
    delay(1000);
  }
  lcd.clear();
}

void loop() {
  now = rtc.now();
  Blynk.run();
  Blynk.virtualWrite(V5, 17);
  String timeOn = String(hOn) + ":" + String(mOn);
  String timeOff = String(hOff) + ":" + String(mOff);
  Blynk.virtualWrite(V0, timeOn);
  Blynk.virtualWrite(V1, timeOff);

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
    case 0: printTime(); flagMode=1; break;
    case 1: selectMode();            break;
    case 2: flagMenu=0;              break;
  }
}

BLYNK_WRITE(V2) {int relayState = param.asInt(); digitalWrite(LIGHT1, relayState);}
// BLYNK_WRITE(V3) {hOn = param.asInt();}
// BLYNK_WRITE(V4) {mOn = param.asInt();}
// BLYNK_WRITE(V6) {hOff = param.asInt();}
// BLYNK_WRITE(V7) {mOff = param.asInt();}