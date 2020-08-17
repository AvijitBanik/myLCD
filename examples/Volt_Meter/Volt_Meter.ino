#include"LCD.h"
lcd display1(0x20);

void setup() { 
  display1.initiate(16, 2);
  display1.showMessage("Hello Avijit!");
  display1.bringCursor(1,0);
  display1.showMessage("Voltage_Meter->");
  delay(1000);
  display1.cleanDisplay();
  display1.showMessage("The Voltage is");
}

void loop() {
  display1.bringCursor(1,0);
  display1.showMessage((float)(analogRead(A0)/204.6), "volt");
  delay(250);
}
