void simCallSms()
{
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
  Ring(30,500);
  Serial2.print(F("ATH"));
  Serial2.print(F(";\r\n"));
  delay(500);
}