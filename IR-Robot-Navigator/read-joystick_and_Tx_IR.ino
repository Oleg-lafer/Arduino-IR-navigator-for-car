#define joyX A2
#define joyY A0
#include <IRremote.h>

const int levels = 1040/15;
IRsend irsend;

void setup() {
  Serial.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int RVx = analogRead(joyX);
  int RVy = analogRead(joyY);
 
  int xTx = RVx/levels;
  int yTx = RVy/levels;

  int hexTx = xTx + yTx*16;

  irsend.sendSony(hexTx, 12);
  
    //print the values with to plot or view
  Serial.print("RVx: " + String(RVx) + " x: " + String(xTx));
  Serial.print("  RVy: " + String(RVy) + " y: " + String(yTx));

  Serial.print("   TX: ");
  Serial.print(hexTx, HEX);

  Serial.println("");
  delay(250);
}
