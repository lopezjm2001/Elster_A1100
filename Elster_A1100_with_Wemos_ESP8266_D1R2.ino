/*
  This project uses a Wemos ESP8266 D1R2 from ebay http://www.ebay.com.au/itm/WeMos-D1-R2-Latest-ESP-12E-WiFi-ESP8266-Board-Arduino-IDE-Uno-SYDNEY/272385909659?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649
  This project is based on https://pedrosnotes.wordpress.com/ which uses an Arduino UNO.
  This project uses a Wemos ESP8266 D1R2 which is Arduino compatible and has WIFI which can be used to 
  upload the Elster A1100 data to www.pvoutput.org. 
  This code has been tested with a Wemos ESP8266 D1R2 wiring a comercial infrared sesor RPM7138-R from Jaycar Cat.No. ZD1952.
  It will print to to the serial port just when it detects a change
  in Total Imports, Total exports or a change in direction (0=Importing , 1=Exporting)
  The code will not work unless 12v is connected to the power jack (9v - 24V) as the serial microUSB cable can 
  only supply 3.3v to the Wemos ESP8266 D1R2 and the RPM7138-R is a 5v device.
  I have tried some IR sensors so far the only one working at the moment is the RPM7138-R which is a 5v device.

  Based on Dave's code to read an elter a100c for more info on that vist:
  http://www.rotwang.co.uk/projects/meter.html
  Thanks Dave.
*/
#define BIT_PERIOD 860      //860 us
#define BUFF_SIZE 64
volatile long data[BUFF_SIZE];
volatile uint8_t in;
volatile uint8_t out;
volatile unsigned long last_us;
uint8_t dbug = 1;


void onPulse() {
  unsigned long us = micros();
  unsigned long diff = us - last_us;
  if (diff > 20 ) {
    last_us = us;
    int next = in + 1;
    if (next >= BUFF_SIZE) next = 0;
    data[in] = diff;
    in = next;
  }
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(0), onPulse, RISING); // D3 = GPIO 0
  Serial.begin(115200);
  if (dbug) Serial.print("Start ........\r\n");
  last_us = micros();
}

unsigned int statusFlag;
float imports;
float exports;

void loop() {
  int rd = decode_buff();
  if (!rd) return;
  if (rd == 3) {
    rd = 4;
    Serial.println("");
    Serial.print("Total Import: ");
    Serial.print(imports);
    Serial.println(" kWh");
    Serial.print("Total Export: ");
    Serial.print(exports);
    Serial.println(" kWh");
    Serial.print("Flag: ");
    if (statusFlag == 1) Serial.println("Exporting");
    if (statusFlag == 0) Serial.println("Importing");
  }
}

float last_data;
uint8_t sFlag;
float imps;
float exps;
uint16_t idx = 0;
uint8_t byt_msg = 0;
uint8_t bit_left = 0;
uint8_t bit_shft = 0;
uint8_t pSum = 0;
uint16_t BCC = 0;
uint8_t eom = 1;

static int decode_buff(void) {
  if (in == out) return 0;
  int next = out + 1;
  if (next >= BUFF_SIZE) next = 0;
  int p = (((data[out]) + (BIT_PERIOD / 2)) / BIT_PERIOD);
//  if (dbug) { Serial.print(data[out]); Serial.print(" "); if (p>500) Serial.println("<-"); }  
  if (p > 500) {
    idx = BCC = eom = imps = exps = sFlag = 0;
    out = next;
    return 0;
  }
  bit_left = (4 - (pSum % 5));
  bit_shft = (bit_left < p) ? bit_left : p;
  pSum = (pSum == 10) ? p : ((pSum + p > 10) ? 10 : pSum + p);
  if (eom == 2 && pSum >= 7) {
    pSum = pSum == 7 ? 11 : 10;
    eom = 0;
  }

  if (bit_shft > 0) {
    byt_msg >>= bit_shft;
    if (p == 2) byt_msg += 0x40 << (p - bit_shft);
    if (p == 3) byt_msg += 0x60 << (p - bit_shft);
    if (p == 4) byt_msg += 0x70 << (p - bit_shft);
    if (p >= 5) byt_msg += 0xF0;
  }
  if (pSum >= 10) {
    idx++;
    if (idx != 328) BCC = (BCC + byt_msg) & 255;
    if (dbug) Serial.print("["); Serial.print(idx); Serial.print(":"); Serial.print(byt_msg, HEX); Serial.print("]");
    if (idx >= 95 && idx <= 101)
      imps += ((float)byt_msg - 48) * pow(10 , (101 - idx));
    if (idx == 103)
      imps += ((float)byt_msg - 48) / 10;
    if (idx >= 114 && idx <= 120)
      exps += ((float)byt_msg - 48) * pow(10 , (120 - idx));
    if (idx == 122)
      exps += ((float)byt_msg - 48) / 10;
    if (idx == 210)
      sFlag = (byt_msg - 48) >> 3; //1=Exporting ; 0=Importing
    if (byt_msg == 3) eom = 2;
    if (idx == 328) {
      if ((byt_msg >> (pSum == 10 ? (((~BCC) & 0b1000000) ? 0 : 1) : 2)) == ((~BCC) & 0x7F)) {
       // if (last_data != (imps + exps + sFlag)) {
          imports = imps;
          exports = exps;
          statusFlag = sFlag;
          last_data = imps + exps + sFlag;
          out = next;
          return 3;
       // }
      }
    }
  }
  out = next;
  return 0;
}
