#ifdef _LCD_H_
#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

//////////  instructions  start //////////
#define CD 1                   //1. Clears entire display and sets DDRAM address 0 in address counter

#define RH 2                   //2. Sets DDRAM address 0 in address counter. Also returns display 
                               //from being shifted to original position. DDRAM contents remain unchanged.
#define EMS_I_S 7              //3. Sets cursor move direction and specifies display shift. 
#define EMS_I_N 6              //These operations are performed during data write and read
#define EMS_D_S 5
#define EMS_D_N 4

#define DC_D_C_B  15           //4. Sets entire display (D) on/off, cursor on/off (C), 
#define DC_D_C_N  14           //and blinking of cursor position character (B)
#define DC_D_N_B  13
#define DC_D_N_N  12
#define DC_N_C_B  11
#define DC_N_C_N  10
#define DC_N_N_B  9
#define DC_N_N_N  8

#define CDS_S_R 28             //5. Moves cursor and shifts display without changing DDRAM contents
#define CDS_S_L 24
#define CDS_C_R 20
#define CDS_C_L 16

#define FS_DLH_NH_FH  60       //6. Sets interface data length (DL), number of display 
#define FS_DLH_NH_FL  56       //lines (N), and character font (F)
#define FS_DLH_NL_FH  52
#define FS_DLH_NL_FL  48
#define FS_DLL_NH_FH  44
#define FS_DLL_NH_FL  40
#define FS_DLL_NL_FH  36
#define FS_DLL_NL_FL  32

#define SCGRAMA 64            //Sets CGRAM address. CGRAM data is sent and received after this setting

#define SDDRAMA 128           //Sets CGRAM address. DDRAM data is sent and received after this setting

#define RS  0                 //Register Select, Read/Write Signal
#define RR  1
#define RD  1
#define RW  0

#define H_BIT 1               //high/low order 4 bits for instruction data
#define L_BIT 0
//////////  instructions  stop  //////////
#endif
#endif
