#define BLYNK_TEMPLATE_ID "TMPL6XAznY3Lo"
#define BLYNK_TEMPLATE_NAME "SMART HOME"
#define BLYNK_AUTH_TOKEN "DTN0jSU9VzT6GvEJr8ULeTh4nWK8ChY1"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <string.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MINH KHA";
char pass[] = "0855508877";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  Blynk.virtualWrite(V5, 17);
  delay(2000);
}
// BLYNK_WRITE(V2) {int relayState = param.asInt(); digitalWrite(LIGHT1, relayState);}
// BLYNK_WRITE(V3) {hOn = param.asInt();}
// BLYNK_WRITE(V4) {mOn = param.asInt();}
// BLYNK_WRITE(V6) {hOff = param.asInt();}
// BLYNK_WRITE(V7) {mOff = param.asInt();}