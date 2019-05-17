#include<18F97J60.h>
#DEVICE ADC=10
#use delay(clock=25M)
#fuses HS,NOWDT
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)
#include <string.h>
#include <stdlib.h>
#include "LCD_PicDemNet.C"
#DEFINE ENQ 5

void main(){

char recu;
unsigned int valeur_led=0;
int bouton=1;//si 0 alors appui,si 1 alors relaché
int entree=0;
int masque=0b00000011;
SET_TRIS_B(0xFF);//en entree
SET_TRIS_J(0x00);//en sortie
lcd_init();
// S3 = RB2 S4=RB3

	while(true){
		recu=getc();
		if(recu==ENQ){
		
			bouton=input_B();
			entree=masque&bouton;
		}

		switch (entree){
			case 0b00001011: printf(lcd_putc,"\f S3");
			break;
			case 0b00000111: printf(lcd_putc,"\f S4");
			break;
			default :printf(lcd_putc,"\fVeuillez appuyez\n");
			break;
		}	
		delay_ms(100);
		
	}

}
//a finir
