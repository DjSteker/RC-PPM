
#define channel_number 6  //set the number of channels
#define sigPin 9  //set PPM signal output pin on the arduino
#define PPM_FrLen 20100//20500 //22500 //30000 //22500   28571  // 27000 set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 500 //562 //750  // 500 set the pulse length
//#define PPM_PulseSinc 30000  //set the pulse length Ch0
#define MultiplicadorIn 1  // 500 set the pulse length
#define clockMultiplier 2 // set this to 2 if you are using a 16MHz arduino, leave as 1 for an 8MHz arduino
//////////////////////////////////////////////////////////////////


int Ch1, Ch1_a, Ch1_b;
int Ch2, Ch2_a, Ch2_b;
int Ch3, Ch3_a, Ch3_b;
int Ch4, Ch4_a, Ch4_b;
int Ch5, Ch5_a, Ch5_b;
int Ch6, Ch6_a, Ch6_b;



int ppm[channel_number];

unsigned long lastRecvTime = 0;

/**************************************************/

void setup() {
  //Prescaler
  //ADPS2 - ADPS1 - ADPS0 - Division Factor
  //0        - 0       - 0        ->2
  //0        - 0       - 1        ->2
  //0        - 1       - 0        ->4
  //0        - 1       - 1        ->8
  //1        - 0       - 0        ->16
  //1        - 0       - 1        ->32
  //1        - 1       - 0        ->64
  //1        - 1       - 1        ->128
  bitWrite(ADCSRA, ADPS2, 0);
  bitWrite(ADCSRA, ADPS1, 0);
  bitWrite(ADCSRA, ADPS0, 1);
  //Serial.begin(19200);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  ppm[0] = 1;
  ppm[1] = 1;
  ppm[2] = 1;
  ppm[3] = 1;
  ppm[4] = 1;
  ppm[5] = 1;
  setupPPM();

}

/**************************************************/

void setupPPM() {
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, 0);  //set the PPM signal pin to the default state (off)

  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 50;  // compare match register (not very important, sets the timeout for the first interrupt)
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  //TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TCCR1B |= (1 << CS01);
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt


//TCCR0A = 0x00;  // Clock source: System Clock 
//TCCR0B = 0x04;  // Set 1024x prescaler - Clock value: 15.625 kHz - 16 ms max time 
//TCNT0 = 0x00; 
//OCR0A = 0x00;   // OC0x outputs: Disconnected 
//OCR0B = 0x00; 
//TIMSK0 = 0x00;    // Timer 1 interrupt disable 


  
  sei();
}

void loop() {
  
  RecivirDatos() ;
  lastRecvTime = millis();

  Ch1_b = Ch1_a;
  Ch2_b = Ch2_a;
  Ch3_b = Ch3_a;
  Ch4_b = Ch4_a;
  Ch5_b = Ch5_a;
  Ch6_b = Ch6_a;

  unsigned long now = millis();
  if ( now - lastRecvTime > 100 ) {
    // signal lost?
    Serial.print("no data");
  }
  //  Serial.print(ppm[1]); Serial.print(" ");
  //  Serial.print(ppm[2]); Serial.print(" ");
  //  Serial.print(ppm[3]); Serial.print(" ");
  //  Serial.print(ppm[4]); Serial.print(" ");
  //  Serial.print(ppm[5]); Serial.print(" ");
  //  Serial.println(Ch6);


}

/**************************************************/

void RecivirDatos() {
  Ch1_a = pulseIn(2, HIGH, 30000);
  if ((Ch1_a > 100) && (Ch1_b > 100)) {
    Ch1 = (Ch1_a + Ch1_b) / 2;
  }
  else if ((Ch1_a < 10) && (Ch1_b > 10) ) {
    Ch1 = Ch1_b;
  }
  else if (Ch1_a > 10) {
    Ch1 = Ch1_a;
  }
  else {
    Ch1 = 0;
  }
  ppm[0] = ((Ch1 - 900) * MultiplicadorIn) + 900;
  Ch2_a = pulseIn(3, HIGH, 30000);
  if ((Ch2_a > 100) && (Ch2_b > 100)) {
    Ch2 = (Ch2_a + Ch2_b) / 2;
  }
  else if ((Ch2_a < 10) && (Ch2_b > 10) ) {
    Ch2 = Ch2_b;
  }
  else if (Ch2_a > 10) {
    Ch2 = Ch2_a;
  }
  else {
    Ch2 = 0;
  }
  ppm[1] = ((Ch2 - 900) * MultiplicadorIn) + 900;
  Ch3_a = pulseIn(4, HIGH, 30000);
  if ((Ch3_a > 100) && (Ch3_b > 100)) {
    Ch3 = (Ch3_a + Ch3_b) / 2;
  }
  else if ((Ch3_a < 10) && (Ch3_b > 10) ) {
    Ch3 = Ch3_b;
  }
  else if (Ch3_a > 10) {
    Ch3 = Ch3_a;
  }
  else {
    Ch3 = 0;
  }
  ppm[2] = ((Ch3 - 900) * MultiplicadorIn) + 900;
  Ch4_a = pulseIn(5, HIGH, 30000);
  if ((Ch4_a > 100) && (Ch4_b > 100)) {
    Ch4 = (Ch4_a + Ch4_b) / 2;
  }
  else if ((Ch4_a < 10) && (Ch4_b > 10) ) {
    Ch4 = Ch4_b;
  }
  else if (Ch4_a > 10) {
    Ch4 = Ch4_a;
  }
  else {
    Ch4 = 0;
  }
  ppm[3] = ((Ch4 - 900) * MultiplicadorIn) + 900;
  Ch5_a = pulseIn(6, HIGH, 30000);
  if ((Ch5_a > 100) && (Ch5_b > 100)) {
    Ch5 = (Ch5_a + Ch5_b) / 2;
  }
  else if ((Ch5_a < 10) && (Ch5_b > 10) ) {
    Ch5 = Ch5_b;
  }
  else if (Ch5_a > 10) {
    Ch5 = Ch5_a;
  }
  else {
    Ch5 = 0;
  }
  ppm[4] = ((Ch5 - 900) * MultiplicadorIn) + 900;
  Ch6_a = pulseIn(7, HIGH, 30000);
  if ((Ch6_a > 100) && (Ch6_b > 100)) {
    Ch6 = (Ch6_a + Ch6_b) / 2;
  }
  else if ((Ch6_a < 10) && (Ch6_b > 10) ) {
    Ch6 = Ch6_b;
  }
  else if (Ch6_a > 10) {
    Ch6 = Ch6_a;
  }
  else {
    Ch6 = 0;
  }
  ppm[5] = ((Ch6 - 900) * MultiplicadorIn) + 900;
}

/**************************************************/

unsigned long UltimoPulso = 0;
unsigned long UltimoResto = 0;
ISR(TIMER1_COMPA_vect) {
  static boolean state = true;
  int SeparadorRetoca = 0;
  TCNT1 = 0;
  static byte cur_chan_numb;
  static unsigned int calc_rest;
  if ( state ) {
    digitalWrite(sigPin, 0);
    OCR1A = (PPM_PulseLen * clockMultiplier) ;//- SeparadorRetoca;
    state = false;
  }
  else {
    digitalWrite(sigPin, 1);
    state = true;
    UltimoPulso = micros();

    if (cur_chan_numb >= channel_number) {
      cur_chan_numb = 0;
      calc_rest += PPM_PulseLen;
      OCR1A = (PPM_FrLen - calc_rest) * clockMultiplier;
      UltimoResto = calc_rest;
      calc_rest = 0;
    }
    else {
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * clockMultiplier;
      calc_rest += ppm[cur_chan_numb];
      cur_chan_numb++;
    }

  }

}
