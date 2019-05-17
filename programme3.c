#include<18F97J60.h>
#include <string.h>
#use delay(clock=25M)
#fuses HS,NOWDT
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)

char chaine_envoye[30];
char chaine_recu[30];
int i=0;
//A=65d   a=97d  faire+32 pour chaque caractere
//dans docklight mettre 0d=CR 0a=LFapres la chaine
//CR LF touche entree
void main(){

	while(true){
		
		gets(chaine_recu);
		//strcpy(chaine_recu,"Nicolas");
		for(i=0;i<strlen(chaine_recu);i++){
			
			chaine_envoye[i]=tolower(chaine_recu[i]);
		}
		puts(chaine_envoye);
	}

}
