void printTime() 
{
  lcd.setCursor(0,0);
  lcd.print(now.day(),DEC); lcd.print("/"); lcd.print(now.month(),DEC); lcd.print("/"); lcd.print(now.year(),DEC); lcd.print("|");
  
  lcd.setCursor(10,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);

  lcd.setCursor(0,1);
  lcd.print(now.hour(),DEC); lcd.print(":"); lcd.print(now.minute(),DEC); lcd.print(":"); lcd.print(now.second(),DEC); lcd.print("   ");

  lcd.setCursor(10,1);
  lcd.print(">MENU<");
  if(now.hour() != currentHour){Ring(2,100); currentHour = now.hour();}
}

void turnOnOffDevice(int hourOn, int minuteOn, int hourOff, int minuteOff)
{
  if(now.hour() == hourOn && now.minute() == minuteOn) //&& now.hour() < hourOff && now.minute() < minuteOff
  {
    // Ring(1,100);
    digitalWrite(LIGHT1, 1);
    digitalWrite(LIGHT2, 1);
  }
  else if(now.hour() == hourOff && now.minute() == minuteOff) //&& now.hour() < hourOn && now.minute() < minuteOn
  {
    // Ring(1,100);
    digitalWrite(LIGHT1, 0);
    digitalWrite(LIGHT2, 0);
  }
}

void selectMode() 
{
  static bool staMenu = 1;
  if (digitalRead(MENU) == 0 && staMenu == 1) {Ring(1,50); flag=0;}
  staMenu = digitalRead(MENU);

  static bool staSelect = 1;
  bool currentSelect = digitalRead(SEL);
  if (currentSelect == 0 && staSelect == 1) {
    Ring(1,50);
    flag2++;
    lcd.clear();
    delay(50);
    if (flag2 > 2) { flag2=1; }
  }
  switch (flag2) 
  {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("<Back");
      lcd.setCursor(6,0);
      lcd.print(" CUSTOM");
      lcd.setCursor(0,1);
      lcd.print("      >DEFAULT<  ");
      static bool staAcc1 = 1;
      if (digitalRead(ACC) == 0 && staAcc1 == 1) 
      {
        Ring(1,500);
        for (int i = 0; i < 9; ++i) {EEPROM.write(i, 0);}
        delay(100);

        a[0] = 17; a[2] = 6;
        a[1] = 30; a[3] = 30;
        hOn = a[0]; hOff = a[2]; 
        mOn = a[1]; mOff = a[3];
        for (int i = 0; i < 4; i++) 
        {
          EEPROM.write(i, a[i]);
          delay(100);
        }
        EEPROM.commit();
        delay(100);
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("SET TIME");
        lcd.setCursor(3,1);
        lcd.print("COMPLETED");
        delay(3000);
        lcd.clear();
        flag = 0;
      }
      staAcc1 = digitalRead(ACC);
    break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("<Back");
      lcd.setCursor(6, 0);
      lcd.print(">CUSTOM<");
      lcd.setCursor(0,1);
      lcd.print("       DEFAULT  ");
      static bool staAcc2 = 1;
      if (digitalRead(ACC) == 0 && staAcc2 == 1){ Ring(1,500); delay(100); lcd.clear(); flag2=3;}
      staAcc2 = digitalRead(ACC);
    break;

    case 3: settingTime(); break;
  }
  staSelect = currentSelect;
}
void settingTime()
{
  int i2 = 4; int i3 = 10; int i4 = 13;
  lcd.setCursor(0,0);
  lcd.print("<Back");
  lcd.setCursor(6, 0);
  lcd.print("SET TIME");
  lcd.setCursor(1, 1);
  lcd.print(hOn); lcd.print(" "); lcd.print(":"); lcd.print(mOn); lcd.print(" ");
  lcd.setCursor(7,1);
  lcd.print("|"); 
  lcd.setCursor(10,1);
  lcd.print(hOff); lcd.print(" "); lcd.print(":"); lcd.print(mOff); lcd.print(" ");

  static bool staMenu = 1;
  if (digitalRead(MENU) == 0 && staMenu == 1) {lcd.clear(); Ring(1,50); flag=1; flag2=1;}
  staMenu = digitalRead(MENU);

  static bool staSw = 1;
  if(digitalRead(SW) == 0 && staSw == 1)
  { 
    Ring(1,50);
    flag1++;
    lcd.clear();
    delay(50);
    if(flag1>4){flag1=1;}
  }
  staSw = digitalRead(SW);

  switch(flag1)
  {
    case 1:
      lcd.setCursor(1,1);
      lcd.write(1);
      //blinkCursor(300);
      if (digitalRead(PLUS) == 0) 
      {
        Ring(1,50);
        hOn++;
        if(hOn>23){hOn = 0;}
        delay(50);
      }
/*-------------PLUS HOUR ON-------------*/
      if (digitalRead(MINUS) == 0) 
      {
        Ring(1,50);
        hOn--;
        if(hOn<0){hOn = 23;}
        delay(50);
      }
/*------------MINUS HOUR ON------------*/
    break;

    case 2:
      if(hOn>=10){i2=i2+1;}
      else{i2=4;}
      lcd.setCursor(i2,1);
      lcd.write(1);
      //blinkCursor(300);
      if (digitalRead(PLUS) == 0) 
      {
        Ring(1,50);
        mOn++;
        if(mOn>59){mOn = 0;}
        delay(50);
      }
/*-------------PLUS MINUTE ON-------------*/
      if (digitalRead(MINUS) == 0) 
      {
        Ring(1,50);
        mOn--;
        if(mOn<0){mOn = 59;}
        delay(50);
      }
/*------------MINUS MINUTE ON------------*/
    break;

    case 3:
      lcd.setCursor(i3,1);
      lcd.write(1);
      //blinkCursor(300);
      if (digitalRead(PLUS) == 0) 
      {
        Ring(1,50);
        hOff++;
        if(hOff>23){hOff = 0;}
        delay(50);
      }
/*-------------PLUS HOUR OFF-------------*/
      if (digitalRead(MINUS) == 0) 
      {
        Ring(1,50);
        hOff--;
        if(hOff<0){hOff = 23;}
        delay(50);
      }
/*------------MINUS HOUR OFF------------*/
    break;

    case 4:
      if(hOff>=10){i4=i4+1;}
      else{i4=13;}
      lcd.setCursor(i4,1);
      lcd.write(1);
      //blinkCursor(300);
      if (digitalRead(PLUS) == 0) 
      {
        Ring(1,50);
        mOff++;
        if(mOff>59){mOff = 0;}
        delay(50);
      }
/*-------------PLUS MINUTE OFF-------------*/
      if (digitalRead(MINUS) == 0) 
      {
        Ring(1,50);
        mOff--;
        if(mOff<0){mOff = 59;}
        delay(50);
      }
/*------------MINUS MINUTE OFF------------*/
    break;
  }
  static bool staAcc = 1;
  if (digitalRead(ACC) == 0 && staAcc == 1)
  {
    if (hOn >= 0 && hOn <= 23 && mOn >= 0 && mOn <= 59 && hOff >= 0 && hOff <= 23 && mOff >= 0 && mOff <= 59) 
    {
      Ring(1,500);
      for (int i = 0; i < 9; ++i){EEPROM.write(i, 0);} delay(100);
      
      Serial.print(hOn); Serial.print("\t");
      Serial.print(mOn); Serial.print("\t");
      Serial.print(hOff); Serial.print("\t");
      Serial.println(mOff);

      a[0] = hOn;  a[1] = mOn;
      a[2] = hOff; a[3] = mOff;
      for (int i = 0; i<4; i++)
      {
        EEPROM.write(i, a[i]);
        delay(100);
      }
      EEPROM.commit();
      delay(100);
      Serial.println("DATA SAVE SUCCESS");
    } 
    else {Serial.println("DATA SAVE FAILED");} //Check error

    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("SET TIME");
    lcd.setCursor(3,1);
    lcd.print("COMPLETED");
    delay(3000);
    lcd.clear();
    flag = 0;
    flag2 = 1;
   }
   staAcc = digitalRead(ACC);
/*------------ACCEPT SET TIME------------*/
}