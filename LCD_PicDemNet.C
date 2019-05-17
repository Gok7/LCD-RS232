///////////////////////////////////////////////////////////////////////////
////                             LCD_PicDemNet.C   					   ////
////				          Modification par JBC                     ////
////                 Driver for common LCD modules                     ////
////                                                                   ////
////  lcd_init()   Must be called before any other function.           ////
////                                                                   ////
////  lcd_putc(c)  Will display c on the next position of the LCD.     ////
////                     The following have special meaning:           ////
////                      \f  Clear display                            ////
////                      \n  Go to start of second line               ////
////                      \b  Move back one position                   ////
////                                                                   ////
////  lcd_gotoxy(x,y) Set write position on LCD (upper left is 1,1)    ////
////                                                                   ////
////  lcd_getc(x,y)   Returns character at position x,y on LCD         ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2007 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////

// As defined in the following structure the pin connection is as follows:
//  H0    enable    
//  H2     rs		 
//  H1     rw
//  E0 à E7  D0 à D7 de l'afficheur

#bit rs=0xf87.2    //Port H
#bit rw=0xf87.1
#bit enable=0xf87.0

#locate Lcd_Data = 0xF84 //Port E

#define lcd_line_two 0x40    // LCD RAM address for the second line


BYTE lcd_read_byte() {
      BYTE ValeurLue;
      //set_tris_lcd(LCD_READ);
	  set_tris_H(0b11111000); //E, RS et RW en sortie
	  set_tris_E(0b11111111); // LCD en lecture	
      rw = 1;
      delay_cycles(1);
      enable = 1;
      delay_cycles(1);
      ValeurLue = Lcd_Data;
      enable = 0;
      set_tris_E(0b00000000); // LCD en écriture	
      return(ValeurLue);
}


void lcd_send_byte( BYTE address, BYTE n ) {

      rs = 0;
      while ( bit_test(lcd_read_byte(),7) ) ;
      rs = address;
      delay_cycles(1);
      rw = 0;
      delay_cycles(1);
      enable = 0;
	  Lcd_Data = n;
	  delay_cycles(1);
      enable = 1;
      delay_us(2);
      enable = 0;
      
}


void lcd_init() {//voir page 10/14 de 24_lcd_information
   
    set_tris_E(0b00000000); // LCD en écriture
    rs = 0;
    rw = 0;
    enable = 0;
    delay_ms(50);
	lcd_send_byte(0,0b00111100);
	delay_us(50);
	lcd_send_byte(0,0b00001100);
	delay_us(50);
	lcd_send_byte(0,0x01);
	delay_ms(2);
	lcd_send_byte(0,0b00000110);
	
	}


void lcd_gotoxy( BYTE x, BYTE y) {
   BYTE address;

   if(y!=1)
     address=lcd_line_two;
   else
     address=0;
   address+=x-1;
   lcd_send_byte(0,0x80|address);
}

void lcd_putc( char c) {
   switch (c) {
     case '\f'   : lcd_send_byte(0,1);
                   delay_ms(2);
                                           break;
     case '\n'   : lcd_gotoxy(1,2);        break;
     case '\b'   : lcd_send_byte(0,0x10);  break;
     default     : lcd_send_byte(1,c);     break;
   }
}

char lcd_getc( BYTE x, BYTE y) {
   char value;

    lcd_gotoxy(x,y);
    while ( bit_test(lcd_read_byte(),7) ); // wait until busy flag is low
    rs=1;
    value = lcd_read_byte();
    rs=0;
    return(value);
}
