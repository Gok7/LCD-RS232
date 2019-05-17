#include<18F97J60.h>
#DEVICE ADC=10
#use delay(clock=25M)
#fuses HS,NOWDT
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)
#include <string.h>
#include <stdlib.h>
#include "LCD_PicDemNet.C"

void main(){

char chaine_recu[30];
unsigned int valeur_led=0;

SET_TRIS_J(0x00);//en sortie
lcd_init();

	while(true){

		gets(chaine_recu);//recevoir une chaine de caractere entre 0 et 255
		//pour la fonction gets mettre 0x0D IMPERATIVEMENT
		valeur_led=atoi(chaine_recu);
		printf(lcd_putc,"\f %u",valeur_led);//LCD
		output_J(valeur_led);//LED
		delay_ms(100);
	}

}
