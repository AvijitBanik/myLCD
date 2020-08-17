#include"LCD.h"

//lcd is the class whose constractor takes the I2C address of the display divice
lcd display1(0x20); //lcd display2(0x27);  There may be more than one display device

void setup() {
  display1.initiate(16, 2); //The coloum and row number of the display, 
                            //like (16, 1) for single line display option
}

void loop() {
  static int i = 0;
  display1.showMessage("Hello World");  //the Message to be printed
  delay(1000);  //delay for the Message to be on the screen
  display1.bringCursor(1,0);  //the coordinates of cursor on screen for second line/row first coloum
  display1.showMessage(i, "is a number"); // showing the integers with message
  delay(1000);              //Similarly float can also be shown in the same way
  i++;                      //display1.showMessage((float)PI, "this is PI");
  display1.cleanDisplay();  //this code will clear the screen and set the cursor at (0,0)  
}