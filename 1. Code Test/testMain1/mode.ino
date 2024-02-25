void selectMode()
{
  static bool staMenu = 1;
  if (digitalRead(MENU) == 0 && staMenu == 1) {Ring(1,50); flagMenu=0;}
  staMenu = digitalRead(MENU);

 static bool staSelectMode = 1;
  if (digitalRead(SEL) == 0 && staSelectMode == 1) {
    Ring(1,50);
    flagMode++;
    lcd.clear();
    delay(50);
    if (flagMode > 2) { flagMode=1; }
  }
  staSelectMode = digitalRead(SEL);
  switch (flagMode)
  {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("<Back");
      lcd.setCursor(6,0);
      lcd.print(" ADMIN ");
      lcd.setCursor(6,1);
      lcd.print(">SET TIME<");
      static bool staAcc1 = 1;
      if (digitalRead(ACC) == 0 && staAcc1 == 1) 
      {
        Ring(1,500);
        lcd.clear();
        flagMode=3;
      }
      staAcc1 = digitalRead(ACC);
    break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("<Back");
      lcd.setCursor(6,0);
      lcd.print(">ADMIN<");
      lcd.setCursor(6,1);
      lcd.print(" SET TIME ");
      static bool staAcc2 = 1;
      if (digitalRead(ACC) == 0 && staAcc2 == 1) 
      {
        Ring(1,500);
        lcd.clear();
        flagMode=4;
      }
      staAcc2 = digitalRead(ACC);
    break;

    case 3:
     selectModeTime();
    break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("setting admin");
    break;
  }

}