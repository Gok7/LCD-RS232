#include<18F97J60.h>
#use delay(clock=25M)
#fuses HS,NOWDT
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)

char car_envoye;
char car_recu;

void main(){

	while(true){
		
		car_recu=getc();
		car_envoye=car_recu+1;
		putc(car_envoye);
	}

}
