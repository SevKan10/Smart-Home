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



