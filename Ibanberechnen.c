
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_FILILIALNAME 100
#define MAX_FILIALNAME_LEN_S "100"
#define MAX_KONTONMR 11
#define MAX_BLZ 9
#define IBAN_LAENGE 23
#define NIBAN_LAENGE 25

typedef enum{true,false}bool; // bool definieren


bool ueberpruefekontonmr(char* Kontonummer); // Die Funktion überprüft ob die kontonummer gültig ist. Parameter char* Kontonummer. Sie gibt ein bool zurück.
bool ueberpruefeblz(char BLZ[MAX_BLZ]);// // Die Funktion überprüft ob die Bankleitzahl gültig ist. Parameter char Kontonummer[MAX_KONTONMR]. Sie gibt ein bool zurück.
bool ueberpruefebankdaten(char Kontonummer[MAX_KONTONMR], char BLZ[MAX_BLZ]);
int berechnePp(char* Kontonummer, char* BLZ);// Die funktion berechnet Prüfziffer.Parameter char* Kontonummer, char* BLZ. Sie gibt ein Integer zurück.
char* IBANberechnen(char* IBAN, char* Kontonummer, char* BLZ); // Die Funktion berechnet IBAN. Parameter char* IBAN, char* Kontonummer, char* BLZ. Sie gibt ein Pointer vom Type char zurück.



int main(void){
FILE *fp;
int i;
int AnzahlBankDaten=56;//56 wegen Anzahl Bankdaten
int iBLZ;
char Filialname[MAX_FILILIALNAME];
char Kontonummer[MAX_KONTONMR];
char BLZ[MAX_BLZ];

fp = fopen("BLZ.txt", "r");
if(fp == NULL) {
	printf("Datei konnte nicht geoeffnet werden.\n");
}else {
	for(i=0; i<=AnzahlBankDaten; i++) {

		fscanf(fp,"%d;%"MAX_FILIALNAME_LEN_S"[^\r]s",&iBLZ,Filialname);
		printf("%d *** %s\n", iBLZ,Filialname);

	}

}
printf("Bitte geben Sie eine gültige Kontonummer ein (10 Stellen): ");
scanf("%s", Kontonummer);
printf("Bitte geben Sie eine Bankleitzahl ein (8 Stellen): ");
scanf("%s", BLZ);
if((ueberpruefebankdaten(Kontonummer,BLZ) == true)) {
      printf("die  Eingabe ist gültig!\n");
	}
else {
	printf("Eingabe ungültig!!\n");
		return 0;
	}
/*if(iBLZ==atoi(BLZ)){
	printf("Filialname :%s\n",Filialname);
}
else {
	printf("Filiale nicht gefunden\n");
}*/

char IBAN[IBAN_LAENGE] = {'\0'};
IBANberechnen(IBAN, Kontonummer, BLZ);

printf("IBAN: %s\n", IBAN);

fclose(fp);
return EXIT_SUCCESS;

}
bool ueberpruefekontonmr(char* Kontonummer) {
	char Konto_nummer[MAX_KONTONMR];
	strcpy(Konto_nummer,Kontonummer);
    int i = 0;
	for(i = 0; i < (MAX_KONTONMR-1 - strlen(Konto_nummer)); i++) {
		Kontonummer[i] = '0';
	}
	strncpy(&Kontonummer[i], Konto_nummer, strlen(Konto_nummer));// kopiert Anzahl(strlen(Konto_nummer)) von Zeichen von Konto_nummer zu Kontonummer

	for(int i=1; i < MAX_KONTONMR; i++) {
		if(Kontonummer[i-1] < '0' || Kontonummer[i-1] > '9') {
			printf("Die eingegebene Kontonummer ist ungültig\n");
			return false;
		}
	}
	return true;
}
bool ueberpruefeblz(char BLZ[MAX_BLZ]) {
	for(int i=1; i < MAX_BLZ; i++) {
		if(BLZ[i-1] < '0' || BLZ[i-1] > '9') {
			printf("Die eingegebene Bankleitzahl ist ungültig. MAX 8 Stellen.\n");
			return false;
		}
	}
	return true;
}
bool ueberpruefebankdaten(char Kontonummer[MAX_KONTONMR], char BLZ[MAX_BLZ]) {
	printf("Ihre Eingabe ist:\nKontonummer : %s\nBankleitzahl: %s\n", Kontonummer, BLZ);


	if(ueberpruefekontonmr(Kontonummer) == false) {
		return false;
	}

	if(ueberpruefeblz(BLZ) == false) {
		return false;
	}

	return true;
}
int berechnePp(char* Kontonummer, char* BLZ) {
	char NIBAN[NIBAN_LAENGE] = {'0'};
	int PP;
    strncpy(NIBAN, BLZ, MAX_BLZ-1); // kopiert(MAX_BLZ-1) von BLZ in NIBAN ()
	strncpy(&NIBAN[MAX_BLZ-1], Kontonummer, MAX_KONTONMR-1);//kopiert(MAX_KONTONMR-1) von Kontonummer in NIBAN
	strncpy(&NIBAN[18], "1314", 4);//kopiert 4 zeichen "1314 in NIBAN
	strncpy(&NIBAN[22],"00", 2); // kopiert 2 zeichen "00" in NIBAN
    printf("nIBAN: %s\n", NIBAN);
    // Prüffziffer berechnen
	char tl = 4;
	char Laenge = (NIBAN_LAENGE-1) / tl; //Laenge=6
	char Nullstring[3] = "00";
	char* TeilString;
	TeilString= (char*)malloc(sizeof(char)*(Laenge+2));
	for(int i = 0; i < tl; i++) {
		strncpy(TeilString, Nullstring, 2);
		strncpy(&TeilString[2], &NIBAN[i*Laenge], Laenge);
		sprintf(Nullstring, "%d", (atoi(TeilString) % 97));//sprintf Instead of printing on console, it store output on char buffer which are specified in sprintf
	}
	PP= 98-atoi(Nullstring);
	return PP ;
}
char* IBANberechnen(char* IBAN, char* Kontonummer, char* BLZ) {
	int Pruefziffer = berechnePp(Kontonummer, BLZ);
    char Prfziffer[3] = {'\0'};
	sprintf(Prfziffer, "%d", Pruefziffer);
	if(strlen(Prfziffer) < 2) {
		Prfziffer[1] = Prfziffer[0];
		Prfziffer[0] = '0';
	}
    printf("Prüfziffer: %s\n", Prfziffer);
    strcat(IBAN, "DE");
	strcat(IBAN, Prfziffer);
	strcat(IBAN, BLZ);
	strcat(IBAN, Kontonummer);
	return IBAN;
}























