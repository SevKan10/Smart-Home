void Ring(int repeat, int delays)
{
  for(int i=repeat; i>0; i--)
  {
    digitalWrite(BUZ,1); delay(delays); 
    digitalWrite(BUZ,0); delay(delays);
  }
}

void blinkCursor(int time) {
  if (millis() - Time >= time) 
  {
    Time = millis();
    if (cursor){lcd.noCursor();} 
    else{lcd.cursor();}
    cursor = !cursor;
  }
}

void writeEeprom(int HOn, int MOn, int HOff, int MOff){
  EEPROM.write(1, HOn);
  EEPROM.write(2, MOn);
  EEPROM.write(3, HOff);
  EEPROM.write(4, MOff);
}

void readEeprom(int &HOn, int &MOn, int &HOff, int &MOff) {
  HOn = EEPROM.read(1);
  HOn = EEPROM.read(2);
  HOff = EEPROM.read(3);
  HOff = EEPROM.read(4);
}
