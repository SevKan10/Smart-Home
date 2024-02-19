void printTime() 
{
  lcd.setCursor(0,0);
  lcd.print(now.day(),DEC); lcd.print("/"); lcd.print(now.month(),DEC); lcd.print("/"); lcd.print(now.year(),DEC); lcd.print("|");
  
  lcd.setCursor(10,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);

  lcd.setCursor(0,1);
  lcd.print(now.hour(),DEC); lcd.print(":"); lcd.print(now.minute(),DEC); lcd.print(":"); lcd.print(now.second(),DEC); lcd.print("   ");

  if(now.hour() != currentHour)
  {
    Ring(2,100);
    currentHour = now.hour();
  }
}

void turnOnOffDevice(int hourOn, int minuteOn, int hourOff, int minuteOff)
{
  if(now.hour() == hourOn && now.minute() == minuteOn)
  {
    Ring(1,100);

    digitalWrite(LIGHT1, 1);
    digitalWrite(LIGHT2, 1);
  }
  else if(now.hour() == hourOff && now.minute() == minuteOff)
  {
    Ring(1,100);

    digitalWrite(LIGHT1, 0);
    digitalWrite(LIGHT2, 0);
  }
}

void settingTime()
{
  lcd.setCursor(0, 0);
  lcd.print("SET TIMER");
  lcd.setCursor(0, 1);
  lcd.print("Hour: " + String(h));

  static bool plusState = 1;
  bool currentPlus = digitalRead(PLUS);
  if (currentPlus == 0 && plusState == 1) 
  {
    Ring(1,50);
    h++;

    if(h>23){h = 0;}
    plusState = currentPlus;
  }

}




