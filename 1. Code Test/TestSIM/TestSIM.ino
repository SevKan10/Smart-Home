String numberPhone = "";
void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  Serial2.println("AT+CMGF=1"); delay(50);
  Serial2.println("AT+CNMI=2,2,0,0,0"); delay(50);
  Serial2.println("AT+CMGL=\"REC UNREAD\""); delay(50);
  Serial2.println("AT+CMGD=1,4"); delay(50);

  Serial2.println("AT+CMGF=1");
  delay(500);
  Serial2.println("AT+CMGS=\"" + numberPhone + "\"\r");
  delay(500);
  Serial2.print("Help me!");
  Serial2.println((char)26);
  delay(5000);

  Serial2.print(F("ATD"));
  Serial2.print(numberPhone);
  Serial2.print(F(";\r\n"));
  ringCall();
  Serial2.print(F("ATH"));
  Serial2.print(F(";\r\n"));
  delay(500);
}

void loop() {
}
