/*
 Dateiname : Minesw.c
 Programm  : Realisierung das Spiel Minesweeper
 Eingaben  : Parametereingabe bei Programmaufruf ueber Konsole. Aufruf mit:
            Dateiname,Zeileen und Spaltern
 Ausgaben  : 0
 Autor     : Akoudad Oualid und Faris Elfellah 11132551
 Version   :1
 Datum     : 12.12.2020
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "console.h"
#include <ctype.h>

#define MIN_ANZAHL_ZeileEN 10
#define MAX_ANZAHL_ZeileEN 26
#define MIN_ANZAHL_SPALTEN 10
#define MAX_ANZAHL_SPALTEN 26



// Funktionsprototypen

void ClearLine(int Line,int SCOL);
char **erstelleboard(int m , int n,char x);
void Bildschirmmaske(int m,int n,int *Spalt,int *ZeileAOM,int *Zeile,int *RZeile);
void zeigefeld(char ** board, char ** mines, int m, int n,int k);
void instaliereminen(char **mines,int m,int n,int totalmines);
int totalmine(int m,int n);
int checkmines( char ** board,char ** mines, int m, int n, int row, int col);
int check_feld( char ** board, char ** mines, int m, int n, int row, int col ) ;
int check_Ende( char ** board, char ** mines, int m, int n,int totalmines );
int check_EndeAUF( char ** board, char ** mines, int m, int n,int totalmines );
char leseSpielzugEin(int ZeileAOM,int Spalt) ;
void startgame(char ** board, char ** mines, int m, int n,int *Spielzug,int Zeile,int Spalt,int ZeileAOM,int totalmines);
void Dateierstellen(char ** board, char ** mines, int m, int n,char* FileName);
void zeigeSpielergebnis(char ** board, char ** mines, int Spielzug,char* sDateiName,int m,int n,int Spieldauer,int RZeile);



int main(int argc, char *argv[])
{
	int Spielzug=0;
	int n=0, m=0, totalmines=0;
	char x='x';
	int Sekunden=0;
	time_t tStart=0, tEnd=0;
	int ZeileAOM=0,Spalt=0,Zeile=0,RZeile=0;

	char **board=NULL;
	char **mines=NULL;

	char* DateiName = NULL;

	if(argc==1)
	{
		printf("Kein Argc gegeben wird\n");
		return 0;
	}

	if(argc > 1) {
		// Name der Datei in die das Spielfeld und das Spielergebnis geschrieben werden
		DateiName = argv[1];
	}

	if(argc > 3) {
		n = atoi(argv[2]);
		m = atoi(argv[3]);

		// Validierung der Eingaben
		if(m< MIN_ANZAHL_ZeileEN || m > MAX_ANZAHL_ZeileEN) {
			printf("m muss zwischen %i und %i liegen!\n", MIN_ANZAHL_ZeileEN, MAX_ANZAHL_ZeileEN);
			return EXIT_FAILURE;
		}
		if(n < MIN_ANZAHL_SPALTEN || n > MAX_ANZAHL_SPALTEN) {
			printf("n muss zwischen %i und %i liegen", MIN_ANZAHL_SPALTEN, MAX_ANZAHL_SPALTEN);
			return EXIT_FAILURE;
		}
	} else {
		m= MIN_ANZAHL_ZeileEN;
		n = MIN_ANZAHL_SPALTEN;
	}
	totalmines=totalmine(m,n);


	printf("Die Spielfeldgroesse ist %d x %d, mit %d Minen\n", n, m, totalmines);
	Bildschirmmaske(m,n,&Spalt,&ZeileAOM,&Zeile,&RZeile);
	board=erstelleboard(m,n,x);
	mines=erstelleboard(m,n,' ');

	instaliereminen(mines,m,n,totalmines);

	Dateierstellen( board,  mines,  m, n, DateiName);

	free(board);
	board=erstelleboard(m,n,x);
	zeigefeld( board,mines, m, n ,0);


	time(&tStart);
	startgame(board, mines,  m,  n,&Spielzug,Zeile,Spalt,ZeileAOM,totalmines);
	time(&tEnd);

	Sekunden = (int) (tEnd - tStart);
	zeigeSpielergebnis(board, mines, Spielzug,DateiName,m,n,Sekunden,RZeile);


	return 0;
}

/*
 Funktion  : ClearLine
 Aufgabe   : Clear Eingaben
 Eingaben  : m,n,x
 Ausgaben  : board
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */


void ClearLine(int Line,int SCOL)
{
	CURPOS(Line, SCOL); printf("   ");
}
/*
 Funktion  : erstelleboard
 Aufgabe   : instialsiert das Array
 Eingaben  : m,n,x
 Ausgaben  : board
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */
char **erstelleboard(int m , int n,char x){
	int i=0,j=0;
	char **board= NULL;

	board = (char **) calloc(m, sizeof(char*));

	for (i = 0; i < m; i++) {
		board[i] = (char *) calloc( n, sizeof(char) );
	}

	for(i=0; i < m; i++) {
		for(j=0; j < n; j++) {
			board[i][j] = x;
		}
	}
	return board;
}


void Bildschirmmaske(int m,int n,int *Spalt,int *ZeileAOM,int *Zeile,int *RZeile){
	int j=4,i=0;
	CLS;

	CURPOS(1,   1); printf("Minesweeper  (c) 2020");
	CURPOS(2,   1); printf("-------------------------------------------------------------------------");
	CURPOS(j++, 5);
	for(i=0; i <n; i++) {
		printf("%3d", i+1);
	}
	CURPOS(j++, 5);
	for(i=0; i < n; i++) {
		printf("---");
	}

	for(i=0; i < m; i++) {
		CURPOS(j++, 1);
		//Zeilen
		printf("%3c|", i+65);
		CURPOS(j-1, n*3+6);
		printf("|%3c", i+65);
	}
	CURPOS(j++, 5);
	for(i=0; i < n; i++) {
		printf("---");
	}

	CURPOS(j++, 5);
	for(i=0; i <n; i++) {
		printf("%3d", i+1);
	}
	CURPOS(j++, 1);
	//Comment oder Message Zeile
	*RZeile=j+1;

	j=(m+5)/2;

	if(n>=20)
		n=n-5;
	CURPOS(j++, n*5);
	printf("---------------------------------------------------");
	CURPOS(j++, n*5);
	printf("|  Feld aufdecken (A)  |");
	CURPOS(j-1, n*5+50);
	printf("|");
	CURPOS(j++, n*5);
	printf("|        oder          |");
	//Spalte und Zeile für die Eingaben
	*Spalt=n*5+36;
	*ZeileAOM=j-1;
	CURPOS(j-1, n*5+50);
	printf("|");
	CURPOS(j++, n*5);
	printf("|  Feld markieren (M)  |");
	CURPOS(j-1, n*5+50);
	printf("|");
	CURPOS(j++, n*5);
	printf("---------------------------------------------------");
	CURPOS(j++, n*5);
	printf("|     Zeile Spalte     |");
	*Zeile=j-1;
	CURPOS(j-1, n*5+50);
	printf("|");
	CURPOS(j++, n*5);
	printf("---------------------------------------------------");

}


/*
 Funktion  : zeigefeld
 Aufgabe   : zeigt das ende vesion des Feld
 Eingaben  : board,mines,m,n
 Ausgaben  : kein
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */

void zeigefeld(char ** board, char ** mines, int m, int n,int k){

	int i=0,j=0;
	int StartZeile=6;
	for(i=0; i < m; i++) {
		CURPOS(StartZeile++, 5);
		for(j=0; j < n; j++) {
			//Ausgabe des Spielfelds
			if(k==1)
			{
				if( (board[i][j]=='x')&&(mines[i][j]=='-')){
					printf("%3c", mines[i][j]);
				}
				else
				 	printf("%3c", board[i][j]);
			}
			else
				printf("%3c", board[i][j]);
		}
	}
}

/*
 Funktion  : instaliereminen
 Aufgabe   : instialisiert das Mines Array mir rand position fuer minen
 Eingaben  : mines,m,n,totalmines
 Ausgaben  : kein
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */

void instaliereminen(char **mines,int m,int n,int totalmines){
	int rows=0,columns=0,i=0;
	srand(time(NULL));
	for(i=0;i<totalmines;i++){
		rows = (rand()%m);
		columns = (rand()%n);
		if( mines[rows][columns] == ' ' ) {
			mines[rows][columns] = '-';
		}else
			i--;
	}
}
/*
 Funktion  : totalmine
 Aufgabe   : geiert ein Zahl fuer Totalminen die mussen nicht klein als10% und nicht grosser als 25%
 Eingaben  : m,n
 Ausgaben  : AnzahlMinen
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */

int totalmine(int m,int n){
	int min=0,max=0;
	int AnzahlMinen = 0;
	time_t t;
	min=(n*m)/10;
	max=(n*m)/4;

	//Initialisiert Zufallszahlengenerator
	srand((unsigned) time(&t));
	// Zahl muss zwischen den Min- und Maxwerten liegen
	do {
		AnzahlMinen = rand() % (((max+min)/2)+1);
	} while(AnzahlMinen < min || AnzahlMinen > max);

	return AnzahlMinen;

}

/*
 Funktion  : checkmines
 Aufgabe   : prueft ob minen in Die umgebung gibt
 Eingaben  : board,mines,m,n,row,col
 Ausgaben  : 0,1,3
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */

int checkmines( char ** board,char ** mines, int m, int n, int row, int col){
		/*
			Recur for all 8 adjacent cells

				  N.W N  N.E
				   \  |  /
					\ | /
				W----Cell----E
					/ | \
				   /  |  \
				S.W  S   S.E

			Cell-->Current Cell (row, col)
			N --> North	 (row-1, col)
			S --> South	 (row+1, col)
			E --> East		 (row, col+1)
			W --> West		 (row, col-1)
			N.E--> North-East (row-1, col+1)
			N.W--> North-West (row-1, col-1)
			S.E--> South-East (row+1, col+1)
			S.W--> South-West (row+1, col-1)
	*/
	int counter=0;
	if( mines[row][col] == '-' ) {
		return 0;
	}

	//int counter=0;

	if( (row+1 < m) && (mines[row+1][col] == '-') ) {
		counter++;
	}
	if( (row-1 >= 0) && (mines[row-1][col] == '-') ) {
		counter++;
	}
	if( (col+1 < n) && (mines[row][col+1] == '-') ) {
		counter++;
	}
	if( (col-1 >= 0) && (mines[row][col-1] == '-') ) {
		counter++;
	}
	if( (row+1 < m) && (col-1 >= 0) && (mines[row+1][col-1] == '-') ) {
		counter++;
	}
	if( (row-1 >= 0) && (col+1 < n) && (mines[row-1][col+1] == '-') ) {
		counter++;
	}
	if( (row+1 < m) && (col+1 < n) && (mines[row+1][col+1] == '-') ) {
		counter++;
	}
	if( (row-1 >= 0) && (col-1 >= 0) && (mines[row-1][col-1] == '-') ) {
		counter++;
	}
	//48+ weil board is ein char
	board[row][col] = 48+counter;

	if(counter!=0){
		return 1;
	}
	return 3;
}
/*
 Funktion  : check_feld
 Aufgabe   : prueft wenn kein minen in Die umgebung gibt die NAchbarn
 Eingaben  : board,mines,m,n,row,col
 Ausgaben  : 0,1
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */
int check_feld( char ** board, char ** mines, int m, int n, int row, int col ) {
	if(checkmines(board,mines,m, n,row,col)==3)
	{
		if( (row+1 < m) && (board[row+1][col] == 'x') && (mines[row+1][col] == ' ') ) {
		check_feld( board, mines, m, n, row+1, col );
		}

		if( (row-1 >= 0) && (board[row-1][col] == 'x') && (mines[row-1][col] == ' ') ) {
			check_feld( board, mines,m, n, row-1, col );
		}

		if( (col+1 < n) && (board[row][col+1] == 'x') && (mines[row][col+1] == ' ') ) {
			check_feld( board, mines, m, n, row, col+1 );
		}

		if( (col-1 >= 0) && (board[row][col-1] == 'x') && (mines[row][col-1] == ' ') ) {
			check_feld( board, mines, m, n, row, col-1 );
		}

		if( (row-1 >= 0) && (col+1 < n) && (board[row-1][col+1] == 'x') && (mines[row-1][col+1] == ' ') ) {
			check_feld( board, mines, m, n, row-1, col+1 );
		}

		if( (row-1 >= 0) && (col-1 >= 0) && (board[row-1][col-1] == 'x') && (mines[row-1][col-1] == ' ') ) {
			check_feld( board, mines,  m, n, row-1, col-1 );
		}

		if( (row+1 < m) && (col+1 < n) && (board[row+1][col+1] == 'x') && (mines[row+1][col+1] == ' ') ) {
			check_feld( board, mines,  m, n, row+1, col+1 );
		}

		if( (row+1 < m) && (col-1 >= 0) && (board[row+1][col-1] == 'x') && (mines[row+1][col-1] == ' ') ) {
			check_feld( board, mines, m, n, row+1, col-1 );
		}
	}
	if(checkmines(board,mines,m,n,row,col)==0){
		return 0;
	}
	return 1;
}
/*
 Funktion  : check_Ende
 Aufgabe   : prueft ob das Spiel is fertig
 Eingaben  : board,mines,m,n
 Ausgaben  : 0 ,1ist fertig
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */

int check_Ende( char ** board, char ** mines, int m, int n,int totalmines ) {
	int i=0, j=0;
	for(i=0; i < m; i++) {
		for(j=0; j < n; j++) {
			if( (mines[i][j] == ' ') && (board[i][j] == 'x') ) {
				return 0;
			}
		}
	}
	return 1;
}
/*
 Funktion  : check_EndeAUF
 Aufgabe   : prueft ob das Spiel is fertig durch FieldMarkierung
 Eingaben  : board,mines,m,n,totalmines
 Ausgaben  : 2 ,1ist fertig
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */
int check_EndeAUF( char ** board, char ** mines, int m, int n,int totalmines ) {
	int i=0, j=0;
	int zaehler=0;
	for(i=0; i < m; i++) {
		for(j=0; j < n; j++) {
			if( (mines[i][j] == '-') && (board[i][j] == 'M') ) {
					zaehler++;
			}
		}
	}
	if(zaehler == totalmines)
		return 1;
	return 2;
}
/*
 Funktion  : leseSpielzugEin
 Aufgabe   : liest das Spielzug ein
 Eingaben  : Eingabe
 Ausgaben  : Eingabe
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */
char leseSpielzugEin(int ZeileAOM,int Spalt) {
	char Eingabe[5]= {0};
	bool Valid = false;

	do {
		CURPOS(ZeileAOM, Spalt);
		scanf("%s",Eingabe);
		if(Eingabe[0] != 'A' && Eingabe[0] != 'M') {
			Valid = false;
		} else {
			Valid = true;
		}
	} while(!Valid);
	return Eingabe[0];
}

/*
 Funktion  : startgame
 Aufgabe   : das Speil fangt an
 Eingaben  : board,  mines,  m,  n,Spielzug
 Ausgaben  : kein
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */

void startgame(char ** board, char ** mines, int m, int n,int *Spielzug,int Zeile,int Spalt,int ZeileAOM,int totalmines)
{

	int col=0,rows=0;
	char cInput = 0;
	char Eingabe[5]={0};
	char Str[3]={0}	;
	int k=0;
	while(1)
	{
		ClearLine(ZeileAOM,Spalt);
		ClearLine(Zeile,Spalt);

		//(Feld aufdecken (A) | Feld markieren/Markierung entfernen (M)
		cInput= leseSpielzugEin(ZeileAOM,Spalt);

		//Zeilee Spalte
		CURPOS(Zeile, Spalt);
		scanf("%s", &Eingabe[0]);
		//clear Comment
		CURPOS(Zeile+3,Spalt-36);
		printf("                                                                  ");
		if(Eingabe[0]>=65&&Eingabe[0]<=90){
			 rows=Eingabe[0]-64;
		}
		else if (Eingabe[0]>=97&&Eingabe[0]<=122){
			rows=Eingabe[0]-96;
		}
		else{
			CURPOS(Zeile+3, Spalt-36);
			printf("Falsche Eingabe!");
		}
		if(Eingabe[1]>= '0' &&Eingabe[1] <= '9'&& ((Eingabe[2] >= '0' && Eingabe[2] <= '9') || Eingabe[2] == '\0' || Eingabe[2] == '\n') ){
			memcpy(Str, &Eingabe[1], 2);
		}
		else{
			CURPOS(Zeile+3, Spalt-36);
			printf("Falsche Eingabe!");
		}

		col=atoi(Str);

	  	rows--;
		col--;

		//Feldgrenzen
		if( rows >= m || rows < 0 ) {
			CURPOS(Zeile+3, Spalt-36);
			printf("Zeilee muss zwischen A und %c sein!\n", m+64);
			continue;
		}
		if( col >= n || col < 0 ) {
			CURPOS(Zeile+3, Spalt-36);
			printf("Spalte muss zwischen 1 und %d sein!\n", n);
			continue;
		}
		//FeldMarkierung
		if(cInput == 'M') {
			board[rows][col] = 'M';
			zeigefeld( board,mines, m, n,k );
			*Spielzug=*Spielzug+1;
			//fertig
			if( check_EndeAUF(board, mines, m, n,totalmines)==1){
				//Zeige die Minen an
				k=1;
				zeigefeld( board,mines, m, n ,k);
				CURPOS(Zeile+3, Spalt-36);
				printf("Super! Korrekt geloest!");
				break;
			}
		}
		else
		{
			//verloren
			if( check_feld( board, mines, m, n, rows, col ) == 0 ) {
				//Zeige die Minen an
				k=1;
				zeigefeld( board,mines, m, n,k );
				CURPOS(Zeile+3, Spalt-36);
				printf("Zeilee: %c Spalte: %d war leider eine Mine!", rows+'A', col+1 );
				break;
			}
			//gewonnen
			else if( check_Ende(board, mines, m, n,totalmines)==1) {
				//Zeige die Minen an
				k=1;
				zeigefeld( board,mines, m, n ,k);
				CURPOS(Zeile+3, Spalt-36);
				printf("Super! Korrekt geloest!");
				break;
			}
			//weiterspielen
			else
			{
				*Spielzug=*Spielzug+1;
				zeigefeld( board,mines, m, n,k );
			}
		}
	}
}
/*
 Funktion  : Dateierstellen
 Aufgabe   : Erstellung von txt datei und da das Spielergebnis speichern
 Eingaben  : board,  mines,  m,  n,Spielzug,FileName
 Ausgaben  : kein
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */
void Dateierstellen(char ** board, char ** mines, int m, int n,char* FileName){
	int i=0, j=0;
	FILE* oFile;

	// Ausgabestream wird ausgewÃƒÂ¤hlt
	if(FileName != NULL) {
		oFile = fopen(FileName, "w");
	} else {
		oFile = stdout;
	}

	fprintf(oFile,"\n\n");
	//Spaltenbeschriftung
	fprintf(oFile,"    ");
	for(i=0; i < n; i++) {
		fprintf(oFile,"%3d", i+1);
	}
	fprintf(oFile,"\n");
	//TrennZeilee
	fprintf(oFile,"    ");
	for(i=0; i < n; i++) {
		fprintf(oFile,"---");
	}
	fprintf(oFile,"\n");

	for(i=0; i < m; i++) {
		//Zeilen
		fprintf(oFile,"%3c|", i+65);
		for(j=0; j < n; j++) {
			check_feld( board, mines, m, n, i, j);
			//Ausgabe des Spielfelds
			if( (board[i][j]=='x')&&(mines[i][j]=='-')){
				fprintf(oFile,"%3c", mines[i][j]);
			}
			else
			 	fprintf(oFile,"%3c", board[i][j]);
		}
		//Zeilen
		fprintf(oFile," |%-3c\n", i+65);
	}
	//TrennZeilee
	fprintf(oFile,"    ");
	for(i=0; i < n; i++) {
		fprintf(oFile,"---");
	}
	fprintf(oFile,"\n");
	//Spalten
	fprintf(oFile,"    ");
	for(i=0; i < n; i++) {
		fprintf(oFile,"%3d", i+1);
	}
	fprintf(oFile,"\n\n");

	if(FileName != NULL) {
		fclose(oFile);
	}
}

/*
 Funktion  : zeigeSpielergebnis
 Aufgabe   : zeige das Spielergebnis sowie Spielzug ,Spieldauer,Korrekt und nicht korrekt markierte Minen
 Eingaben  : board,  mines,  m,  n,Spielzug,FileName
 Ausgaben  : kein
 Autor     : Akoudad Oualid
 Version   : 01
 Datum der letzten Ãƒâ€žnderung: 12.12.20
 */

void zeigeSpielergebnis(char ** board, char ** mines, int Spielzug,char* sDateiName,int m,int n,int Spieldauer,int RZeile)
{
	int i=0,j=0;
	char* KorrektMarkierteMinen=NULL;
	char* NichtGetroffeneMinen=NULL;
	char sStr[3] = {'\0'};

	FILE* oFile = fopen(sDateiName, "a");
	KorrektMarkierteMinen =calloc(100, sizeof(char));
	NichtGetroffeneMinen=calloc(100, sizeof(char));

	for(i=0; i < m; i++) {
		for(j=0; j < n; j++) {
			if(mines[i][j]=='-'){
				if(board[i][j]=='M'){
					sprintf(sStr, "%c%i\t", i+'A', j+1); // Umwandlung von Index-Position zu Anzeige-Position
					KorrektMarkierteMinen = strcat(KorrektMarkierteMinen, sStr);
				}else {
					sprintf(sStr, "%c%i\t", i+'A', j+1); // Umwandlung von Index-Position zu Anzeige-Position
					NichtGetroffeneMinen = strcat(NichtGetroffeneMinen, sStr);
				}
			}
		}
	}
	RZeile++;
	CURPOS(RZeile++, 1);
	printf("Nicht getroffene Minen: %s", NichtGetroffeneMinen);
	fprintf(oFile, "Nicht getroffene Minen: %s\n", NichtGetroffeneMinen);
	RZeile++;
	CURPOS(RZeile++, 1);
	printf("Korrekt markierte Minen: %s", KorrektMarkierteMinen);
	fprintf(oFile, "Korrekt markierte Minen: %s\n", KorrektMarkierteMinen);
	RZeile++;
	CURPOS(RZeile++, 1);
	printf("Spielzuege: %i",Spielzug);
	fprintf(oFile, "Spielzuege: %i\n", Spielzug);
	RZeile++;
	CURPOS(RZeile++, 1);
	printf("Time: %i Min. %i Sek.",(Spieldauer/60), Spieldauer % 60);
	fprintf(oFile, "Time: %i Min. %i Sek.\n", (Spieldauer/60), Spieldauer % 60);

	fclose(oFile);
}


