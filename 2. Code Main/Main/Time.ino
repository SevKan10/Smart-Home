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
      // Ring(1,100);

      digitalWrite(LIGHT1, 1);
      digitalWrite(LIGHT2, 1);
    }
    else if(now.hour() == hourOff && now.minute() == minuteOff)
    {
      // Ring(1,100);

      digitalWrite(LIGHT1, 0);
      digitalWrite(LIGHT2, 0);
    }
  }

  void settingTime()
  {
    int i2 = 4; int i3 = 10; int i4 = 13;
    lcd.setCursor(3, 0);
    lcd.print("SET TIMER:");
    lcd.setCursor(1, 1);
    lcd.print(hOn); lcd.print(" "); lcd.print(":"); lcd.print(mOn); lcd.print(" ");
    lcd.setCursor(7,1);
    lcd.print("|"); 
    lcd.setCursor(10,1);
    lcd.print(hOff); lcd.print(" "); lcd.print(":"); lcd.print(mOff); lcd.print(" ");



    if(digitalRead(SW) == 0)
    { 
      Ring(1,50);
      flag1++;
      lcd.clear();
      delay(50);
      if(flag1>4){flag1 = 1;}
    }
    
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
    if (digitalRead(ACC) == 0)
    {
      if (hOn >= 0 && hOn <= 23 && mOn >= 0 && mOn <= 59 && hOff >= 0 && hOff <= 23 && mOff >= 0 && mOff <= 59) 
      {
        for (int i = 0; i < 9; ++i){EEPROM.write(i, 0);} delay(100);
      
        Serial.print(hOn); Serial.print("\t");
        Serial.print(mOn); Serial.print("\t");
        Serial.print(hOff); Serial.print("\t");
        Serial.println(mOff);

        a[0] = hOn;
        a[1] = mOn;
        a[2] = hOff;
        a[3] = mOff;
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
    }
  }




