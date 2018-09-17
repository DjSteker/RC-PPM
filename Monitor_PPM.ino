void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(2, INPUT);
}

int Ch_a = 0 ;
int CanalSelect = 0 ;


void loop() {
  // put your main code here, to run repeatedly:
  Ch_a = pulseIn(2, LOW, 600);
  Serial.print(Ch_a); Serial.print(" - ");

  Start:
  Ch1();if (Ch_a < 10) {Serial.println("XXX"); goto Start;}
  Ch2();if (Ch_a < 10) {Serial.println("XXX"); goto Start;}
  Ch3();if (Ch_a < 10) {Serial.println("XXX"); goto Start;}
  Ch4();if (Ch_a < 10) {Serial.println("XXX"); goto Start;}
  Ch5();if (Ch_a < 10) {Serial.println("XXX"); goto Start;}
  Ch6();if (Ch_a < 10) {Serial.println("XXX"); goto Start;}
  ChCheck();
}
void Ch1() {
  Ch_a = pulseIn(2, HIGH, 4500);
  Serial.print(Ch_a); Serial.print(" ");
}
void Ch2() {
  Ch_a = pulseIn(2, HIGH, 4500);
  Serial.print(Ch_a); Serial.print(" ");
}
void Ch3() {
  Ch_a = pulseIn(2, HIGH, 4500);
  Serial.print(Ch_a); Serial.print(" ");
}
void Ch4() {
  Ch_a = pulseIn(2, HIGH, 4500);
  Serial.print(Ch_a); Serial.print(" ");
}
void Ch5() {
  Ch_a = pulseIn(2, HIGH, 4500);
  Serial.print(Ch_a); Serial.print(" ");
}
void Ch6() {
  Ch_a = pulseIn(2, HIGH, 4500);
  Serial.print(Ch_a); Serial.println(" ");
}
void ChCheck() {
  Ch_a = pulseIn(2, HIGH, 30000);
  Serial.print(Ch_a); Serial.println(" ");
}


