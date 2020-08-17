#include"LCD.h"
#include"instructions.h"

bool wireState = true;
//////////############### public ###############///////////

lcd::lcd(byte test_byte) {
  deviceAddress = test_byte;
  if(wireState){
    Wire.begin();
    wireState = false;
  }
}

void lcd::initiate(byte test_byte1, byte test_byte2){//think about the test_byte1
  isDeviceOn = true;
  _backlight_state = true;
  displayLine = test_byte2;
  Wire.beginTransmission(deviceAddress);
  Wire.write(8);
  Wire.endTransmission();
  delayMicroseconds(100);          //A crude Practice of delay, I don't think it's necessary
  _initial_instruction(test_byte2);
}

void lcd::endDisplay(){
  isDeviceOn = false;
  Wire.end();
}

void lcd::show(char letter){
  //_send_instruction(_set_instruction(letter, H_BIT, RR));
  //_send_instruction(_set_instruction(letter, L_BIT, RR));
  _send_message(letter);
}

void lcd::showMessage(char *message){
  byte count = _message_length(message);
  if(count > 32){
    count = 32;
  }
  for(byte bt = 0; bt < count; bt++){
    //showMessage(message[bt]);//Which is better?
    //_send_instruction(_set_instruction(message[bt], H_BIT, RR));
    //_send_instruction(_set_instruction(message[bt], L_BIT, RR));
    _send_message(message[bt]);
  }
}

void lcd::showMessage(float value, char * message){
  int i = value;
  int j = (value - i) * 1000;
  char buf[16];
  //String string1 = String(value, decimalPlaces);
  sprintf(buf, "%i.%.3i %s", i, j, message);
  //Serial.begin(9600);
  //Serial.println(buf);
  showMessage(buf);
}

void lcd::showMessage(int value, char * message){
  char buf[16];
  sprintf(buf, "%i %s", value, message);
  showMessage(buf);
}

void lcd::cleanDisplay(){
  //_send_instruction(_set_instruction(CD, H_BIT, RS));
  //_send_instruction(_set_instruction(CD, L_BIT, RS));
  _send_instructions(CD);
  delayMicroseconds(10000);
}

void lcd::returnHome(){
  //_send_instruction(_set_instruction(RH, H_BIT, RS));
  //_send_instruction(_set_instruction(RH, L_BIT, RS));
  _send_instructions(RH);
  delayMicroseconds(1000);
}

void lcd::entryMode(byte cursor_address, byte shift_movement){
  switch(cursor_address | shift_movement){
    case 3:
          //_send_instruction(_set_instruction(EMS_I_S, H_BIT, RS));
          //_send_instruction(_set_instruction(EMS_I_S, L_BIT, RS));
          _send_instructions(EMS_I_S);
          break;
    case 2:
          //_send_instruction(_set_instruction(EMS_I_N, H_BIT, RS));
          //_send_instruction(_set_instruction(EMS_I_N, L_BIT, RS));
          _send_instructions(EMS_I_N);
          break;
  }
}

void lcd::displayControl(byte cursor_status, byte blink_status){
  switch(cursor_status | blink_status){
    case 3:
          //_send_instruction(_set_instruction(DC_D_C_B, H_BIT, RS));
          //_send_instruction(_set_instruction(DC_D_C_B, L_BIT, RS));
          _send_instructions(DC_D_C_B);
          break;
    case 2:
          //_send_instruction(_set_instruction(DC_D_C_N, H_BIT, RS));
          //_send_instruction(_set_instruction(DC_D_C_N, L_BIT, RS));
          _send_instructions(DC_D_C_N);
          break;
    case 1:
          //_send_instruction(_set_instruction(DC_D_N_B, H_BIT, RS));
          //_send_instruction(_set_instruction(DC_D_N_B, L_BIT, RS));
          _send_instructions(DC_D_N_B);
          break;
    case 0:
          //_send_instruction(_set_instruction(DC_D_N_N, H_BIT, RS));
          //_send_instruction(_set_instruction(DC_D_N_N, L_BIT, RS));
          _send_instructions(DC_D_N_N);
          break;
  }
}

void lcd::cursorShift(byte movement, byte times){
  for(int i = 0; i < times; i++){
    _cursor_shift(movement);
  }
}

void lcd::cursorShift(byte movement){
  _cursor_shift(movement);
}

void lcd::displayShift(byte movement, byte times){
  for(int i = 0; i < times; i++){
    _display_shift(movement);
  }
}
void lcd::displayShift(byte movement){
  _display_shift(movement);
}

void lcd::bringCursor(byte line, byte no){
  byte ddAddress;
  if(displayLine == 2){
    ddAddress = line * 0x40 + no;
    //_send_instruction(_set_instruction((SDDRAMA | ddAddress), H_BIT, RS));
    //_send_instruction(_set_instruction((SDDRAMA | ddAddress), L_BIT, RS));
    _send_instructions((SDDRAMA | ddAddress));
  }
  else if(displayLine == 1){
    ddAddress = no;
    //_send_instruction(_set_instruction((SDDRAMA | ddAddress), H_BIT, RS));
    //_send_instruction(_set_instruction((SDDRAMA | ddAddress), L_BIT, RS));
    _send_instructions((SDDRAMA | ddAddress));
  }
}
//////////############ private ################//////////

byte lcd::_set_instruction(byte instruction, byte state, byte registerSelect){
  byte data_register = 0;
  if(state == 1) data_register = (instruction & B11110000) | (_backlight_state << 3) | registerSelect;
  else if(state == 0) data_register = (instruction << 4) | (_backlight_state << 3) |registerSelect;
  return data_register;
}

void lcd::_send_instruction(byte data){
  Wire.beginTransmission(deviceAddress);
  Wire.write(data);
  Wire.write(data | 4);
  Wire.write(data);
  Wire.endTransmission();
}

void lcd::_send_instructions(byte data){
  _send_instruction(_set_instruction(data, H_BIT, RS));
  _send_instruction(_set_instruction(data, L_BIT, RS));
}

void lcd::_send_message(byte data){
  _send_instruction(_set_instruction(data, H_BIT, RR));
  _send_instruction(_set_instruction(data, L_BIT, RR));
}

void lcd::_initial_instruction(byte line){
  if(line == 2){
    _reset();
    _send_instruction(_set_instruction(FS_DLL_NH_FL, H_BIT, RS));
    //_send_instruction(_set_instruction(FS_DLL_NH_FL, H_BIT, RS));
    //_send_instruction(_set_instruction(FS_DLL_NH_FL, L_BIT, RS));
    _send_instructions(FS_DLL_NH_FL);
  }
  else if(line == 1){
    _reset();
    _send_instruction(_set_instruction(FS_DLL_NL_FL, H_BIT, RS));
    //_send_instruction(_set_instruction(FS_DLL_NL_FL, H_BIT, RS));
    //_send_instruction(_set_instruction(FS_DLL_NL_FL, L_BIT, RS));
    _send_instructions(FS_DLL_NL_FL);
  }
  //_send_instruction(_set_instruction(DC_D_C_N, H_BIT, RS));
  //_send_instruction(_set_instruction(DC_D_C_N, L_BIT, RS));
  displayControl(CURSOR_ON, BLINK_OFF);
  //_send_instruction(_set_instruction(EMS_I_N, H_BIT, RS));
  //_send_instruction(_set_instruction(EMS_I_N, L_BIT, RS));
  entryMode(INCREMENT, NO_SHIFT);
  //_send_instruction(_set_instruction(CD, H_BIT, RS));
  //_send_instruction(_set_instruction(CD, L_BIT, RS));
  cleanDisplay();
  delayMicroseconds(10000);
}

byte lcd::_message_length(char *message){
  int i = 0;
  while(message[i] != '\0'){
    i++;
  }
  return (byte)i; 
}

void lcd::_reset(){
    _send_instruction(_set_instruction(FS_DLH_NL_FL, H_BIT, RS));
    delayMicroseconds(4500);
    _send_instruction(_set_instruction(FS_DLH_NL_FL, H_BIT, RS));
    delayMicroseconds(4500);
    _send_instruction(_set_instruction(FS_DLH_NL_FL, H_BIT, RS));
    delayMicroseconds(150);
    _send_instruction(_set_instruction(FS_DLH_NL_FL, H_BIT, RS));
}

void lcd::_cursor_shift(byte movement){
  switch(movement){
    case 1:
          //_send_instruction(_set_instruction(CDS_C_R, H_BIT, RS));
          //_send_instruction(_set_instruction(CDS_C_R, L_BIT, RS));
          _send_instructions(CDS_C_R);
          break;
    case 0:
          //_send_instruction(_set_instruction(CDS_C_L, H_BIT, RS));
          //_send_instruction(_set_instruction(CDS_C_L, L_BIT, RS));
          _send_instructions(CDS_C_L);
          break;
  }
}

void lcd::_display_shift(byte movement){
  switch(movement){
    case 1:
          //_send_instruction(_set_instruction(CDS_S_R, H_BIT, RS));
          //_send_instruction(_set_instruction(CDS_S_R, L_BIT, RS));
          _send_instructions(CDS_S_R);
          break;
    case 0:
          //_send_instruction(_set_instruction(CDS_S_L, H_BIT, RS));
          //_send_instruction(_set_instruction(CDS_S_L, L_BIT, RS));
          _send_instructions(CDS_S_L);
          break;
  }
}
