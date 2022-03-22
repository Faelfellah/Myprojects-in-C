/*
 ============================================================================
 Name        : ZeichenCod.c
 Author      : Faris Elfellah
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 Programm    : Es sollen Worte beliebiger Länge bestehend aus Groß-  und Kleinbuchstaben sowie Zahlenwerten (Zeichen) codiert werden.
 Eingaben 	 : Wort beliebige Länge
 Ausgaben    : Das eingegebene Wort und dessen Codierung.
               Fehler Meldung falls nicht zulässige Zeichen eigegeben wurden.


 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40
int main(void) {
	char zeichen[MAX]; // variable für Zeichen und für die Eingabe
    int valid = 1; // valid Variable für die Fehler Behandlung


	printf("bitte Zeichenkette bestehend aus Zahlen oder Buchstaben eingeben\n");
	scanf("%s",zeichen);


	while (valid == 1) { // diesen Block hier für die Überprüfung ob  nicht zulässige Zeichen von der Tastatur eigelesen wurden

		for (int i = 0; i < strlen(zeichen); i++) { // führe den Block Bis die länge von der Zeichenkette erreicht wird
			if ((zeichen[i]>='A'&& zeichen[i]<='Z') || (zeichen[i]>='a'&& zeichen[i]<='z') || (zeichen[i]>='0'&& zeichen[i]<='9') ){
                 // wenn zulässige Zeichen eingelesen werden, nichts machen
			}
        	  else{ // sonst Fehler Meldung
        	  	printf ("An der Stelle %d taucht ein nicht zulaessige Zeichen auf \n",i+1);
        		  printf ("bitte neu eingeben \n");
        		  scanf("%s", zeichen);

        		  i=0; // i neu initiasieren
        	  }

          }

		valid=2;
	}

	for (int i=0;i<strlen(zeichen);i++){
		if (zeichen[i]>='A'&& zeichen[i]<='Z'){ // Wort Ausgeben
			printf ("%c",zeichen[i]);
		}
		else{

		if (((int)zeichen[i]%2)==0){ //  wenn zeichen einen geraden Zahlenwert haben
			zeichen[i]=(int)zeichen[i]/2; // Zahl durch zwei dividieren
			zeichen[i]=zeichen[i]-3; // und anschliessend 3 substrahieren
			if(zeichen[i]<32){  // wenn codierte Zahlenwert kleiner als 32 ist, 92 addieren
				zeichen[i]=zeichen[i]+92;
				printf ("%c",zeichen[i]); // Ausgabe
			}
			else{

			printf ("%c",zeichen[i]);
		    }
		}
		else { // sonst wenn der Zahlenwert ungerade ist
			zeichen[i]=(int)zeichen[i]+1; // 1 addieren
			zeichen[i]=zeichen[i]/2; // Ergebnis durch 2 teilen
			zeichen[i]=zeichen[i]-16; // Anschliessend 16 com Ergebnis abziehen
			if(zeichen[i]<32){   // wenn codierte Zahlenwert kleiner als 32 ist, 92 addieren
				zeichen[i]=zeichen[i]+92;
				printf ("%c",zeichen[i]); // Ausgabe
			}
			else
			printf ("%c",zeichen[i]);
		}
	}

	}

	return EXIT_SUCCESS;

}
