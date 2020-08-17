#ifndef _LCD_H_
#define _LCD_H_

#include<Wire.h>
#include<Arduino.h>

#define INCREMENT B10          //Entry Mode Control Macros
#define DECREMENT B00
#define SHIFT B1
#define NO_SHIFT  B0

#define CURSOR_ON B10          //display control settings
#define CURSOR_OFF  B00
#define BLINK_ON  B1
#define BLINK_OFF B0

#define RIGHT 1                //cursor display movement
#define LEFT  0

class lcd {
  public:
    lcd(byte);
    void initiate(byte,byte);
    void endDisplay();
    void show(char);
    void showMessage(char *);
    void showMessage(float,char *);
    void showMessage(int, char *);
    void cleanDisplay();
    void returnHome();
    void entryMode(byte,byte);
    void displayControl(byte,byte);
    void cursorShift(byte,byte);
    void cursorShift(byte);
    void displayShift(byte,byte);
    void displayShift(byte);
    void bringCursor(byte,byte);
    byte deviceAddress;
    bool isDeviceOn = false;
    byte displayLine;
    
  private:
    byte _set_instruction(byte,byte,byte);
    void _send_instruction(byte);
    void _send_instructions(byte);
    void _send_message(byte);
    void _initial_instruction(byte);
    byte _message_length(char *);
    void _reset();
    void _cursor_shift(byte);
    void _display_shift(byte);
    bool _backlight_state;
};

#endif
