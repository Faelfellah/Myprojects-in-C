/*
 ============================================================================
 Name        : ParkscheinAutomat.c
 Author      : Faris Elfellah

 Programm    : Das Programm soll die funktion eines Parkscheinautmats simulieren

 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
struct tm * ts;
unsigned int o_timeh,o_timem,c_timeh,c_timem; // globale Variablen für oeffnungszeiten
unsigned int entrance_timeh,entrance_timem,exit_timeh,exit_timem; // globale Variablen für Einfahrt und Ausfahrtzeiten
unsigned int parkzeit_h,parkzeit_m; // globale varibalen für die Parkzeit
float parkgebuehr,geld,egeld,geldneu; // Globale Variablen für die Zahlung

void init(); // Funktion für die Eingabe und Ausgabe der Oeffnungszeiten , keine rückgabe (void)
void timejetzt(); // Funktion für Ausgabe des Datums und Einfahrtzeit,keine rückgabe (void)
void ausfahrtzeit(); // Funktion für die Berechnung von Ausfahrtzeiten mithilfe des Zufallsgenerator,keine rückgabe (void)
void parkdauer(); // Fuktion für die Berechnung der Parkdauer,keine rückgabe (void)
int main(void){

	init();
	timejetzt();
	ausfahrtzeit();
	parkdauer();
	int k;
	float s10 = 0, s5 = 0, m2 = 0, m1 = 0,ctm50 = 0, ctm20 = 0, ctm10 = 0;
           if(parkzeit_h==0 && parkzeit_m<= 10){
        	printf("10min Konstenlos\n");
        }
           else if(parkzeit_h == 0 && parkzeit_m > 10 ){
    			parkgebuehr = 1.60;
    		}else if(parkzeit_h == 1){
    			parkgebuehr = 2.80;
    		}else if(parkzeit_h == 2){
    			parkgebuehr = 4.10;
    		}else for(k=0; k < parkzeit_h; k++){
    			parkgebuehr =  3.10 + k;
    		}
    	printf("Parkgebuehr:%0.2fEuro\n",parkgebuehr);
    	printf("Bitte Geld einwerfen:"); //erste Aufforderung fÃƒÂ¼r Geldeinwurf
    		scanf("%f", &geld);//Einlesen des Geldbetrages
    		if(geld>parkgebuehr || geld<parkgebuehr){
    			if(geld == 10){
    				s10 ++;
    			}if(geld ==5){
    				s5 ++;
    			}if(geld == 2){
    				m2 ++;
    			}if(geld == 1){
    				m1 ++;
    			}if(geld == 0.50){
    				ctm50 ++;
    			}if(geld == 0.20){
    				ctm20 ++;
    			}if(geld == 0.10){
    				ctm10 ++;
    			}
    		}
    		//geldneu = geld;
    			while(geld < parkgebuehr){ //Wenn nicht genÃƒÂ¼gend Geld eingeworfen wurde
    				printf("\n bitte der restlliche Betrag einwerfen:"); //Weitere Geldeinwurf Aufforderung
    				scanf("%f", &egeld);   //Einlesen des neu dazu  eingewofenen Gelbetrages
    				geld += egeld;
    				printf("\nEingeworfen:%0.2f Euro\n",geld);//Ausgabe des bisher eingeworfenen Geldbetrags

    					geldneu = egeld;
    						if(geldneu == 10){
    							s10 ++;
    						}else if(geldneu == 5){
    							s5 ++;
    						}else if(geldneu == 2){
    							m2 ++;
    						}else if(geldneu == 1){
    							m1 ++;
    						}else if(geldneu == 0.50){
    							ctm50 ++;
    						}else if(geldneu == 0.20){
    							ctm20 ++;
    						}else if(geldneu == 0.10){
    							ctm10 ++;
    						}
    			}
    		    printf("Datum :%02d.%02d.%04d\n",ts->tm_mday,ts->tm_mon+1,ts->tm_year+1900);
    		    printf("Einfahrtzeit:%02duhr%02dmin\n",entrance_timeh,entrance_timem);
    		    printf("Ausfahrtzeit:%duhr%dmin\n",exit_timeh,exit_timem);
    		    printf("Parkzeit:%02dh%02dmin\n",parkzeit_h,parkzeit_m);
    			printf("Gezahlt:%0.2fEuro(%1.0f:10Euro; %1.0f:5Euro; %1.0f:2Euro; %1.0f:1Euro; %1.0f:50Cent; %1.0f:20Cent; %1.0f:10Cent\n", geld, s10, s5, m2, m1, ctm50, ctm20, ctm10);
    			printf("Rueckgeld :%0.2f",geld - parkgebuehr);

    		}


void init(){
	printf("Parkschein Automat\n");
	printf("Oeffnungszeiten in (HH:MM) Format eingeben zwischen\n");
	printf("HH:");
	scanf("%d",&o_timeh);
	printf("MM:");
    scanf("%d",&o_timem);
	printf("HH:");
	scanf("%d",&c_timeh);
	printf("MM:");
	scanf("%d",&c_timem);
	printf("Das Parkhaus ist von %02duhr%02d bis %02duhr%02d geoeffnet.\n",o_timeh,o_timem,c_timeh,c_timem);

}
void timejetzt(){
	time_t t;
    t = time(NULL);
	ts = localtime(&t);
	printf("heutige Datum und Uhrzeit : %s", asctime(ts));
	time(&t);
	srand((unsigned int)t);
    entrance_timeh = ts->tm_hour;
    entrance_timem = ts->tm_min;
    if(entrance_timeh>6 && 24>entrance_timeh){
    printf("ParkHaus ist offen\n");

		    }
    else{
	printf("Parkhaus ist geschlossen\n");
		    }


}
void ausfahrtzeit(){

   exit_timeh = (rand() % (23 - entrance_timeh +1)) + entrance_timeh;
   exit_timem  = (rand() % (59 - entrance_timem +1)) + entrance_timem;
	printf("Ausfahrt  %02d:%02d \n", exit_timeh,exit_timem);

}
void parkdauer(){
	parkzeit_h = exit_timeh-entrance_timeh   ;
	parkzeit_m = exit_timem-entrance_timem ;
	printf("Parkdauer:%02dh%02dmin\n",parkzeit_h,parkzeit_m);

   }
