#define R1 13
#define R2 12
#define R3 14
#define R4 27
#define R5 26
#define R6 25
#define R7 33 
#define R8 32

void setup() {

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);

}

void loop() {

  digitalWrite(R1, 1); delay(50);
  digitalWrite(R2, 1); delay(50);
  digitalWrite(R3, 1); delay(50);
  digitalWrite(R4, 1); delay(50);
  digitalWrite(R5, 1); delay(50);
  digitalWrite(R6, 1); delay(50);
  digitalWrite(R7, 1); delay(50);
  digitalWrite(R8, 1); delay(50);

  delay(2000);
  digitalWrite(R1, 0); delay(50);
  digitalWrite(R2, 0); delay(50);
  digitalWrite(R3, 0); delay(50);
  digitalWrite(R4, 0); delay(50);
  digitalWrite(R5, 0); delay(50);
  digitalWrite(R6, 0); delay(50);
  digitalWrite(R7, 0); delay(50);
  digitalWrite(R8, 0); delay(50);

  delay(2000);
  digitalWrite(R1, 1); delay(50);
  digitalWrite(R2, 0); delay(50);
  digitalWrite(R3, 1); delay(50);
  digitalWrite(R4, 0); delay(50);
  digitalWrite(R5, 1); delay(50);
  digitalWrite(R6, 0); delay(50);
  digitalWrite(R7, 1); delay(50);
  digitalWrite(R8, 0); delay(50);

  delay(2000);
  digitalWrite(R1, 0); delay(50);
  digitalWrite(R2, 1); delay(50);
  digitalWrite(R3, 0); delay(50);
  digitalWrite(R4, 1); delay(50);
  digitalWrite(R5, 0); delay(50);
  digitalWrite(R6, 1); delay(50);
  digitalWrite(R7, 0); delay(50);
  digitalWrite(R8, 1); delay(50);

  delay(2000);
  digitalWrite(R1, 1); delay(50);   digitalWrite(R1, 0); delay(50);
  digitalWrite(R2, 1); delay(50);   digitalWrite(R2, 0); delay(50);
  digitalWrite(R3, 1); delay(50);   digitalWrite(R3, 0); delay(50);
  digitalWrite(R4, 1); delay(50);   digitalWrite(R4, 0); delay(50);
  digitalWrite(R5, 1); delay(50);   digitalWrite(R5, 0); delay(50);
  digitalWrite(R6, 1); delay(50);   digitalWrite(R6, 0); delay(50);
  digitalWrite(R7, 1); delay(50);   digitalWrite(R7, 0); delay(50);
  digitalWrite(R8, 1); delay(50);   digitalWrite(R8, 0); delay(50);
  delay(2000);
}
